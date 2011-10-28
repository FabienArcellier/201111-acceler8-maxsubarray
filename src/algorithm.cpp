
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
  else if(data.GetWidth() == 1)
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
  this->SetCoordMaximumSubArray(0,0,data.GetLength()-1,data.GetWidth()-1);
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
      max_coordinate[0] = i - (int)(((i-1)/data.GetLength())*data.GetLength());
      max_coordinate[1] = (int)(i/data.GetLength());
      
      this -> ClearCoordMaximumSubArray();
      this -> SetCoordMaximumSubArray(max_coordinate[0],max_coordinate[1],max_coordinate[0],max_coordinate[1]);
    }
    else if (matrice[i] == max_value)
    {
      max_coordinate[0] = i - (int)(((i-1)/data.GetLength())*data.GetLength());
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
    int max_coordinate[2] = {0,0};
    short* matrice = data.GetMatrice();
    int s=1<<31, t = 0, j = 1;
    for (int i=0;i<data.GetLength();i++)
    {
        t = t + matrice[i];
        if (t > s) 
        {
          max_coordinate[0] = j;
          max_coordinate[1] = i;
          s = t;
        }
        if (t < 0)
        {
          t = 0; 
          j = i + 1;
        }
    }
    this->SetCoordMaximumSubArray(max_coordinate[0],0,max_coordinate[1],0);
    
}    
    


/** \todo Réaliser l'algorithme de Kadane sur cette fonction en 2D
  */
/** \brief Algorithme de résolution dans le cas d'une matrice à 2 dimensions
  */
void TwoDimensionMatrix::resolve(ProblemData &data)
{
  int max_value = data.GetValue (0, 0);
  this -> SetCoordMaximumSubArray (0, 0, 0, 0);
  
  for(int borne_gauche_x = 0; borne_gauche_x < data.GetWidth(); borne_gauche_x++) 
  {
    vector<int> tableau_colonne (data.GetLength(), 0);
    
    for(int borne_droite_x = borne_gauche_x  ; borne_droite_x < data.GetWidth(); borne_droite_x++) 
    {
      int value = 0;
      int current_row_y_low = 0;
      int borne_gauche_y = 0;
      int borne_droite_y = 0;
      for(int current_row_y_high = 0; current_row_y_high < data.GetLength(); current_row_y_high++) 
      {
        tableau_colonne[current_row_y_high] += data.GetValue (current_row_y_high, borne_droite_x);
        value += tableau_colonne[current_row_y_high];
        
        if (value > max_value)
        {
          max_value = value;
          borne_gauche_y = current_row_y_low;
          borne_droite_y = current_row_y_high;
          this -> ClearCoordMaximumSubArray ();
          this -> SetCoordMaximumSubArray (borne_gauche_y, borne_gauche_x, borne_droite_y, borne_droite_x);
        }
        else if (value == max_value)
        {
          borne_gauche_y = current_row_y_low;
          borne_droite_y = current_row_y_high;
          this -> SetCoordMaximumSubArray (borne_gauche_y, borne_gauche_x, borne_droite_y, borne_droite_x);
        }
        else if (value < 0)
        {
          value = 0;
          current_row_y_low = current_row_y_high + 1;
        }
      }
    }
  }
}
