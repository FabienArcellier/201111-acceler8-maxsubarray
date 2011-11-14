#include <cstdlib>
#include <assert.h>
#include <memory>
#include <new>
#include "problem_data.h"

ProblemData::ProblemData (int width, int height)
{
  this -> width = width;
  this -> height = height;
  this -> matrice = (short *) malloc (width * height * sizeof (short));
  
  // 0 etant l'element neutre, il contient que des positifs et des negatifs
  this -> containOnlyPositiveNumbers = 1;
  this -> containOnlyNegativeNumbers = 1;
}

ProblemData::~ProblemData ()
{
  free(this -> matrice);
}

int ProblemData::GetWidth ()
{
  return this -> width;
}

int ProblemData::GetHeight ()
{
  return this -> height;
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
  assert (row < this -> height);
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