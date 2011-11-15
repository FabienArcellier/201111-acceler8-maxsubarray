using namespace std;
#include <cassert>
#include "test.h"
#include "debug.h"
#include <iostream>
#include "problem_data.h"
#include "verif.h"

/* Prototype des fonctions de tests */
void CalculateMaxValueTests ();

int main (void)
{
  CalculateMaxValueTests ();
}

void CalculateMaxValueTests ()
{
  TEST_TITLE ("CalculateMaxValueTests");
  
  // Assignation
  char **tab;
  tab = (char **) new int[4];
  for (int i = 0; i < 4; i++)
  {
    tab[i] = new char(255);
  }
  strcpy (tab[0], "1");
  strcpy (tab[1], "1");
  strcpy (tab[2], "2");
  strcpy (tab[3], "2");
  
  
  ProblemData data (5, 7);
  
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      data.SetValue (i, j, 5);
    }
  }
  
  // Action
  int result = CalculateMaxValue (data, tab);
  
  // Assertion
  DEBUG_IF (result != 20, result);
  TEST (result == 20);
}