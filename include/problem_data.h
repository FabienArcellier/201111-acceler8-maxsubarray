/*!
 * \brief Class that define the structure to hold problem's datas
 */
class ProblemData {
public:
  ProblemData (int width, int height);
  ~ProblemData ();
  int GetWidth ();
  int GetHeight ();
  
  /*!
   * \brief Permet d'enregistrer une valeur de type short dans la matrice
   * 
   * column et row doivent être defini à l'interieur de la matrice
   */
  void SetValue (int column, int row, short value)
  {
    assert (column < this -> width);
    assert (column >= 0);
    assert (row < this -> height);
    assert (row >= 0);
    
    (this -> matrice)[(this -> width * row) + column] = value;
    this -> containOnlyPositiveNumbers = this -> containOnlyPositiveNumbers & (value >= 0);
    this -> containOnlyNegativeNumbers = this -> containOnlyNegativeNumbers & (value <= 0);
  }
  
  /*!
   * \brief Permet de recuperer une valeur de type short de la matrice
   * 
   * column et row doivent être defini à l'interieur de la matrice
   */
  short GetValue (int column, int row);
  
  /*!
   * \brief Retourne le tableau 1D matrice. Doit etre utilise en lecture seule
   * 
   * indice = row * width + column
   */
  short* GetMatrice ();
  
  int ContainOnlyPositiveNumbers ();
  int ContainOnlyNegativeNumbers ();

private:
  short *matrice;
  int width;
  int height;
  int containOnlyPositiveNumbers;
  int containOnlyNegativeNumbers;
};