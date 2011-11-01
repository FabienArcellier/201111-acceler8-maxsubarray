/*!
 * \brief 
 */
class CacheProblemData {
public:
  CacheProblemData (ProblemData &data);
  ~CacheProblemData ();
  int GetValue(int col,int row);
  int GetValue(int col_ref, int col, int row);
private:
  int *matrice;
  int width;
  int length;
};