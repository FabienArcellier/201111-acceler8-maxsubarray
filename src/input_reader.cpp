#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <assert.h>
#include <string>
using namespace std;
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
  
  file_handle.seekg (0, ios::end);
  int file_length = (int) (file_handle.tellg()) + 1;
  file_handle.seekg (0, ios::beg);
  char* string_buffer = (char *) malloc(file_length * sizeof (char));
  file_handle.read (string_buffer, file_length);

  
  file_handle.close ();
  
  istringstream *string_stream = new istringstream (string_buffer,istringstream::in);
  
  int row = 0, column = 0;
  short buffer = 0;
  
  CountRowColumnFromFilehandle (string_buffer, &row, &column, file_length);
  
  ProblemData *data = NULL;
  data = new ProblemData (column, row);
  
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      *string_stream >> buffer;
      data -> SetValue(j, i, buffer);
    }
  }
  
  string_stream -> str("");
  delete string_stream;
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