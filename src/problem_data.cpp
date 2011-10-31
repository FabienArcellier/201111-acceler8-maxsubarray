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
 * row et column doivent être defini à l'interieur de la matrice
 */
void ProblemData::SetValue (int column, int row, short value)
{
  assert (column < this -> width);
  assert (column >= 0);
  assert (row < this -> length);
  assert (row >= 0);
  
  (this -> matrice)[(this -> width * row) + column] = value;
  this -> containOnlyPositiveNumbers = this -> containOnlyPositiveNumbers & (value >= 0);
  this -> containOnlyNegativeNumbers = this -> containOnlyNegativeNumbers & (value <= 0);
}

/*!
 * \brief Permet de recuperer une valeur de type short de la matrice
 * 
 * row et column doivent être defini à l'interieur de la matrice
 */
short ProblemData::GetValue (int column, int row)
{
  assert (column < this -> width);
  assert (column >= 0);
  assert (row < this -> length);
  assert (row >= 0);
  
  return (this -> matrice)[(this -> width * row) + column];
}

/*!
 * \brief Retourne le tableau 1D matrice. Doit etre utilise en lecture seule
 * 
 * indice = row * width + column
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