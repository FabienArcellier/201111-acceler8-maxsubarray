using namespace std;
#include <cassert>
#include "test.h"
#include "debug.h"
#include <iostream>
#include <vector>
#include <list>

#include "coords_maximum_subarray.h"

/* Prototypes des fonctions de tests */
void AddTests ();
void DisplayTests ();
void ClearDestroyTest ();
void CopyTest ();
void ConcatTest ();

int main (void)
{
  AddTests ();
  DisplayTests ();
  ClearDestroyTest ();
  CopyTest ();
  ConcatTest ();
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
  TEST (coords.Count () == 2);
  list<vector<int> *>::iterator it = coords.GetIterator ();
  
  vector<int> vecteur = **it;
  TEST (vecteur [0] == 0);
  TEST (vecteur [1] == 0);
  TEST (vecteur [2] == 1);
  TEST (vecteur [3] == 1);
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

void ClearDestroyTest ()
{
  TEST_TITLE ("CoordsMaximumSubarray::ClearDestroyTest (must not crashed)");
  // Assignation
  CoordsMaximumSubarray coords;
  
  // Action
  coords.Add (0, 0, 1, 1);
  coords.Add (1, 1, 2, 2);
  
  // Assertion
  coords.ClearDestroy ();
}

void CopyTest ()
{
  TEST_TITLE ("CoordsMaximumSubarray::CopyTest");
  // Assignation
  CoordsMaximumSubarray coords;
  CoordsMaximumSubarray coords2;
  // Action
  coords.Add (0, 0, 1, 1);
  
  coords2.Add (2, 0, 1, 1);
  coords2.Add (1, 1, 2, 2);
  coords2.Add (3, 1, 4, 2);
  
  // Assertion
  coords.Copy (coords2);
  TEST (coords.Count () == 3);
  list<vector<int> *>::iterator it = coords.GetIterator ();
  
  TEST ((**it)[0] == 2);
  it++;
  TEST ((**it)[0] == 1);
  it++;
  TEST ((**it)[0] == 3);
}

void ConcatTest ()
{
  TEST_TITLE ("CoordsMaximumSubarray::ConcatTest");
  // Assignation
  CoordsMaximumSubarray coords;
  CoordsMaximumSubarray coords2;
  // Action
  coords.Add (0, 0, 1, 1);
  
  coords2.Add (2, 0, 1, 1);
  coords2.Add (1, 1, 2, 2);
  coords2.Add (3, 1, 4, 2);
  
  // Assertion
  coords.Concat (coords2);
  TEST (coords.Count () == 4);
  list<vector<int> *>::iterator it = coords.GetIterator ();
  
  TEST ((**it)[0] == 0);
  it++;
  TEST ((**it)[0] == 2);
  it++;
  TEST ((**it)[0] == 1);
  it++;
  TEST ((**it)[0] == 3);
}