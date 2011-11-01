/*!
 * \brief 
 */
class CacheProblemData {
public:
  CacheProblemData (ProblemData &data);
  ~CacheProblemData ();
  int GetValue(int col,int row);
  int GetValue(int col_ref, int col, int row)
  {
    int* matrice = this->matrice;
    int l_width = this->width;
    return (matrice[col+row*l_width] - matrice[col_ref+row*l_width]);
  }
private:
  int *matrice;
  int width;
  int length;
};