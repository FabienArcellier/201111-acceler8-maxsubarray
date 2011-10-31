class DebugAlgorithm
{
public:
  DebugAlgorithm (string&, ProblemData&);
  ~DebugAlgorithm ();
  void WriteValue (int);
  void WriteMaxValue (int);
  void WriteCoord (int x0, int y0, int x1, int y1);
  void WriteMatrice (int x0, int y0, int x1, int y1);
  void WriteEmptyLine ();
  void WriteString (string &);
private:
  ProblemData *problem_data;
  ofstream *output;
};