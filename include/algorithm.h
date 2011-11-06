
class algorithm
{
  public:
    algorithm ();
    ~algorithm ();
    virtual void resolve(ProblemData &data) = 0;
    void SetWorkerThreads(short threads_quantity);
    short GetWorkerThreads();
    CoordsMaximumSubarray * GetCoordsMaximumSubarray();
    void SetCoordsMaximumSubarray(int x0, int y0, int x1, int y1);
    void ClearCoordsMaximumSubarray ();
  protected:
    CoordsMaximumSubarray *coord_maximum_subarray;
    short WorkerThreads;
};

algorithm* SelectAlgorithm (ProblemData &data);

class AllPositiveMatrix : public algorithm
{
  public:
    void resolve(ProblemData &data);

};

class AllNegativeMatrix : public algorithm
{
  public:
     void resolve(ProblemData &data);
  
};

class OneDimensionMatrix : public algorithm
{
  public:
    void resolve(ProblemData &data)  ;
};

class TwoDimensionMatrix : public algorithm
{
  public:
    void resolve(ProblemData &data);
};

class TwoDimensionMatrixWithCache : public algorithm
{
  public:
    void resolve(ProblemData &data);
};

class TwoDimensionMatrixParallel : public algorithm
{
  public:
    void resolve(ProblemData &data);
};