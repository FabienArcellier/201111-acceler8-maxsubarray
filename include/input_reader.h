/*!
 * \brief Load data into an instance of ProblemData
 */
ProblemData * InstanciateProblemDataFromFilename (string filename);

void CountRowColumnFromFilehandle (const char *buffer, int *row, int *column, int size);

class InputReaderParseData
{
public:
  list<short> * data;
  char * buffer;
  
  InputReaderParseData (char *buffer) :
    buffer(buffer)
  {
    this -> data = new list<short>();
  };
  
  InputReaderParseData (InputReaderParseData &r, split) :
    buffer(r.buffer)
  {
    this -> data = new list<short>();
  };
  
  ~InputReaderParseData()
  {
    delete this -> data;
  }
  
  /*!
   * \brief Task to perform as Parallel treatment
   */
  void operator () ( const blocked_range<int> &r);
  
  void join (InputReaderParseData&);
};