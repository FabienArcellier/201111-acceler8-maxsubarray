#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <cstdlib>
#include <assert.h>
#include <string>
#include "tbb/tick_count.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_reduce.h"
using namespace std;
using namespace tbb;
#include "debug.h"
#include "problem_data.h"
#include "input_reader.h"

/*!
 * \brief Load data into an instance of ProblemData
 */
ProblemData * InstanciateProblemDataFromFilename (string filename)
{
  ifstream file_handle (filename.c_str());
  if (!file_handle)
  {
    cerr << "Can't open " << filename;
    //exit (1);
  }
  
  tick_count t0 = tick_count::now();
  
  file_handle.seekg (0, ios::end);
  int file_length = (int) (file_handle.tellg()) + 1;
  file_handle.seekg (0, ios::beg);
  char* string_buffer = (char *) malloc(file_length * sizeof (char));
  file_handle.read (string_buffer, file_length);  
  file_handle.close ();
  
  tick_count t1 = tick_count::now();
  tick_count::interval_t i_read_file = t1 - t0;
  DEBUG_IF(1, i_read_file.seconds());
  
  int row = 0, column = 0;
  
  
  CountRowColumnFromFilehandle (string_buffer, &row, &column, file_length);
  tick_count t2 = tick_count::now();
  tick_count::interval_t i_count_row_column = t2 - t1;
  DEBUG_IF(1, i_count_row_column.seconds());
  
  InputReaderParseData input_parse_data(string_buffer);
  parallel_reduce (blocked_range<int> (0, file_length, 10000), input_parse_data);
  list <short> *buffer_input = input_parse_data.data;
  
//   istringstream *string_stream = new istringstream (string_buffer,istringstream::in);
//   list<short> buffer_input;
//   for (string_stream -> seekg(0, ios::beg); string_stream -> tellg() < file_length && string_stream -> eof() == 0;)
//   {
//     short buffer;
//     *string_stream >> buffer;
//     buffer_input.push_back (buffer);
//   }
  
  row = buffer_input -> size() / column;
  DEBUG_IF(1, row);
  DEBUG_IF(1, column);
  DEBUG_IF(1, buffer_input -> size());
  
  tick_count t3 = tick_count::now();
  tick_count::interval_t i_load_data = t3 - t2;
  DEBUG_IF(1, i_load_data.seconds());
  
  ProblemData *data = NULL;
  data = new ProblemData (column, row);
  
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      data -> SetValue(j, i, buffer_input -> front());
      buffer_input -> pop_front();
    }
  }
  
  tick_count t4 = tick_count::now();
  tick_count::interval_t i_get_data = t4 - t3;
  DEBUG_IF(1, i_get_data.seconds());
  
  free(string_buffer);
  
  return data;
}

void CountRowColumnFromFilehandle (const char *buffer, int *row, int *column, int size)
{
  //assert (file_handle != NULL);
  assert (*row == 0);
  assert (*column == 0);
  
  int column_reference = 0;
  int separator = 0;
  int new_line = 0;

    // Invariant, there was a segmentation fault because of NULL value
  for (int i = 0; i < size - 1; i++)
  {
    assert (column != NULL);
    assert (row != NULL);
    char character = buffer[i];
    if (character == ' ' && separator == 0)
    {
      (*column)++;
      separator = 1;
    }
    else if (character == '\n')
    {
      if (*column != 0)
      {
        (*row)++;
      }
      
      if (separator == 1 && *column != 0)
      {
        (*column)--;
      }
      
      if (column_reference == 0)
      {
        column_reference = *column;
      }
      
      assert (*column == column_reference || *column == 0);
      *column = 0;
      new_line = 1;
      break;
    }
    else
    {
      separator = 0;
      new_line = 0;
    }
  }
  
  *column = column_reference + 1;
  if (new_line == 0)
  {
    (*row)++;
  }
}

/*!
 * \brief Task to perform as Parallel treatment
 */
void InputReaderParseData::operator () ( const blocked_range<int> &r)
{
  istringstream string_stream (this -> buffer,istringstream::in);
  string_stream.seekg (r.begin(), ios::beg);
  char character = '\0';
  if (r.begin() != 0)
  {
    do
    {
      character = string_stream.get();
    } while (character != '\n' && character != ' ');
  }
  
  for (; string_stream.tellg() <= r.end() && string_stream.eof() == 0;)
  {
    short buffer;
    string_stream >> buffer;
    this -> data  -> push_back (buffer);
  }
  
  string_stream.str("");
}

void InputReaderParseData::join (InputReaderParseData &r)
{
  list<short>::iterator it = this -> data -> end();
  this -> data -> splice (it, *(r.data));
}