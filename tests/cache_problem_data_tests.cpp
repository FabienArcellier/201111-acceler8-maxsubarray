using namespace std;
#include <iostream>
#include "test.h"
#include "debug.h"
#include "problem_data.h"
#include "cache_problem_data.h"

void CacheProblemDataGetValue();
void CacheProblemDataGetValueSoustraction();

int main(void)
{
  CacheProblemDataGetValue();
  
}

void CacheProblemDataGetValue()
{
  TEST_TITLE ("CacheProblemDataGetValue");
  ProblemData data(4,4);
  int k=1;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      data.SetValue (j,i, k++);
    }
  }
  CacheProblemData cachedata(data);
  TEST(cachedata.GetValue(0,0) == 0);
  TEST(cachedata.GetValue(2,2) == 19);
} 

void CacheProblemDataGetValueSoustraction()
{
  TEST_TITLE ("CacheProblemDataGetValueSoustraction");
  ProblemData data(4,4);
  int k=1;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      data.SetValue (j,i, k++);
    }
  }
  CacheProblemData cachedata(data);
  TEST(cachedata.GetValue(0,3,0) == 6);
  TEST(cachedata.GetValue(2,4,2) == 23);  
  
}