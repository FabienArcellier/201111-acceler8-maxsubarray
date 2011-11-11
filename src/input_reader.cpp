using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <assert.h>
#include <string>
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
  
  int row = 0, column = 0;
  short buffer = 0;
  
  CountRowColumnFromFilehandle (file_handle, &row, &column);
  
  ProblemData *data = NULL;
  data = new ProblemData (column, row);
  
//   DEBUG_IF (1, column);
//   DEBUG_IF (1, row);
  
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      file_handle >> buffer;
      data -> SetValue(j, i, buffer);
    }
  }
  
  file_handle.close ();
  
  return data;
}

void CountRowColumnFromFilehandle (ifstream &file_handle, int *row, int *column)
{
  //assert (file_handle != NULL);
  assert (*row == 0);
  assert (*column == 0);
  assert (file_handle.tellg () == 0);
  
  int column_reference = 0;
  char character = '\0';
  int separator = 0;
  int new_line = 0;
  char line[500];
  
  while (file_handle.eof () == 0)
  {
    // Invariant, there was a segmentation fault because of NULL value
    assert (column != NULL);
    assert (row != NULL);
    file_handle.getline (line, 500);
//     DEBUG_IF (1, line);
    for (int i = 0; i < 500; i++)
    {
      character = line[i];
      if (character == ' ' && separator == 0)
      {
        (*column)++;
        separator = 1;
      }
      else if (character == '\0' && i != 499)
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
    
    if (file_handle.fail() == 1 && file_handle.eof () == 0)
    {
      file_handle.clear();
    }
  }
  file_handle.clear ();
  file_handle.seekg (0, ios::beg);
  
  // Pour the space after the last element is missing
  *column = column_reference + 1;
  if (new_line == 0)
  {
    (*row)++; 
  }
  
  assert (file_handle.tellg () == 0);
}