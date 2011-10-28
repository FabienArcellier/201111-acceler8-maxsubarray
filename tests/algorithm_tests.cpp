#include "test.h"
#include "problem_data.h"
#include "algorithm.h"
#include <iostream>

/* Tests declaration */
void AlgorithmResolvePositiveMatrix ();
void AlgorithmResolveNegativeMatrix ();
void AlgorithmResolve1DMatrix();
void AlgorithmResolveMultiNegativeMatrice ();

int main (void)
{
  AlgorithmResolvePositiveMatrix ();
  AlgorithmResolveNegativeMatrix ();
  AlgorithmResolve1DMatrix();
  AlgorithmResolveMultiNegativeMatrice ();
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
  cout <<  (*test_value)[2] << endl;
  
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
  testAlgorithme  = SelectAlgorithm (data);
  testAlgorithme->resolve(data);
  list< vector<int> > * tableautest = testAlgorithme->GetCoordMaximumSubArray();
  list< vector<int> > :: iterator test_value;
  test_value = (*tableautest).begin();
  TEST((*test_value)[2] == 4);
  TEST((*test_value)[0] == 4);
  
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
  list< vector<int> > * tableautest = testAlgorithme->GetCoordMaximumSubArray();
  list< vector<int> > :: iterator test_value;
  test_value = (*tableautest).begin();
  TEST((*test_value)[0] == 4);
  TEST((*test_value)[2] == 9);
  cout << (*test_value)[2]  << endl;
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
  list< vector<int> > * tableautest = testAlgorithme->GetCoordMaximumSubArray();
  TEST (tableautest -> size() == 2);
  
}