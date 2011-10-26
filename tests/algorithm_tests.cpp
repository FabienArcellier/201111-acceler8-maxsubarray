#include "test.h"
#include "problem_data.h"
#include "algorithm.h"


/* Tests declaration */
void AlgorithmResolvePositiveMatrix ();
void AlgorithmResolveNegativeMatrix ();

int main (void)
{
  AlgorithmResolvePositiveMatrix ();
  AlgorithmResolveNegativeMatrix ();
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
  TEST(tableautest[2] == 4)
  
}
