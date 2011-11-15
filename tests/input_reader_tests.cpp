#include <assert.h>
#include <fstream>
#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include "tbb/blocked_range.h"
using namespace std;
using namespace tbb;
#include "debug.h"
#include "test.h"
#include "problem_data.h"
#include "input_reader.h"

/* Tests declaration */
void CountRowColumnFromFilehandleTest ();
void CountRowColumnFromFilehandleScenario3Test ();
void InstanciateProblemDataFromFilenameTest ();
void InstanciateProblemDataFromFilenameScenario3Test ();

int main (void)
{
  CountRowColumnFromFilehandleTest ();
  CountRowColumnFromFilehandleScenario3Test();
  InstanciateProblemDataFromFilenameTest ();
  InstanciateProblemDataFromFilenameScenario3Test ();
}

void CountRowColumnFromFilehandleTest ()
{
  TEST_TITLE ("CountRowColumnFromFilehandleTest");
  string data = "0 0 12 0 14\n12 5 22 21 15\n12 5 22 21 15";
  
  //assert (iss);
  int row = 0, column = 0;
  
  CountRowColumnFromFilehandle (data.c_str(), &row, &column, data.length());
  DEBUG_IF (row != 1, row);
  TEST (row == 1);
  TEST (column == 5);
}

void CountRowColumnFromFilehandleScenario3Test ()
{
  TEST_TITLE ("CountRowColumnFromFilehandleScenario3Test");
  string data = "0 0 12 0 14\n12 5 22 21 15\n12 5 22 21 15\n12 5 22 21 15\n";
  
  //assert (iss);
  int row = 0, column = 0;
  
  CountRowColumnFromFilehandle (data.c_str(), &row, &column, data.length());
  
  DEBUG_IF (row != 1, row);
  TEST (row == 1);
  DEBUG_IF (column != 5, column);
  TEST (column == 5);
}

void InstanciateProblemDataFromFilenameTest ()
{
  TEST_TITLE ("CountRowColumnFromFilehandleTest");
  ProblemData *data = NULL;
  data = InstanciateProblemDataFromFilename ("scenarios/scenario1/data");
  
  TEST (data -> GetWidth () == 5);
  TEST (data -> GetHeight () == 3);
  TEST (data -> GetValue (0, 0) == 0);
  TEST (data -> GetValue (1, 0) == 0);
  TEST (data -> GetValue (4, 2) == 15);
}

void InstanciateProblemDataFromFilenameScenario3Test ()
{
  TEST_TITLE ("InstanciateProblemDataFromFilenameScenario3Test");
  ProblemData *data = NULL;
  data = InstanciateProblemDataFromFilename ("scenarios/scenario3/input.txt");
  
  TEST (data -> GetWidth () == 101);
  DEBUG_IF (data -> GetHeight () != 100, data -> GetHeight ());
  TEST (data -> GetHeight () == 100);
}