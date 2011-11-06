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
    maxValue (1 << 31) {
//       cout << "ApplyKadan2d : Constructeur by copy invoked" << endl;
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
  void operator () ( const blocked_range<int> &r);
  
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
