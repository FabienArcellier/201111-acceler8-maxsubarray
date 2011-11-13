
#include <assert.h>
#include <algorithm>
#include <memory>
#include <new>
#include <iostream>
#include <vector>
#include <list>
#include "debug.h"

using namespace std;

#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"

using namespace tbb;

#include "problem_data.h"
#include "cache_problem_data.h"
#include "coords_maximum_subarray.h"
#include "apply_kadan2d.h"
#include "apply_kadan2d_with_cache.h"
#include "algorithm.h"
#include "debug_algorithm.h"

algorithm::algorithm ()
{
  this -> coord_maximum_subarray = new CoordsMaximumSubarray ();
}

algorithm::~algorithm ()
{
  delete this -> coord_maximum_subarray;
}

/** \brief Selection de l'algorithme en fonction de la composition de la matrice - Peut etre amené à évoluer après benchmarck
  */
algorithm* SelectAlgorithm (ProblemData& data)
{
  if(data.ContainOnlyPositiveNumbers() == 1)
	return new AllPositiveMatrix;
  else if(data.ContainOnlyNegativeNumbers() == 1)
    return new AllNegativeMatrix;
  /** \todo Vérifier si la longueur/largeur commence à zéro ou à un
    */  
  else if(data.GetWidth() == 1 || data.GetHeight() == 1)
    return new OneDimensionMatrix;
  else
  {
//     return new TwoDimensionMatrix;
//     return new TwoDimensionMatrixParallel;
//     return new TwoDimensionMatrixWithCache;
    return new TwoDimensionMatrixParallelWithCache;
  }
}

/** \brief Méthodes de la fonction algorithme pour accéder aux attributs privés (Set/Get/Display)
  */
CoordsMaximumSubarray * algorithm::GetCoordsMaximumSubarray()
{
  return this -> coord_maximum_subarray;
}


void algorithm::SetCoordsMaximumSubarray(int x0, int y0, int x1, int y1)
{
  (this -> coord_maximum_subarray) -> Add (x0, y0, x1, y1);
}

/*!
 * \brief Vide la file qui contient les resultats pour en mettre des nouveaux
 */
void algorithm::ClearCoordsMaximumSubarray ()
{
  (this->coord_maximum_subarray) -> ClearDestroy ();
}


short algorithm::GetWorkerThreads()
{
  return this->WorkerThreads;
}

void algorithm::SetWorkerThreads(short threads_quantity)
{
  this->WorkerThreads = threads_quantity;
}

/** \brief Algorithme de résolution dans le cas d'une matrice totalement positive
  */
void AllPositiveMatrix::resolve(ProblemData &data)
{
  this->SetCoordsMaximumSubarray(0,0,data.GetWidth()-1,data.GetHeight()-1);
}


/** \brief Algorithme de résolution dans le cas d'une matrice totalement négative
  */
void AllNegativeMatrix::resolve(ProblemData &data)
{
  short* matrice = data.GetMatrice();

  short max_value = matrice[0];
  this -> SetCoordsMaximumSubarray(0,0,0,0);
  int max_coordinate[2] = {0,0};

  
  for(int i=1;i<data.GetWidth()*data.GetHeight();i++){
    if(matrice[i] > max_value){
      max_value = matrice[i];
      max_coordinate[0] = (int)(i%data.GetHeight());
      max_coordinate[1] = (int)(i/data.GetHeight());
      
      this -> ClearCoordsMaximumSubarray();
      this -> SetCoordsMaximumSubarray(max_coordinate[0],max_coordinate[1],max_coordinate[0],max_coordinate[1]);
    }
    else if (matrice[i] == max_value)
    {
      max_coordinate[0] = (int)(i%data.GetHeight());
      max_coordinate[1] = (int)(i/data.GetHeight());
      
      this -> SetCoordsMaximumSubarray(max_coordinate[0],max_coordinate[1],max_coordinate[0],max_coordinate[1]);
    }
  }
}


/** \brief Algorithme de résolution dans le cas d'une matrice à une seule dimension
  */
void OneDimensionMatrix::resolve(ProblemData &data)
{
    /* maximum subarray a[k..l] of a[1..n] */
    short* matrice = data.GetMatrice();
    int matrice_length = data.GetHeight();
    int matrice_width = data.GetWidth();
    int s=1<<31, t = 0, j = 1;
    for (int i=0;i<matrice_length *matrice_width;i++)
    {
        t = t + matrice[i];
        if (t > s) 
        {
          this -> ClearCoordsMaximumSubarray();
          if(matrice_width== 1)
            this->SetCoordsMaximumSubarray(j,0,i,0);
          else
             this->SetCoordsMaximumSubarray(0,j,0,i);
          s = t;
        }
        else if( t==s)
        {
          if(matrice_width == 1)
            this->SetCoordsMaximumSubarray(j,0,i,0);
          else
             this->SetCoordsMaximumSubarray(0,j,0,i);
        }
        if (t < 0)
        {
          t = 0; 
          j = i + 1;
        }
    }
    
}    
    


