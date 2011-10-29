/*!
 * \brief Load data into an instance of ProblemData
 */
ProblemData * InstanciateProblemDataFromFilename (string filename);

void CountRowColumnFromFilehandle (ifstream &file_handle, int *row, int *column);
