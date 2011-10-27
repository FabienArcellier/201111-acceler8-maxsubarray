#include <iostream>
#include <fstream>
using namespace std;

#include <assert.h>
#include <string>
#include <vector>
#include <cstdlib>
#include "debug.h"
#include "problem_data.h"
#include "algorithm.h"
#include "main.h"


#ifndef UNIT_TEST

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    DisplayHelp ();
  }
  
  ApplicationSettings application_settings;
  application_settings.processor_number = atoi (argv[1]);
  
  vector<string> filenames;
  for (int i = 2; i < argc; i++)
  {    
    string filename (argv[i]);
    filenames.push_back (filename);
  }
  
  assert (filenames.size() == (uint)(argc - 2));
  int count_filename = filenames.size();
  for (int i = 0; i < count_filename; i++)
  {
    ProblemData *data = NULL;
    data = InstanciateProblemDataFromFilename (filenames[i]);
    algorithm * Algorithm = NULL;
    Algorithm = SelectAlgorithm (*data);
    Algorithm -> SetWorkerThreads ((short) (application_settings.processor_number));
    Algorithm -> resolve (*data);
    list<vector<int> > *tab = NULL;
    tab = Algorithm -> GetCoordMaximumSubArray ();
    DisplayMaxSubarray (tab);
    
    delete Algorithm;
    delete data;
  }
  
  cout << "Fin du traitement" << endl;
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
void DisplayMaxSubarray (list<vector<int> > * max_subarray_bornes)
{
  assert (max_subarray_bornes != NULL);
  max_subarray_bornes -> front ();
  std::list<vector<int> >::iterator it = max_subarray_bornes -> begin();
  
  for (; it != max_subarray_bornes -> end(); it++)
  {    
    for (int j = 0; j < 4; j++)
    {
      cout << (*it)[j] << flush;
      if (j < 3)
      {
        cout << " ";
      }
      else
      {
        cout << "\n";
      }
    }
  }
  
  max_subarray_bornes -> front ();
}

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
  char cbuffer = '\0';
  int x = 0, y = 0;
  
  CountRowColumnFromFilehandle (file_handle, &row, &column);
  
  ProblemData *data = NULL;
  data = new ProblemData (column, row);
  
 
  while (file_handle.eof () == 0)
  {
    file_handle >> buffer;
    file_handle.get (cbuffer);
    data -> SetValue(x, y, buffer);
    x++; 
    if (cbuffer == '\n')
    {
      y++;
      x = 0;
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
  while (file_handle.eof () == 0)
  {
    // Invariant, there was a segmentation fault because of NULL value
    assert (column != NULL);
    assert (row != NULL);
    
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
  file_handle.clear ();
  file_handle.seekg (0, ios::beg);
  
  // Pour the space after the last element is missing
  *column = column_reference + 1;
  (*row)++; 

  assert (file_handle.tellg () == 0);
}