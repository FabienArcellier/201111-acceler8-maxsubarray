using namespace std;
#include <cassert>
#include "test.h"
#include "debug.h"
#include <iostream>
#include <list>
#include <vector>

#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
using namespace tbb;

#include "coords_maximum_subarray.h"
#include "problem_data.h"
#include "apply_kadan2d.h"
#include "algorithm.h"

/* Tests declaration */
void AlgorithmResolvePositiveMatrix ();
void AlgorithmResolveNegativeMatrix ();
void AlgorithmResolve1DMatrix();
void AlgorithmResolveMultiNegativeMatrice ();
void AlgorithmResolve2DMatrix();
void AlgorithmResolve2DMatrixMultiSolution();

int main (void)
{
  AlgorithmResolvePositiveMatrix ();
  AlgorithmResolveNegativeMatrix ();
  AlgorithmResolve1DMatrix();
  AlgorithmResolveMultiNegativeMatrice ();
  AlgorithmResolve2DMatrix();
  AlgorithmResolve2DMatrixMultiSolution();
  return 0;
}


void AlgorithmResolvePositiveMatrix ()
{
  TEST_TITLE ("AlgorithmResolvePositiveMatrix");
  ProblemData data(5, 5);

  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      data.SetValue (i, j, 2);
    }
  }

  algorithm* testAlgorithme = NULL;
  testAlgorithme = SelectAlgorithm (data);
  testAlgorithme -> resolve(data);
  CoordsMaximumSubarray* tableautest = testAlgorithme -> GetCoordsMaximumSubarray();
  list< vector<int> *> :: iterator it = tableautest -> GetIterator ();
  TEST((**it)[0] == 0);
  TEST((**it)[2] == 4);
  tableautest = NULL;
  delete testAlgorithme;
}

void AlgorithmResolveNegativeMatrix ()
{
  TEST_TITLE ("AlgorithmResolveNegativeMatrix");
  ProblemData data(5, 5);
  
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      data.SetValue (i, j, i+j-40);
    }
  }
  
  algorithm* testAlgorithme = NULL;
  testAlgorithme = SelectAlgorithm (data);
  testAlgorithme -> resolve(data);
  CoordsMaximumSubarray* tableautest = testAlgorithme -> GetCoordsMaximumSubarray();
  list< vector<int> *> :: iterator it = tableautest -> GetIterator ();
  TEST((**it)[0] == 4);
  TEST((**it)[2] == 4); 
}


void AlgorithmResolve1DMatrix()
{
  TEST_TITLE ("AlgorithmResolve1DMatrix");
  ProblemData data(1, 10);
  
  for (int i = 0; i < 10; i++)
  {
      data.SetValue (0, i, -4+i); 
  }
  
  algorithm* testAlgorithme = NULL;
  testAlgorithme  = SelectAlgorithm (data);
  testAlgorithme->resolve(data);
  CoordsMaximumSubarray* tableautest = testAlgorithme->GetCoordsMaximumSubarray();
  list< vector<int> *> :: iterator it = tableautest -> GetIterator ();
  TEST((**it)[0] == 4);
  TEST((**it)[2] == 9);

}

void AlgorithmResolveMultiNegativeMatrice ()
{
  TEST_TITLE ("AlgorithmResolveMultiNegativeMatrice");
  ProblemData data(5, 5);
  
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      data.SetValue (i, j, -3);
    }
  }
  
  data.SetValue (0, 0, -1);
  data.SetValue (2, 2, -1);
  
  algorithm* testAlgorithme = NULL;
  testAlgorithme  = SelectAlgorithm (data);
  testAlgorithme->resolve(data);
  CoordsMaximumSubarray* tableautest = testAlgorithme->GetCoordsMaximumSubarray();
  
  DEBUG_IF (!(tableautest -> Count() == 2), tableautest -> Count());
  TEST (tableautest -> Count() == 2);
  
}

void AlgorithmResolve2DMatrix()
{
  TEST_TITLE ("AlgorithmResolve2DMatrix");
  task_scheduler_init init_tbb (10);
  ProblemData data(5, 5);
  
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      data.SetValue (i, j, -3);
    }
  }
  
  data.SetValue (1, 1, 4);
  data.SetValue (1, 2, 4);
  data.SetValue (2, 1, 4);
  data.SetValue (2, 2, 4);
  
  algorithm* testAlgorithme = NULL;
  testAlgorithme  = SelectAlgorithm (data);
  testAlgorithme->resolve(data);
  
  CoordsMaximumSubarray* tableautest = testAlgorithme -> GetCoordsMaximumSubarray();
  
  tableautest -> Display();
  DEBUG_IF (!(tableautest -> Count() == 1), tableautest -> Count());
  TEST (tableautest -> Count() == 1);
  
  list< vector<int> *> :: iterator it = tableautest -> GetIterator ();
  
  DEBUG_IF (!((**it)[0] == 1), (**it)[0]);
  TEST((**it)[0] == 1);
  
  DEBUG_IF (!((**it)[1] == 1), (**it)[1]);
  TEST((**it)[1] == 1);
  
  DEBUG_IF (!((**it)[2] == 2), (**it)[2]);
  TEST((**it)[2] == 2);
  
  DEBUG_IF (!((**it)[3] == 2), (**it)[3]);
  TEST((**it)[3] == 2);
}

void AlgorithmResolve2DMatrixMultiSolution()
{
  TEST_TITLE ("AlgorithmResolve2DMatrixMultiSolution");
  task_scheduler_init init_tbb (10);
  ProblemData data(5, 7);
  
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      data.SetValue (i, j, -6);
    }
  }
  
  data.SetValue (1, 1, 4);
  data.SetValue (1, 2, 4);
  data.SetValue (3, 1, 4);
  data.SetValue (3, 2, 4);
  
  algorithm* testAlgorithme = NULL;
  testAlgorithme  = SelectAlgorithm (data);
  testAlgorithme->resolve(data);
  
  CoordsMaximumSubarray* tableautest = testAlgorithme->GetCoordsMaximumSubarray();
  DEBUG_IF (!(tableautest -> Count() == 2), tableautest -> Count());
  TEST (tableautest -> Count() == 2);
  
  list< vector<int> *> :: iterator it = tableautest -> GetIterator ();
  
  DEBUG_IF (!((**it)[0] == 1), (**it)[0]);
  TEST((**it)[0] == 1);
  
  DEBUG_IF (!((**it)[1] == 1), (**it)[1]);
  TEST(((**it)[1] == 1));
  
  DEBUG_IF (!((**it)[2] == 1), (**it)[2]);
  TEST((**it)[2] == 1);
  
  DEBUG_IF (!((**it)[3] == 2), (**it)[3]);
  TEST((**it)[3] == 2);
  
  it++;
  TEST((**it)[0] == 3);
  TEST((**it)[1] == 1);
  TEST((**it)[2] == 3);
  TEST((**it)[3] == 2);
  
  
}