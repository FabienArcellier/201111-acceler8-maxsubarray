/*!
 * \brief Load data into an instance of ProblemData
 */
ProblemData * InstanciateProblemDataFromFilename (string filename);

void CountRowColumnFromFilehandle (const char *buffer, int *row, int *column, int size);
