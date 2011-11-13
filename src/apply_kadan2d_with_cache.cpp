#include <cassert>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

#include "debug.h"
#include "coords_maximum_subarray.h"
#include "problem_data.h"
#include "cache_problem_data.h"
#include "tbb/blocked_range.h"
using namespace tbb;

#include "debug_algorithm.h"
#include "apply_kadan2d_with_cache.h"

/*!
* \brief Task to perform as Parallel treatment
*/
void ApplyKadan2dWithCache::operator () ( const blocked_range<int> &r)
{
//   cout << "ApplyKadan2dWithCache" << endl;
//   DEBUG_IF(1, r.begin());
//   DEBUG_IF(1, r.end());
//   string report_name ("resolve.log");
//   DebugAlgorithm debug (report_name, *(this -> problem_data));
  CacheProblemData * matrice_cache = this -> cache_problem_data;
  int max_value = this -> maxValue;
  int matrice_width = matrice_cache -> GetWidth();
  int matrice_length = matrice_cache -> GetLength();  
  
  for(int borne_gauche_y = r.begin(); borne_gauche_y < r.end(); borne_gauche_y++) 
  {  
    for(int borne_droite_y = borne_gauche_y; borne_droite_y < matrice_length; borne_droite_y++) 
    {
      int value = 0;
      int borne_gauche_x = 0;
      
      for(int borne_droite_x = 0; borne_droite_x < matrice_width; borne_droite_x++) 
      {
        value += matrice_cache -> GetValue(borne_droite_x, borne_droite_y, borne_gauche_y);
        
//         debug.WriteCoord (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
//         debug.WriteValue (value);
//         debug.WriteMaxValue (max_value);
//         debug.WriteEmptyLine ();
//         debug.WriteMatrice (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
//         debug.WriteEmptyLine ();
                
        if (value > max_value)
        {
          max_value = value;
          this ->  coords_maximum_subarray -> Clear ();
          this ->  coords_maximum_subarray -> Add (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
        }
        else if (value == max_value)
        {
          this ->  coords_maximum_subarray -> Add (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
        }
        else if (value < 0)
        {
//           string text_reset_zero ("Reset value zero");
//           debug.WriteString (text_reset_zero);
          
          value = 0;
          borne_gauche_x = borne_droite_x + 1;
        }
      }
    }
  }
  
  this -> maxValue = max_value;
}

void ApplyKadan2dWithCache::join ( ApplyKadan2dWithCache &copy)
{
  DEBUG_IF (1, copy.GetMaxValue ());
  DEBUG_IF (1, this -> maxValue);
  
  if (this -> maxValue < copy.GetMaxValue ())
  {
    this -> coords_maximum_subarray -> Copy (*(copy.GetCoordsMaximumSubarray()));
    this -> maxValue = copy.GetMaxValue ();
  }
  else if (this -> maxValue == copy.GetMaxValue ())
  {
    this -> coords_maximum_subarray -> Concat (*(copy.GetCoordsMaximumSubarray()));
  }
}