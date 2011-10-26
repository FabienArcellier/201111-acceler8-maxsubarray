#include "test.h"
#include "problem_data.h"
#include "algorithm.h"


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
  testAlgorithme->resolve(data,1);
  int* tableautest = testAlgorithme->GetCoordMaximumSubArray();
  TEST(tableautest[0] == 0);
  TEST(tableautest[2] == 4);
  
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
  testAlgorithme->resolve(data,1);
  int* tableautest = testAlgorithme->GetCoordMaximumSubArray();
  TEST(tableautest[2] == 4);
  
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
  testAlgorithme->resolve(data,1);
  int* tableautest = testAlgorithme->GetCoordMaximumSubArray();
  TEST(tableautest[0] == 4);
  TEST(tableautest[2] == 9);
}
