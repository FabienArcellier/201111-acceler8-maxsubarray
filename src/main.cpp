#include <iostream>
#include "assert.h"
#include "main.h"

using namespace std;

/*!
 * \brief Class that define the structure to hold problem's datas
 */
class Matrice {
public:
  /*!
   * \brief Constructor of an instance of Matrice
   */
  Matrice (int width, int length)
  {
    this -> width = width;
    this -> length = length;
    this -> matrice = new short[width * length];
  }
  
  ~Matrice ()
  {
    delete [] this -> matrice;
  }
  
  short *matrice;
  int width;
  int length;
};

#ifndef UNIT_TEST

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    DisplayHelp ();
  }
}

#endif

/*!
 * \brief Display information when the program can't be executed
 */
void DisplayHelp ()
{
  cout << "Usage : run [PROCESSORS] [FILES]...\n\n";
  cout << "\tDisplay the coords of the maximum subarray for each array contained in FILES\n\n";
  cout << "\t[PROCESSORS] Count of processor used\n\n";
  cout << "Exemple";
  cout << "\t./run 40 input1.txt input2.txt input3.txt > output.txt\n";
}

void DisplayMaxSubarray (int max_subarray_bornes[])
{
  assert (max_subarray_bornes != NULL);
  
  for (int i = 0; i < 4; i++)
  {
    cout << max_subarray_bornes[i];
    if (i < 3)
    {
      cout << " ";
    }
    else
    {
      cout << "\n";
    }
  }
}