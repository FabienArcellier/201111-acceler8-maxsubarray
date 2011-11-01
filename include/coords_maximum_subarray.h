
class CoordsMaximumSubarray
{
public:
  CoordsMaximumSubarray ();
  ~CoordsMaximumSubarray ();
  
  /*!
   * \brief Add the coord of an array
   */
  void Add (int x0, int y0, int x1, int y1);
  
  /*!
   * \brief Return the list that contains all the results coords
   */
  list<vector<int> > * Get () 
  {
    return this -> coords;
  }
  
  /*!
   * \brief Clear the result list
   */
  void Clear ()
  {
    this -> coords -> clear ();
  }
  
  /*!
   * \brief Display the result on a stream (cout for example)
   */
  void Display ();
  
private:
  list<vector<int> > * coords;
};