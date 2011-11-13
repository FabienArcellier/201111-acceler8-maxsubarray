#include <assert.h>
#include <memory>
#include <new>
#include <iostream>
using namespace std;

#include "problem_data.h"
#include "cache_problem_data.h"



CacheProblemData::CacheProblemData(ProblemData &data)
{
  
  int matrice_length = data.GetHeight();
  int matrice_width = data.GetWidth();
  short * matrice = data.GetMatrice();
  this -> matrice = new int[matrice_width * (matrice_length + 1)];
  for(int row = 0; row < matrice_length + 1; row++)
  {
    for(int col = 0; col < matrice_width; col++)
    {
      this->matrice[col + row * matrice_width] = 0;
      
      if (row != 0)
      {
        // Valeur de la ligne courante
        this -> matrice[col + row * matrice_width] = matrice[col + (row - 1) * matrice_width];
        // Ajour de la valeur des lignes precedentes
        this -> matrice[col + row * matrice_width] += this -> matrice[col + (row - 1) * matrice_width];
      }
    }
  }

  this -> length = matrice_length + 1;
  this -> width = matrice_width;
}

CacheProblemData::~CacheProblemData ()
{
  delete [] this -> matrice;
}

int CacheProblemData::GetValue(int col, int row)
{
  assert (col < this -> width);
  assert (col >= 0);
  assert (row < this -> length - 1);
  assert (row >= -1);
  
  return (this -> matrice)[this -> width * (row + 1) + col]; 
}

