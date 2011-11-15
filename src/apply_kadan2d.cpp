#include <cassert>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

#include "debug.h"
#include "coords_maximum_subarray.h"
#include "problem_data.h"
#include "tbb/blocked_range.h"
#include "tbb/cache_aligned_allocator.h"
using namespace tbb;

#include "debug_algorithm.h"
#include "apply_kadan2d.h"

/*!
 * \brief Task to perform as Parallel treatment
 */
void ApplyKadan2d::operator () ( const BlockKadan2d &r)
{
//   cout << "ApplyKadan2d" << endl;
//   DEBUG_IF(1, r.begin());
//   DEBUG_IF(1, r.end());
//   string report_name ("resolve.log");
//   DebugAlgorithm debug (report_name, *(this -> problem_data));
  short *matrice = this -> problem_data -> GetMatrice ();
  int max_value = this -> maxValue;
  int matrice_width = this -> problem_data -> GetWidth();
  int matrice_length = this -> problem_data -> GetHeight();  
  
  for(int borne_gauche_y = r.lower; borne_gauche_y < r.upper; borne_gauche_y++) 
  {  
    vector<int, cache_aligned_allocator<int> > tableau_colonne (matrice_width, 0);
    // Parallelisable à condition de faire sauter le cache
    for(int borne_droite_y = borne_gauche_y; borne_droite_y < matrice_length; borne_droite_y++) 
    {
      int value = 0;
      int borne_gauche_x = 0;
      
      // Non parallelisable (Dependante des calculs precedents)
      for(int borne_droite_x = 0; borne_droite_x < matrice_width; borne_droite_x++) 
      {
        value += (tableau_colonne[borne_droite_x] += matrice [borne_droite_x + borne_droite_y * matrice_width]);
        
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

void ApplyKadan2d::join ( ApplyKadan2d &copy)
{
  //DEBUG_IF (1, "join");
  
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