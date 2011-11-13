class ApplyKadan2dWithCache
{
public:
  ApplyKadan2dWithCache (CacheProblemData *data) : 
    cache_problem_data (data),
    maxValue (1 << 31) 
  {
    this -> coords_maximum_subarray = new CoordsMaximumSubarray ();
  };
    
    /*!
     * \brief Constructor by copy to instanciate the parallele_reduce
     */
    ApplyKadan2dWithCache (ApplyKadan2dWithCache& x, split) : 
    cache_problem_data (x.GetCacheProblemData()),
    maxValue (x.GetMaxValue()) {
      //       cout << "ApplyKadan2dWithCache : Constructeur by copy invoked" << endl;
      this -> coords_maximum_subarray = new CoordsMaximumSubarray ();
    };
    
    ~ApplyKadan2dWithCache ()
  {
    //     cout << "ApplyKadan2dWithCache : Destructor invoked" << endl;
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
  
  CacheProblemData * GetCacheProblemData ()
  {
    return this -> cache_problem_data;
  }
  
  void join (ApplyKadan2dWithCache&);
  
private:
  CacheProblemData *cache_problem_data;
  CoordsMaximumSubarray *coords_maximum_subarray;
  int maxValue;
};

class ApplyKadan2dWithCacheInternalLoop
{
  
public:
  ApplyKadan2dWithCacheInternalLoop (CacheProblemData *data, int arg_borne_gauche_y) : 
    borne_gauche_y (arg_borne_gauche_y),
    cache_problem_data (data),
    maxValue (1 << 31)
  {
    this -> coords_maximum_subarray = new CoordsMaximumSubarray ();
  };
    
  /*!
    * \brief Constructor by copy to instanciate the parallele_reduce
    */
  ApplyKadan2dWithCacheInternalLoop (ApplyKadan2dWithCacheInternalLoop& x, split) : 
    borne_gauche_y (x.borne_gauche_y),
    cache_problem_data (x.GetCacheProblemData()),
    maxValue (x.GetMaxValue())
  {
    //       cout << "ApplyKadan2dWithCacheInternalLoop : Constructeur by copy invoked" << endl;
    this -> coords_maximum_subarray = new CoordsMaximumSubarray ();
  };
    
    ~ApplyKadan2dWithCacheInternalLoop ()
  {
    //     cout << "ApplyKadan2dWithCacheInternalLoop : Destructor invoked" << endl;
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
  
  CacheProblemData * GetCacheProblemData ()
  {
    return this -> cache_problem_data;
  }
  
  void join (ApplyKadan2dWithCacheInternalLoop&);
  int borne_gauche_y;
  
private:
  CacheProblemData *cache_problem_data;
  CoordsMaximumSubarray *coords_maximum_subarray;
  int maxValue;
};
