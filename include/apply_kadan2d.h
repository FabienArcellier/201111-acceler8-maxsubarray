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

class ApplyKadan2DScan
{
public:
  int value;
  int max_value;
  int borne_gauche_x;
  int borne_gauche_y;
  int borne_droite_y;
  const vector<int> tableau_colonne;
  CoordsMaximumSubarray *coords_maximum_subarray;
  
  ApplyKadan2DScan (int arg_borne_gauche_x, int arg_borne_gauche_y, int arg_borne_droite_y, const vector<int> arg_tableau_colonne, int arg_max_value) : 
    value (0), 
    max_value(arg_max_value), 
    borne_gauche_x (arg_borne_gauche_x), 
    borne_gauche_y (arg_borne_gauche_y), 
    borne_droite_y (arg_borne_droite_y), 
    tableau_colonne (arg_tableau_colonne)
  {
    this -> coords_maximum_subarray = new CoordsMaximumSubarray ();
  }
  
  ApplyKadan2DScan (ApplyKadan2DScan &scan, split) : 
    value(scan.value), 
    max_value(scan.max_value), 
    borne_gauche_x (scan.borne_gauche_x), 
    borne_gauche_y (scan.borne_gauche_y),
    borne_droite_y (scan.borne_droite_y),
    tableau_colonne (scan.tableau_colonne)
  {
    this -> coords_maximum_subarray = new CoordsMaximumSubarray ();
  }
  
  template<typename Tag>
  void operator () (const blocked_range<int> &r, Tag);
  
  void reverse_join (ApplyKadan2DScan &scan);
  
  void assign (ApplyKadan2DScan &scan)
  {
    this -> value = scan.value;
    this -> max_value = scan.max_value;
    this -> borne_gauche_x += scan.borne_gauche_x;
    this -> coords_maximum_subarray -> Copy (*(scan.coords_maximum_subarray));
  }
};
