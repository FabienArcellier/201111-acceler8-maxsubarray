#include <iostream>
#include <fstream>
#include <cstdlib>
#include <assert.h>
#include <string>
#include <vector>
#include <list>
using namespace std;

#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/cache_aligned_allocator.h"
using namespace tbb;

#include "debug.h"
#include "problem_data.h"
#include "cache_problem_data.h"
#include "coords_maximum_subarray.h"
#include "apply_kadan2d.h"
#include "apply_kadan2d_with_cache.h"
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
  
  task_scheduler_init init_tbb (application_settings.processor_number);
  
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
    
    CoordsMaximumSubarray *tab = Algorithm -> GetCoordsMaximumSubarray ();
    DisplayMaxSubarray (*tab);
    
    delete Algorithm;
    delete data;
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
void DisplayMaxSubarray (CoordsMaximumSubarray &max_subarray_bornes)
{
  max_subarray_bornes.Display ();
}