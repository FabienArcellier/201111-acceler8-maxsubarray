#include <assert.h>
#include <fstream>
#include <iostream>
using namespace std;
#include "test.h"
#include "problem_data.h"
#include "main.h"

/* Tests declaration */
void DisplayMaxSubarrayTests ();
void CountRowColumnFromFilehandleTest ();
void InstanciateProblemDataFromFilenameTest ();

int main (void)
{
  DisplayMaxSubarrayTests ();
  CountRowColumnFromFilehandleTest ();
  InstanciateProblemDataFromFilenameTest ();
}

void DisplayMaxSubarrayTests ()
{
  TEST_TITLE ("DisplayMaxSubarrayTests");
  int tab[4] = {4,5,6,7};
  DisplayMaxSubarray (tab);
}

void CountRowColumnFromFilehandleTest ()
{
  TEST_TITLE ("CountRowColumnFromFilehandleTest");
  ifstream file_handle ("scenarios/scenario1/data");
  assert (file_handle);
  int row = 0, column = 0;
  
  CountRowColumnFromFilehandle (file_handle, &row, &column);
  TEST (row == 3);
  TEST (column == 5);
  
  file_handle.close();
}

void InstanciateProblemDataFromFilenameTest ()
{
  TEST_TITLE ("CountRowColumnFromFilehandleTest");
  ProblemData *data = NULL;
  data = InstanciateProblemDataFromFilename ("scenarios/scenario1/data");
  
  TEST (data -> GetWidth () == 3);
  TEST (data -> GetLength () == 5);
  TEST (data -> GetValue (0, 0) == 0);
  cout << "data -> GetValue (2, 4) " << data -> GetValue (2, 4) << '\n';
  TEST (data -> GetValue (2, 4) == 15);
}