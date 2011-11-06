
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
   * \brief Return the iterator to first element to browse through results
   */
  list<vector<int> *>::iterator GetIterator () 
  {
    assert (this -> coords != NULL);
    return this -> coords -> begin ();
  }
  
  /*!
   * \brief Return the number of coords store in an instance of CoordsMaximumSubarray
   */
  int Count ()
  {
    assert (this -> coords != NULL);
    return this -> coords -> size ();
  }
  
  /*!
   * \brief Clear the result list
   */
  void Clear ()
  {
    assert (this -> coords != NULL);
    this -> coords -> clear ();
  }
  
  /*!
   * \brief Call delete on every object and clear the list
   */
  void ClearDestroy ();
  
  /*!
   * \brief Copy an instance of CoordsMaximumSubarray inside this
   */
  void Copy (CoordsMaximumSubarray &);
  
  /*!
   * \brief Concat the content of an instance of CoordsMaximumSubarray inside this
   */
  void Concat (CoordsMaximumSubarray &);
  
  /*!
   * \brief Display the result on a stream (cout for example)
   */
  void Display ();
  
private:
  list<vector<int> *> * coords;
};