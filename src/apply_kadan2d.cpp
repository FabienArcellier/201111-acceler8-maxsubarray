#include <cassert>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

#include "debug.h"
#include "coords_maximum_subarray.h"
#include "problem_data.h"
#include "tbb/parallel_scan.h"
#include "tbb/blocked_range.h"
using namespace tbb;

#include "debug_algorithm.h"
#include "apply_kadan2d.h"

/*!
 * \brief Task to perform as Parallel treatment
 */
void ApplyKadan2d::operator () ( const blocked_range<int> &r)
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
  
  for(int borne_gauche_y = r.begin(); borne_gauche_y < r.end(); borne_gauche_y++) 
  {  
    vector<int> tableau_colonne (matrice_width, 0);
    // Pas parallelisable
    for(int borne_droite_y = borne_gauche_y; borne_droite_y < matrice_length; borne_droite_y++) 
    {
      int borne_gauche_x = 0;
      // Parallel for possible
      for (int borne_droite_x = 0; borne_droite_x < matrice_width; borne_droite_x++)
      {
        tableau_colonne[borne_droite_x] += matrice [borne_droite_x + borne_droite_y * matrice_width];
      }
      
      ApplyKadan2DScan scan(
        borne_gauche_x, 
        borne_gauche_y, 
        borne_droite_y, 
        tableau_colonne,
        max_value);
      
      parallel_scan (blocked_range<int> (0, matrice_width, 100), scan);
      
      if (scan.max_value > max_value)
      {
        max_value = scan.max_value;
        this -> coords_maximum_subarray -> Copy (*(scan.coords_maximum_subarray));
      }
      else if (scan.max_value == max_value)
      {
        this -> coords_maximum_subarray -> Concat (*(scan.coords_maximum_subarray));
      }
    }
  }
  
  this -> maxValue = max_value;
}

void ApplyKadan2d::join ( ApplyKadan2d &copy)
{  
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

template<typename Tag>
void ApplyKadan2DScan::operator () (const blocked_range<int> &scan, Tag)
{
  // Parallel_scan à  partir d'ici
  for(int borne_droite_x = scan.begin(); borne_droite_x < scan.end(); borne_droite_x++) 
  {
    this -> value += this -> tableau_colonne[borne_droite_x];
    
    //         debug.WriteCoord (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
    //         debug.WriteValue (value);
    //         debug.WriteMaxValue (max_value);
    //         debug.WriteEmptyLine ();
    //         debug.WriteMatrice (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
    //         debug.WriteEmptyLine ();
    
    // Traitement au milieu
    if (this -> value < 0)
    {
      //           string text_reset_zero ("Reset value zero");
      //           debug.WriteString (text_reset_zero);
      
      this -> value = 0;
      this -> borne_gauche_x = borne_droite_x + 1;
    }
    
    // Traitement si final
    if (Tag::is_final_scan ())
    {
      if (value > max_value)
      {
        max_value = value;
        this ->  coords_maximum_subarray -> Clear ();
        this ->  coords_maximum_subarray -> Add (
           this -> borne_gauche_x, 
           this -> borne_gauche_y, 
           borne_droite_x, 
           this -> borne_droite_y);
      }
      else if (value == max_value)
      {
        this ->  coords_maximum_subarray -> Add (
          this -> borne_gauche_x, 
          this -> borne_gauche_y, 
          borne_droite_x, 
          this -> borne_droite_y);
      }
    }
  }
}

void ApplyKadan2DScan::reverse_join (ApplyKadan2DScan &scan)
{
  this -> value += scan.value;
  this -> borne_gauche_x += scan.borne_gauche_x;
  
  if (this -> max_value < scan.max_value)
  {
    this -> max_value = scan.max_value;
    this -> coords_maximum_subarray -> Copy (*(scan.coords_maximum_subarray));
  }
  else if (this -> max_value == scan.max_value)
  {
    this -> coords_maximum_subarray -> Concat (*(scan.coords_maximum_subarray));
  }
}