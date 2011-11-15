using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <assert.h>
#include <string>

#include "problem_data.h"
#include "input_reader.h"
#include "verif.h"

#ifndef UNIT_TEST

int main (int argc, char *argv[])
{
  assert (argc == 6);
  string filename (argv[1]);
  ProblemData * data = InstanciateProblemDataFromFilename (filename);
  int total = CalculateMaxValue (*data, argv + 2);
  cout << "Subarray value " << total << endl;
  
}

#endif

int CalculateMaxValue (ProblemData & data, char *borne[])
{
  assert (*borne != NULL);
  int borne_x_gauche = atoi (borne[0]);
  int borne_y_gauche = atoi (borne[1]);
  int borne_x_droite = atoi (borne[2]);
  int borne_y_droite = atoi (borne[3]);
  int total = 0;
  
  for (int i = borne_x_gauche; i <= borne_x_droite; i++)
  {
    for (int j = borne_y_gauche; j <= borne_y_droite; j++)
    {
      total += data.GetValue (i, j);
    }
  }
  
  return total;
}