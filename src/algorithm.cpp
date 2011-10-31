
#include <assert.h>
#include <algorithm>
#include <memory>
#include <new>
#include <iostream>
#include <vector>
#include <list>

#include "debug.h"


using namespace std;

#include "problem_data.h"
#include "algorithm.h"
#include "debug_algorithm.h"

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
  else if(data.GetWidth() == 1 || data.GetLength() == 1)
    return new OneDimensionMatrix;
  else
    return new TwoDimensionMatrix;

}


/** \brief Méthodes de la fonction algorithme pour accéder aux attributs privés (Set/Get/Display)
  */
list<vector<int> > * algorithm::GetCoordMaximumSubArray()
{
  return &(this->coord_maximum_subarray);
}


void algorithm::SetCoordMaximumSubArray(int x0, int y0, int x1, int y1)
{
  vector<int> coordonnes;
  coordonnes.push_back(x0);
  coordonnes.push_back(y0);
  coordonnes.push_back(x1);
  coordonnes.push_back(y1);
  this->coord_maximum_subarray.push_back(coordonnes);
}

/*!
 * \brief Vide la file qui contient les resultats pour en mettre des nouveaux
 */
void algorithm::ClearCoordMaximumSubArray ()
{
  this->coord_maximum_subarray.clear ();
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
  this->SetCoordMaximumSubArray(0,0,data.GetWidth()-1,data.GetLength()-1);
}


/** \brief Algorithme de résolution dans le cas d'une matrice totalement négative
  */
void AllNegativeMatrix::resolve(ProblemData &data)
{
  short* matrice = data.GetMatrice();
  
  short max_value = matrice[0];
  this -> SetCoordMaximumSubArray(0,0,0,0);
  int max_coordinate[2] = {0,0};
  
  
  for(int i=1;i<data.GetWidth()*data.GetLength();i++){
    if(matrice[i] > max_value){
      max_value = matrice[i];
      max_coordinate[0] = (int)(i%data.GetLength());
      max_coordinate[1] = (int)(i/data.GetLength());
      
      this -> ClearCoordMaximumSubArray();
      this -> SetCoordMaximumSubArray(max_coordinate[0],max_coordinate[1],max_coordinate[0],max_coordinate[1]);
    }
    else if (matrice[i] == max_value)
    {
      max_coordinate[0] = (int)(i%data.GetLength());
      max_coordinate[1] = (int)(i/data.GetLength());
      this -> SetCoordMaximumSubArray(max_coordinate[0],max_coordinate[1],max_coordinate[0],max_coordinate[1]);
    }
  }
}


/** \brief Algorithme de résolution dans le cas d'une matrice à une seule dimension
  */
void OneDimensionMatrix::resolve(ProblemData &data)
{
    /* maximum subarray a[k..l] of a[1..n] */
    short* matrice = data.GetMatrice();
    int matrice_length = data.GetLength();
    int matrice_width = data.GetWidth();
    int s=1<<31, t = 0, j = 1;
    for (int i=0;i<matrice_length *matrice_width;i++)
    {
        t = t + matrice[i];
        if (t > s) 
        {
          this -> ClearCoordMaximumSubArray();
          if(matrice_width== 1)
            this->SetCoordMaximumSubArray(j,0,i,0);
          else
             this->SetCoordMaximumSubArray(0,j,0,i);
          s = t;
        }
        else if( t==s)
        {
          if(matrice_width == 1)
            this->SetCoordMaximumSubArray(j,0,i,0);
          else
             this->SetCoordMaximumSubArray(0,j,0,i);
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
  int matrice_length = data.GetLength();
  int matrice_width = data.GetWidth();
  
  int max_value = data.GetValue (0, 0);
  this -> SetCoordMaximumSubArray (0, 0, 0, 0);
  
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
          this -> ClearCoordMaximumSubArray ();
          this -> SetCoordMaximumSubArray (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
        }
        else if (value == max_value)
        {
          this -> SetCoordMaximumSubArray (borne_gauche_x, borne_gauche_y, borne_droite_x, borne_droite_y);
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
