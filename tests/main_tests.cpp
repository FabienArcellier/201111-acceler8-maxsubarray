#include <assert.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
using namespace std;
#include "debug.h"
#include "test.h"
#include "problem_data.h"
#include "main.h"

/* Tests declaration */
void DisplayMaxSubarrayTests ();
void CountRowColumnFromFilehandleTest ();
void CountRowColumnFromFilehandleScenario3Test ();
void InstanciateProblemDataFromFilenameTest ();
void InstanciateProblemDataFromFilenameScenario3Test ();

int main (void)
{
  DisplayMaxSubarrayTests ();
  CountRowColumnFromFilehandleTest ();
  CountRowColumnFromFilehandleScenario3Test();
  InstanciateProblemDataFromFilenameTest ();
  InstanciateProblemDataFromFilenameScenario3Test ();
}

void DisplayMaxSubarrayTests ()
{
  TEST_TITLE ("DisplayMaxSubarrayTests");

  list<vector<int> > list;
  vector<int> tab (4);
  tab[0] = 4;
  tab[1] = 5;
  tab[2] = 6;
  tab[3] = 7;
  list.push_back (tab);
  list.push_back (tab);
  list.push_back (tab);
  DisplayMaxSubarray (list);
}

void CountRowColumnFromFilehandleTest ()
{
  TEST_TITLE ("CountRowColumnFromFilehandleTest");
  ifstream file_handle ("scenarios/scenario1/data");
  assert (file_handle);
  int row = 0, column = 0;
  
  CountRowColumnFromFilehandle (file_handle, &row, &column);
  DEBUG_IF (row != 3, row);
  TEST (row == 3);
  TEST (column == 5);
  
  file_handle.close();
}

void CountRowColumnFromFilehandleScenario3Test ()
{
  TEST_TITLE ("CountRowColumnFromFilehandleScenario3Test");
  ifstream file_handle ("scenarios/scenario3/input.txt");
  assert (file_handle);
  int row = 0, column = 0;
  
  CountRowColumnFromFilehandle (file_handle, &row, &column);
  DEBUG_IF (row != 100, row);
  TEST (row == 100);
  DEBUG_IF (column != 101, column);
  TEST (column == 101);
  
  file_handle.close();
}

void InstanciateProblemDataFromFilenameTest ()
{
  TEST_TITLE ("CountRowColumnFromFilehandleTest");
  ProblemData *data = NULL;
  data = InstanciateProblemDataFromFilename ("scenarios/scenario1/data");
  
  TEST (data -> GetWidth () == 5);
  TEST (data -> GetLength () == 3);
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
  TEST (data -> GetLength () == 100);
}