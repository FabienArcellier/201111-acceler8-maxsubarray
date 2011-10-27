
#include <assert.h>
#include <memory>
#include <new>
#include <iostream>
#include <vector>
#include <list>


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
  list< vector<int> > max_coordinate;
  vector<int> local_max;
  local_max.push_back(0);
  local_max.push_back(0);
  max_coordinate.push_back(local_max);
  
  
  for(int i=1;i<data.GetWidth()*data.GetLength();i++){
    if(matrice[i]>max_value){
      max_value = matrice[i];
      local_max[0] = i%data.GetWidth();
      local_max[1] = (int)(i/data.GetWidth());
      max_coordinate.clear();
      max_coordinate.push_back(local_max);
    }
    else if(matrice[i] == max_value){
      local_max[0] = i%data.GetWidth();
      local_max[1] = (int)(i/data.GetWidth());
      max_coordinate.push_back(local_max);
    }
    if(matrice[i] == 0)
      break;
  }
  list< vector<int> > :: iterator k;
  for(k=max_coordinate.begin();k!=max_coordinate.end();k++){
    this->SetCoordMaximumSubArray((*k)[0],(*k)[1],(*k)[0],(*k)[1]);
  }
}


/** \brief Algorithme de résolution dans le cas d'une matrice à une seule dimension
  */
void OneDimensionMatrix::resolve(ProblemData &data)
{
    /* maximum subarray a[k..l] of a[1..n] */
    short* matrice = data.GetMatrice();
    
    list< vector<int> > max_coordinate;
    vector<int> local_max;
    local_max.push_back(0);
    local_max.push_back(0);
    max_coordinate.push_back(local_max);
    
    
    
    
    int s=1<<31, t = 0, j = 0;
    for (int i=0;i<data.GetLength();i++)
    {
        t = t + matrice[i];
        if (t > s) 
        {
          local_max[0] = j;
          local_max[1] = i;
          max_coordinate.clear();
          max_coordinate.push_back(local_max);
          s = t;
        }
        else if(t==s)
        {
          local_max[0] = j;
          local_max[1] = i;
          max_coordinate.push_back(local_max); 
	}
        if (t < 0)
        {
          t = 0; 
          j = i + 1;
        }
    }
    list< vector<int> > :: iterator k;
  for(k=max_coordinate.begin();k!=max_coordinate.end();k++){
    this->SetCoordMaximumSubArray((*k)[0],0,(*k)[1],0);
  }
}    
    


/** \todo Réaliser l'algorithme de Kadane sur cette fonction en 2D
  */
/** \brief Algorithme de résolution dans le cas d'une matrice à 2 dimensions
  */
void TwoDimensionMatrix::resolve(ProblemData &data)
{
}
