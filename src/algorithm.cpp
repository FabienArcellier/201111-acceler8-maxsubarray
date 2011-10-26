
#include <assert.h>
#include <memory>
#include <new>
#include <iostream>

#include "problem_data.h"
#include "algorithm.h"



using namespace std;


/** \brief Selection de l'algorithme en fonction de la composition de la matrice - Peut etre amen� � �voluer apr�s benchmarck
  */
algorithm* SelectAlgorithm (ProblemData& data)
{
  if(data.ContainOnlyPositiveNumbers() == 1)
	return new AllPositiveMatrix;
  else if(data.ContainOnlyNegativeNumbers() == 1)
    return new AllNegativeMatrix;
  /** \todo V�rifier si la longueur/largeur commence � z�ro ou � un
    */  
  else if(data.GetWidth() == 0)
    return new OneDimensionMatrix;
  else
    return new TwoDimensionMatrix;

}


/** \brief M�thodes de la fonction algorithme pour acc�der aux attributs priv�s (Set/Get/Display)
  */
int* algorithm::GetCoordMaximumSubArray()
{
  return this->coord_maximum_subarray;
}


void algorithm::SetCoordMaximumSubArray(int x0, int y0, int x1, int y1)
{
  this->coord_maximum_subarray[0] = x0;
  this->coord_maximum_subarray[1] = y0;
  this->coord_maximum_subarray[2] = x1;
  this->coord_maximum_subarray[3] = y1;
}

void algorithm::AfficherMaximumSubArray()
{
  if(this->coord_maximum_subarray)
  {
	for(int i=0;i<4;i++)
		cout << this->coord_maximum_subarray[i] << " ";
	cout << endl;
  }
}

short algorithm::GetWorkerThreads()
{
  return this->WorkerThreads;
}

void algorithm::SetWorkerThreads(short threads_quantity)
{
  this->WorkerThreads = threads_quantity;
}




/** \brief Algorithme de r�solution dans le cas d'une matrice totalement positive
  */
void AllPositiveMatrix::resolve(ProblemData &data, short AllocatedThreads)
{
  /** \todo V�rifier si la longueur/largeur commence � z�ro ou � un
    */ 
  this->SetCoordMaximumSubArray(0,0,data.GetLength()-1,data.GetWidth()-1);
}


/** \brief Algorithme de r�solution dans le cas d'une matrice totalement n�gative
  */
void AllNegativeMatrix::resolve(ProblemData &data, short AllocatedThreads)
{
  short* matrice = data.GetMatrice();
  
  short max_value = matrice[0];
  int max_coordinate[2] = {0,0};
  
  
  for(int i=1;i<data.GetWidth()*data.GetLength();i++){
    if(matrice[i]>max_value){
      max_value = matrice[i];
      max_coordinate[0] = i - (int)(((i-1)/data.GetLength())*data.GetLength());
      max_coordinate[1] = (int)(i/data.GetLength());
    }
    if(matrice[i] == 0)
      break;
  }

  /** \todo V�rifier si la longueur/largeur commence � z�ro ou � un
  */ 
  this->SetCoordMaximumSubArray(max_coordinate[0],max_coordinate[1],max_coordinate[0],max_coordinate[1]);

}


/** \todo R�aliser l'algorithme de Kadane sur cette fonction en 1D
  */
/** \brief Algorithme de r�solution dans le cas d'une matrice � une seule dimension
  */
void OneDimensionMatrix::resolve(ProblemData &data, short AllocatedThreads)
{
}

/** \todo R�aliser l'algorithme de Kadane sur cette fonction en 2D
  */
/** \brief Algorithme de r�solution dans le cas d'une matrice � 2 dimensions
  */
void TwoDimensionMatrix::resolve(ProblemData &data, short AllocatedThreads)
{
}