/** \todo Réaliser l'algorithme de Kadane sur cette fonction en 2D
  */
/** \brief Algorithme de résolution dans le cas d'une matrice à 2 dimensions
  */
void TwoDimensionMatrix::resolve(ProblemData &data)
{
//   string report_name ("resolve.log");
//   DebugAlgorithm debug (report_name, data);
  short *matrice = data.GetMatrice ();
  int matrice_length = data.GetHeight();
  int matrice_width = data.GetWidth();
  
  int max_value = data.GetValue (0, 0);
  this -> SetCoordsMaximumSubarray (0, 0, 0, 0);
  
  // Parallelisable
  for(int borne_gauche_y = 0; borne_gauche_y < matrice_length; borne_gauche_y++) 
  {
    vector<int> tableau_colonne (matrice_width, 0);
    
    // Parallelisable à condition de faire sauter le cache
    for(int borne_droite_y = borne_gauche_y  ; borne_droite_y < matrice_length; borne_droite_y++) 
    {
      int value = 0;
      int borne_gauche_x = 0;
      
      // Non parallelisable (Dependante des calculs precedents)
      for(int borne_droite_x = 0; borne_droite_x < matrice_width; borne_droite_x++) 
      {
        tableau_colonne[borne_droite_x] += matrice [borne_droite_x + borne_droite_y * matrice_width];
        value += tableau_colonne[borne_droite_x];
        
//         debug.WriteCoord (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
//         debug.WriteValue (value);
//         debug.WriteMaxValue (max_value);
//         debug.WriteEmptyLine ();
//         debug.WriteMatrice (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
//         debug.WriteEmptyLine ();
//         
        if (value > max_value)
        {
          max_value = value;
          this -> ClearCoordsMaximumSubarray ();
          this -> SetCoordsMaximumSubarray (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
        }
        else if (value == max_value)
        {
          this -> SetCoordsMaximumSubarray (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
        }
        else if (value < 0)
        {
          value = 0;
          borne_gauche_x = borne_droite_x + 1;
        }
      }
    }
  }
  
//   DEBUG_IF (1, max_value);
}

void TwoDimensionMatrixWithCache::resolve(ProblemData &data)
{
//   string report_name ("resolve.log");
//   DebugAlgorithm debug (report_name, data);
  int matrice_length = data.GetHeight();
  int matrice_width = data.GetWidth();
  
  int max_value = data.GetValue (0, 0);
  this -> SetCoordsMaximumSubarray (0, 0, 0, 0);
  
  
  CacheProblemData matrice_cache(data);
  // Parallelisable
  for(int borne_gauche_y = 0; borne_gauche_y < matrice_length; borne_gauche_y++) 
  {   
    
    // Parallelisable à condition de faire sauter le cache
    for(int borne_droite_y = borne_gauche_y  ; borne_droite_y < matrice_length; borne_droite_y++) 
    {
      int value = 0;
      int borne_gauche_x = 0;
      
      // Non parallelisable (Dependante des calculs precedents)
      for(int borne_droite_x = 0; borne_droite_x < matrice_width; borne_droite_x++) 
      {
        value += matrice_cache.GetValue(borne_droite_x, borne_droite_y, borne_gauche_y);
//         debug.WriteCoord (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
//         debug.WriteValue (value);
//         debug.WriteMaxValue (max_value);
//         debug.WriteEmptyLine ();
//         debug.WriteMatrice (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
//         debug.WriteEmptyLine ();
        
        if (value > max_value)
        {
          max_value = value;
          this -> ClearCoordsMaximumSubarray ();
          this -> SetCoordsMaximumSubarray (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
        }
        else if (value == max_value)
        {
          this -> SetCoordsMaximumSubarray (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
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
  DEBUG_IF (1, max_value);
}

void TwoDimensionMatrixParallel::resolve(ProblemData &data)
{
  int matrice_width = data.GetWidth();
  int Grain = (matrice_width / this -> WorkerThreads) + 1;
  
//   DEBUG_IF (1, matrice_width);
  ApplyKadan2d kadan = ApplyKadan2d (&data);
  
  parallel_reduce (blocked_range<int> (0, matrice_width, Grain), kadan);
  
  this -> coord_maximum_subarray -> Copy (*(kadan.GetCoordsMaximumSubarray()));
}

void TwoDimensionMatrixParallelWithCache::resolve(ProblemData &data)
{
  int matrice_width = data.GetWidth();
  int Grain = 100;
  CacheProblemData matrice_cache(data);
  
  //   DEBUG_IF (1, matrice_width);
  ApplyKadan2dWithCache kadan = ApplyKadan2dWithCache (&matrice_cache);
  parallel_reduce (blocked_range<int> (0, matrice_width, Grain), kadan);
  
  this -> coord_maximum_subarray -> Copy (*(kadan.GetCoordsMaximumSubarray()));
}


