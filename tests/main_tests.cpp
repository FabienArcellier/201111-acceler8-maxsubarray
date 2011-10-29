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

int main (void)
{
  DisplayMaxSubarrayTests ();
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