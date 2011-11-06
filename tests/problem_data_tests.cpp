#include <cassert>
#include <iostream>
#include "test.h"
#include "problem_data.h"

using namespace std;

/* Tests declaration */
void ProblemDataWithOnlyPositiveValuesTest ();
void ProblemDataWithOnlyNegativeValuesTest ();
void ProblemDataWithBothValuesTest ();

int main (void)
{
  ProblemDataWithOnlyPositiveValuesTest ();
  ProblemDataWithOnlyNegativeValuesTest ();
  ProblemDataWithBothValuesTest ();
}

void ProblemDataWithOnlyPositiveValuesTest ()
{
  TEST_TITLE ("ProblemDataWithOnlyPositiveValuesTest");
  ProblemData data(5, 5);
  
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      data.SetValue (i, j, 2);
    }
  }

  TEST (data.ContainOnlyPositiveNumbers() == 1);
  TEST (data.ContainOnlyNegativeNumbers() == 0);
}

void ProblemDataWithOnlyNegativeValuesTest ()
{
  TEST_TITLE ("ProblemDataWithOnlyNegativeValuesTest");
  ProblemData data1(5, 5);
  
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      data1.SetValue (i, j, -2);
    }
  }
  
  TEST (data1.ContainOnlyPositiveNumbers() == 0);
  TEST (data1.ContainOnlyNegativeNumbers() == 1);
}

void ProblemDataWithBothValuesTest ()
{
  TEST_TITLE ("ProblemDataWithBothValuesTest");
  ProblemData data2(5, 5);
  
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      data2.SetValue (i, j, j - 2);
    }
  }
  
  TEST (data2.GetValue(0, 0) == -2);
  TEST (data2.GetValue(0, 1) == -1);
  TEST (data2.GetValue(1, 2) == 0);
  TEST (data2.GetValue(2, 2) == 0);
  TEST (data2.ContainOnlyPositiveNumbers() == 0);
  TEST (data2.ContainOnlyNegativeNumbers() == 0);
}