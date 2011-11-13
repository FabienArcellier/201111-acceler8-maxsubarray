/*!
 * \brief 
 */
class CacheProblemData {
public:
  CacheProblemData (ProblemData &data);
  ~CacheProblemData ();
  int GetValue(int col,int row);
  int GetValue(int col, int row, int row_ref)
  {
    int* matrice = this->matrice;
    int l_width = this->width;
    return matrice [col + (row + 1) * l_width] - matrice [col + (row_ref) * l_width];
  };
  
  int GetWidth()
  {
    return this -> width;
  };
  
  int GetLength()
  {
    return this -> length - 1;
  };
  
  int GetRealLength ()
  {
    return this -> length;
  };
private:
  int *matrice;
  int width;
  int length;
};