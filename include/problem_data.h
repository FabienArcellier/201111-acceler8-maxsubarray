/*!
 * \brief Class that define the structure to hold problem's datas
 */
class ProblemData {
public:
  ProblemData (int width, int length);
  ~ProblemData ();
  int GetWidth ();
  int GetLength ();
  
  /*!
   * \brief Permet d'enregistrer une valeur de type short dans la matrice
   * 
   * x et y doivent être defini à l'interieur de la matrice
   */
  void SetValue (int x, int y, short value);
  
  /*!
   * \brief Permet de recuperer une valeur de type short de la matrice
   * 
   * x et y doivent être defini à l'interieur de la matrice
   */
  short GetValue (int x, int y);
  
  /*!
   * \brief Retourne le tableau 1D matrice. Doit etre utilise en lecture seule
   * 
   * indice = x * length + y
   */
  short* GetMatrice ();
  
  int ContainOnlyPositiveNumbers ();
  int ContainOnlyNegativeNumbers ();

private:
  short *matrice;
  int width;
  int length;
  int containOnlyPositiveNumbers;
  int containOnlyNegativeNumbers;
};