/*!
 * \brief 
 */
class CacheProblemData {
public:
  CacheProblemData (ProblemData &data);
  ~CacheProblemData ();
  int GetValue(int col,int row);
  int GetValue(int col, int row, int row_ref);
private:
  int *matrice;
  int width;
  int length;
};