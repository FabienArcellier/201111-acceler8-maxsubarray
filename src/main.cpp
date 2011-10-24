#include <iostream>
#include <fstream>
using namespace std;

#include <assert.h>
#include "debug.h"
#include "problem_data.h"
#include "main.h"


#ifndef UNIT_TEST

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    DisplayHelp ();
  }
}

#endif

/*!
 * \brief Display information when the program can't be executed
 */
void DisplayHelp ()
{
  cout << "Usage : run [PROCESSORS] [FILES]...\n\n";
  cout << "\tDisplay the coords of the maximum subarray for each array contained in FILES\n\n";
  cout << "\t[PROCESSORS] Count of processor used\n\n";
  cout << "Exemple";
  cout << "\t./run 40 input1.txt input2.txt input3.txt > output.txt\n";
}

/*!
 * \brief Display the coord of an array with 4 items
 */
void DisplayMaxSubarray (int max_subarray_bornes[])
{
  assert (max_subarray_bornes != NULL);
  
  for (int i = 0; i < 4; i++)
  {
    cout << max_subarray_bornes[i];
    if (i < 3)
    {
      cout << " ";
    }
    else
    {
      cout << "\n";
    }
  }
}

/*!
 * \brief Load data into an instance of ProblemData
 */
ProblemData * InstanciateProblemDataFromFilename (char filename[])
{
  ifstream file_handle (filename);
  if (!file_handle)
  {
    cerr << "Can't open " << filename;
    //exit (1);
  }
  
  int row = 0, column = 0;
  short buffer = 0;
  char cbuffer = '\0';
  int i = 0, j = 0;
  
  DEBUG_IF (1, "%d", file_handle.eof ());
  CountRowColumnFromFilehandle (file_handle, &row, &column);
  DEBUG_IF (1, "%d", file_handle.eof ());
  
  ProblemData *data = NULL;
  data = new ProblemData (row, column);
 
  while (file_handle.eof () == 0)
  {
    file_handle >> buffer;
    file_handle >> cbuffer;
    i++; 
    (*data).SetValue(i, j, buffer);
    if (cbuffer == '\n')
    {
      j++;
      i = 0;
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
  cout << file_handle.tellg () << '\n';
  while (file_handle.eof () == 0)
  {
    // Invariant, there was a segmentation fault because of NULL value
    assert (column != NULL);
    assert (row != NULL);
    
    cout << file_handle.eof () << '\n';
    file_handle.get (character);
    
    if (character == ' ')
    {
      (*column)++;
    }
    else if (character == '\n')
    {
      (*row)++;
      if (column_reference == 0)
      {
        column_reference = *column;
      }
      
      assert (*column == column_reference);
      *column = 0;
    }
  }
  file_handle.seekg (0, ios::beg);
  
  // Pour the space after the last element is missing
  *column = column_reference + 1; 
  
  cout << file_handle.tellg () << '\n';
  assert (file_handle.tellg () == 0);
}