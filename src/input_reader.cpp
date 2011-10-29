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
  while (file_handle.eof () == 0)
  {
    // Invariant, there was a segmentation fault because of NULL value
    assert (column != NULL);
    assert (row != NULL);
    file_handle.get (character);
    
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