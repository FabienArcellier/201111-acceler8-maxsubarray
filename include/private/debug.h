
/* Macro qui affiche la valeur d'une variable si une expression == 1
 * */

#include <string.h>
#include <stdio.h>

#ifndef NDEBUG

#define DEBUG_IF(EXPRESSION, VARIABLE) \
if (EXPRESSION)\
{\
  cerr << __FILE__ << " - " << __LINE__ << " D:" << #VARIABLE << " : " << VARIABLE << endl << flush;\
}

#endif

#ifdef NDEBUG

#define DEBUG_IF(EXPRESSION, VARIABLE)

#endif