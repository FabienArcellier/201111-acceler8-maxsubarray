#include <iostream>
#include <fstream>
#include <cstdlib>
#include <assert.h>
#include <string>
#include <vector>
#include <list>
using namespace std;

#include "debug.h"
#include "problem_data.h"
#include "coords_maximum_subarray.h"
#include "algorithm.h"
#include "input_reader.h"
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
    cout << "test" << endl;
    data = InstanciateProblemDataFromFilename (filenames[i]);
    algorithm * Algorithm = NULL;
    Algorithm = SelectAlgorithm (*data);
    Algorithm -> SetWorkerThreads ((short) (application_settings.processor_number));
    Algorithm -> resolve (*data);
    cout << "test" << endl;
    list<vector<int> > *tab = NULL;
    tab = Algorithm -> GetCoordMaximumSubArray ();
    DisplayMaxSubarray (*tab);
    
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
void DisplayMaxSubarray (list<vector<int> > & max_subarray_bornes)
{
  max_subarray_bornes.front ();
  std::list<vector<int> >::iterator it = max_subarray_bornes.begin();
  
  for (; it != max_subarray_bornes.end(); it++)
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
}