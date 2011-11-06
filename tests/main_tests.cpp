#include <assert.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
using namespace std;
#include "coords_maximum_subarray.h"
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

  CoordsMaximumSubarray coords;
  coords.Add (4, 5, 6, 7);
  coords.Add (4, 5, 6, 7);
  coords.Add (4, 5, 6, 7);
  DisplayMaxSubarray (coords);
}