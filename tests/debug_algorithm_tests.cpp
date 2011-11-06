using namespace std;
#include <cassert>
#include <iostream>
#include <string>
#include "test.h"
#include "debug.h"
#include "problem_data.h"
#include "debug_algorithm.h"

// Prototype des fonctions de tests
void GeneralTests ();

int main (void)
{
  GeneralTests ();
  return 0;
}

void GeneralTests ()
{
  // Assignation
  TEST_TITLE ("GeneralTests");
  string filename ("debug_algorithm.log");
  ProblemData problem_data (5, 5);
  DebugAlgorithm debug (filename, problem_data);
  
  // Action
  debug.WriteCoord (1, 1, 3, 2);
  debug.WriteValue (1);
  debug.WriteMaxValue (5);
  debug.WriteEmptyLine ();
  debug.WriteMatrice (1, 1, 3, 2);
  debug.WriteEmptyLine ();
  
  // Tests
  cout << "Check the file debug_algoritm.log contains :" << endl;
  cout << "Value : 1" << endl;
  cout << "Max Value : 5" << endl;
}
