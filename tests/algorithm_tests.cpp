#include "test.h"
#include "problem_data.h"
#include "algorithm.h"
#include <iostream>

/* Tests declaration */
void AlgorithmResolvePositiveMatrix ();
void AlgorithmResolveNegativeMatrix ();
void AlgorithmResolve1DMatrix();

int main (void)
{
  AlgorithmResolvePositiveMatrix ();
  AlgorithmResolveNegativeMatrix ();
  AlgorithmResolve1DMatrix();
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
  testAlgorithme  = SelectAlgorithm (data);
  testAlgorithme->resolve(data);
  list< vector<int> > * tableautest = testAlgorithme->GetCoordMaximumSubArray();
  list< vector<int> > :: iterator test_value;
  test_value = (*tableautest).begin();
  TEST((*test_value)[0] == 0);
  TEST((*test_value)[2] == 4);
  
}

void AlgorithmResolveNegativeMatrix ()
{
  TEST_TITLE ("AlgorithmResolveNegativeMatrix");
  ProblemData data(5, 5);
   for (int j = 0; j < 5; j++)
    {
      data.SetValue (0, j, -5);
    }
  
  for (int i = 1; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      data.SetValue (i, j, -1);
    }
  }
  
  algorithm* testAlgorithme = NULL;
  testAlgorithme  = SelectAlgorithm (data);
  testAlgorithme->resolve(data);
  list< vector<int> > * tableautest = testAlgorithme->GetCoordMaximumSubArray();
  list< vector<int> > :: iterator test_value;
  test_value = (*tableautest).begin();
  TEST((*test_value)[2] == 1);
  TEST((*test_value)[1] == 0);
  test_value++;
  TEST((*test_value)[2] == 2);
  TEST((*test_value)[1] == 0);
  
}


void AlgorithmResolve1DMatrix()
{
  TEST_TITLE ("AlgorithmResolve1DMatrix");
  ProblemData data(1, 10);
  data.SetValue (0, 0, 100);
  for (int i = 1; i < 5; i++)
  {
      data.SetValue (0, i, -400+i); 
  }
  data.SetValue (0, 5, 100);
  for (int i = 6; i < 10; i++)
  {
      data.SetValue (0, i, -400+i); 
  }
  algorithm* testAlgorithme = NULL;
  testAlgorithme  = SelectAlgorithm (data);
  testAlgorithme->resolve(data);
  list< vector<int> > * tableautest = testAlgorithme->GetCoordMaximumSubArray();
  list< vector<int> > :: iterator test_value;
  test_value = (*tableautest).begin();
  TEST((*test_value)[0] == 0);
  TEST((*test_value)[2] == 0);
  test_value++;
  TEST((*test_value)[2] == 5);
  TEST((*test_value)[0] == 5);
}
