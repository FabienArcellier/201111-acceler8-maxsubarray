#include <assert.h>
#include <memory>
#include <new>
#include <iostream>
using namespace std;

#include "problem_data.h"
#include "cache_problem_data.h"



CacheProblemData::CacheProblemData(ProblemData &data)
{
  
 int matrice_length = data.GetLength();
 int matrice_width = data.GetWidth();
 short * matrice = data.GetMatrice();
 this -> matrice = new int[(matrice_width+1) * matrice_length];
 for(int row=0;row<matrice_length;row++)
 {
   for(int col=0;col<matrice_width+1;col++)
   {
     this->matrice[row*(matrice_width+1)+col] = 0;
     
     if(col==0)
     {
       this->matrice[row*(matrice_width+1)+col] = 0;
     }
     else
     {
       for(int k=0;k<col;k++)
       {
         this->matrice[row*(matrice_width+1)+col] += matrice[k + row * matrice_width];
       }
     }
   }
   
 }
 
 this -> length = matrice_length;
 this -> width = matrice_width+1;
}

CacheProblemData::~CacheProblemData ()
{
  delete [] this -> matrice;
}




int CacheProblemData::GetValue(int col,int row)
{
  assert (col < this -> width-1);
  assert (col >= -1);
  assert (row < this -> length);
  assert (row >= 0);
  
  return (this -> matrice)[(this -> width * row) + col+1]; 
}

int CacheProblemData::GetValue(int col_ref, int col, int row)
{
  int* matrice = this->matrice;
  int l_width = this->width;
  return (matrice[col+1+row*l_width] - matrice[col_ref+row*l_width]);
}

