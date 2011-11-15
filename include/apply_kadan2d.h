class BlockKadan2d
{
public:
  int lower;
  int upper;
  int total_work;
  int work_by_thread;
  int current_work;
  
  bool empty() const 
  {
    return this -> lower == this -> upper;
  };
  
  bool is_divisible() const 
  {
    return this -> upper > this -> lower + 1 && this -> current_work > (this -> work_by_thread * 2);
  };
  
  BlockKadan2d (int lower, int upper, int count_thread) : 
  lower (lower),
  upper (upper)
  {
    int local_total_work = 0;
    for (int i = lower; i < upper; i++)
    {
      local_total_work += i;
    }
    
    this -> total_work = local_total_work;
    this -> work_by_thread = local_total_work / count_thread;
    this -> current_work = local_total_work;
  };
  
  BlockKadan2d (BlockKadan2d &r, split) :
    work_by_thread (r.work_by_thread)
  {
    int local_upper = r.upper;
    int local_lower = r.lower;
    int work = 0;
    do
    {
      work += local_upper - local_lower;
      local_lower++;
    } while (work < this -> work_by_thread && local_lower < local_upper); 
    
    this -> lower = local_lower;
    this -> upper = r.upper;
    this -> current_work = r.current_work - work;
    
    r.upper = local_lower;
    r.current_work = work;
    
    /*DEBUG_IF (1, "New Thread");
    DEBUG_IF (1, this -> work_by_thread);
    DEBUG_IF (1, this -> lower);
    DEBUG_IF (1, this -> upper);
    DEBUG_IF (1, this -> current_work);
    DEBUG_IF (1, r.lower);
    DEBUG_IF (1, r.upper);
    DEBUG_IF (1, r.current_work);*/
  };
};


class ApplyKadan2d
{
public:
  ApplyKadan2d (ProblemData *data) : 
    problem_data (data),
    maxValue (1 << 31) {
//       cout << "ApplyKadan2d : Constructeur invoked" << endl;
      this -> coords_maximum_subarray = new CoordsMaximumSubarray ();
    };
    
    /*!
     * \brief Constructor by copy to instanciate the parallele_reduce
     */
    ApplyKadan2d (ApplyKadan2d& x, split) : 
    problem_data (x.GetProblemData()),
    maxValue (x.GetMaxValue()) {
       cout << "ApplyKadan2d : Constructeur by copy invoked" << endl;
      this -> coords_maximum_subarray = new CoordsMaximumSubarray ();
    };
    
  ~ApplyKadan2d ()
  {
//     cout << "ApplyKadan2d : Destructor invoked" << endl;
    delete this -> coords_maximum_subarray;
  }

  /*!
   * \brief Task to perform as Parallel treatment
   */
  void operator () ( const BlockKadan2d &r);
  
  /*!
   * \brief Read only accessor for the attribute maxValue
   */
  int GetMaxValue ()
  {
    return this -> maxValue;
  }
  
  CoordsMaximumSubarray * GetCoordsMaximumSubarray ()
  {
    return this -> coords_maximum_subarray;
  }
  
  ProblemData * GetProblemData ()
  {
    return this -> problem_data;
  }
  
  void join (ApplyKadan2d&);
  
private:
  ProblemData *problem_data;
  CoordsMaximumSubarray *coords_maximum_subarray;
  int maxValue;
};
