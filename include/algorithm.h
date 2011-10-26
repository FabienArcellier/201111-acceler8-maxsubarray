



class algorithm
{
  public:  
    virtual void resolve(ProblemData &data, short AllocatedThreads) = 0;
    void SetWorkerThreads(short threads_quantity);
    short GetWorkerThreads();
    int* GetCoordMaximumSubArray();
    void AfficherMaximumSubArray();
    void SetCoordMaximumSubArray(int x0, int y0, int x1, int y1);
  private:
    short WorkerThreads;
    int coord_maximum_subarray[4];
};

algorithm* SelectAlgorithm (ProblemData &data);

class AllPositiveMatrix : public algorithm
{
  public:
    void resolve(ProblemData &data, short AllocatedThreads);

};

class AllNegativeMatrix : public algorithm
{
  public:
     void resolve(ProblemData &data, short AllocatedThreads);
  
};


class OneDimensionMatrix : public algorithm
{
  public:
    void resolve(ProblemData &data, short AllocatedThreads)  ;
};


class TwoDimensionMatrix : public algorithm
{
  public:
    void resolve(ProblemData &data, short AllocatedThreads);
};

