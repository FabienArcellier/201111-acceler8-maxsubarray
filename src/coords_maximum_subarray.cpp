using namespace std;
#include <iostream>
#include <vector>
#include <list>

#include "coords_maximum_subarray.h"

CoordsMaximumSubarray::CoordsMaximumSubarray ()
{
  this -> coords = new list<vector<int> > ();
}

CoordsMaximumSubarray::~CoordsMaximumSubarray ()
{
  delete this -> coords;
}

/*!
 * \brief Add the coord of an array
 */
void CoordsMaximumSubarray::Add (int x0, int y0, int x1, int y1)
{
  vector <int> coord (4, 0);
  coord[0] = x0;
  coord[1] = y0;
  coord[2] = x1;
  coord[3] = y1;
  this -> coords -> push_back (coord);
}

/*!
 * \brief Display the result on cout
 */
void CoordsMaximumSubarray::Display ()
{
  list<vector<int> > * max_subarray_bornes = this -> coords;
  
  max_subarray_bornes -> front ();
  std::list<vector<int> >::iterator it = max_subarray_bornes -> begin();
  
  for (; it != max_subarray_bornes -> end(); it++)
  {    
    for (int j = 0; j < 4; j++)
    {
      cout << (*it)[j] << flush;
      if (j < 3)
      {
        cout << " ";
      }
      else
      {
        cout << "\n";
      }
    }
  }
}