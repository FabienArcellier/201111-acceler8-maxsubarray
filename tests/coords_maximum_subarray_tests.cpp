using namespace std;

#include "test.h"
#include "debug.h"
#include <iostream>
#include <vector>
#include <list>

#include "coords_maximum_subarray.h"

/* Prototypes des fonctions de tests */
void AddTests ();
void DisplayTests ();

int main (void)
{
  AddTests ();
  DisplayTests ();
}

void AddTests ()
{
  TEST_TITLE ("CoordsMaximumSubarray::AddTests");
  
  // Assignation
  CoordsMaximumSubarray coords;
  
  // Action
  coords.Add (0, 0, 1, 1);
  coords.Add (1, 1, 2, 2);
  
  // Assertion
  list<vector<int> > * list_vector_coords = coords.Get ();
  
  TEST (list_vector_coords -> size () == 2);
  list<vector<int> >::iterator it = list_vector_coords -> begin ();
  TEST ((*it) [0] == 0);
  TEST ((*it) [1] == 0);
  TEST ((*it) [2] == 1);
  TEST ((*it) [3] == 1);
}

void DisplayTests ()
{
  TEST_TITLE ("CoordsMaximumSubarray::DisplayTests (manual checking)");
  // Assignation
  CoordsMaximumSubarray coords;
  
  // Action
  coords.Add (0, 0, 1, 1);
  coords.Add (1, 1, 2, 2);
  
  // Assertion
  coords.Display ();
}