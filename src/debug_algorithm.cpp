using namespace std;

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include "problem_data.h"
#include "debug_algorithm.h"

DebugAlgorithm::DebugAlgorithm (string &filename, ProblemData &problem_data)
{
  this -> output = new ofstream (filename.c_str());
  this -> problem_data = &problem_data;
}

DebugAlgorithm::~DebugAlgorithm ()
{
  this -> output -> close ();
  delete this -> output;
}

void DebugAlgorithm::WriteValue (int value)
{
  assert (this -> output != NULL);
  
  ofstream &output = *(this -> output);
  output << "\tValue : " << value << endl;
}

void DebugAlgorithm::WriteMaxValue (int max_value)
{
  assert (this -> output != NULL);
  
  ofstream &output = *(this -> output);
  output << "\tMax value : " << max_value << endl;
}

void DebugAlgorithm::WriteCoord (int x0, int y0, int x1, int y1)
{
  assert (this -> output != NULL);
  
  ofstream &output = *(this -> output);
  output << "Coords : " << x0 << " " << y0 << " " << x1 << " " << y1 << endl;
}

void DebugAlgorithm::WriteMatrice (int x0, int y0, int x1, int y1)
{
  assert (this -> output != NULL);
  assert (this -> problem_data != NULL);
  
  ofstream &output = *(this -> output);
  int matrice_width = problem_data -> GetWidth ();
  int matrice_height = problem_data -> GetHeight ();
  
  for (int j = 0; j < matrice_height; j++)
  {
    output << "\t";
    for (int i = 0; i < matrice_width; i++)
    {
      if (i >= x0 && i <= x1 && j >= y0 && j <= y1)
      {
        output << problem_data -> GetValue (i, j);
        output << " ";
      }
      else
      {
        output << "- ";
      }
    }
    
    output << endl;
  }
}

void DebugAlgorithm::WriteEmptyLine ()
{
  assert (this -> output != NULL);
  
  ofstream &output = *(this -> output);
  output << "\n";
}

void DebugAlgorithm::WriteString (string &text)
{
  assert (this -> output != NULL);
  
  ofstream &output = *(this -> output);
  output << text << endl;
}