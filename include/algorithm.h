
#include <vector>
#include <list>


using namespace std;


class algorithm
{
  public:  
    virtual void resolve(ProblemData &data) = 0;
    void SetWorkerThreads(short threads_quantity);
    short GetWorkerThreads();
    list< vector<int> > * GetCoordMaximumSubArray();
    void SetCoordMaximumSubArray(int x0, int y0, int x1, int y1);
    void ClearCoordMaximumSubArray ();
  private:
    short WorkerThreads;
    list < vector<int> >  coord_maximum_subarray;
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

