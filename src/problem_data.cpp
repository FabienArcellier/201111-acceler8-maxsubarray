#include <assert.h>
#include <memory>
#include <new>
#include "problem_data.h"

ProblemData::ProblemData (int width, int length)
{
  this -> width = width;
  this -> length = length;
  this -> matrice = new short[width * length];
  
  // 0 etant l'element neutre, il contient que des positifs et des negatifs
  this -> containOnlyPositiveNumbers = 1;
  this -> containOnlyNegativeNumbers = 1;
}

ProblemData::~ProblemData ()
{
  delete [] this -> matrice;
}

int ProblemData::GetWidth ()
{
  return this -> width;
}

int ProblemData::GetLength ()
{
  return this -> length;
}

/*!
 * \brief Permet d'enregistrer une valeur de type short dans la matrice
 * 
 * x et y doivent être defini à l'interieur de la matrice
 */
void ProblemData::SetValue (int x, int y, short value)
{
  assert (x < this -> width);
  assert (x >= 0);
  assert (y < this -> length);
  assert (y >= 0);
  
  (this -> matrice)[x * y] = value;
  this -> containOnlyPositiveNumbers = this -> containOnlyPositiveNumbers & (value >= 0);
  this -> containOnlyNegativeNumbers = this -> containOnlyNegativeNumbers & (value <= 0);
}

/*!
 * \brief Permet de recuperer une valeur de type short de la matrice
 * 
 * x et y doivent être defini à l'interieur de la matrice
 */
short ProblemData::GetValue (int x, int y)
{
  assert (x < this -> width);
  assert (x >= 0);
  assert (y < this -> length);
  assert (y >= 0);
  
  return (this -> matrice)[x * y];
}

/*!
 * \brief Retourne le tableau 1D matrice. Doit etre utilise en lecture seule
 * 
 * indice = x * length + y
 */
short* ProblemData::GetMatrice ()
{
  return this -> matrice;
}

int ProblemData::ContainOnlyPositiveNumbers ()
{
  return this -> containOnlyPositiveNumbers;
}

int ProblemData::ContainOnlyNegativeNumbers ()
{
  return this -> containOnlyNegativeNumbers;
}