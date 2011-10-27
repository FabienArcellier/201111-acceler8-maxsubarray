typedef struct
{
  int processor_number;
} ApplicationSettings;


/*!
 * \brief Display information when the program can't be executed
 */
void DisplayHelp ();

/*!
 * \brief Display the coord of an array with 4 items
 */
void DisplayMaxSubarray (list<vector<int> > & max_subarray_bornes);

/*!
 * \brief Load data into an instance of ProblemData
 */
ProblemData * InstanciateProblemDataFromFilename (string filename);

void CountRowColumnFromFilehandle (ifstream &file_handle, int *row, int *column);