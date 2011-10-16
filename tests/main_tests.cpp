#define UNIT_TEST

#include "test.h"
#include "main.h"

/* Tests declaration */
void DisplayMaxSubarrayTests ();

int main (void)
{
  DisplayMaxSubarrayTests ();
}

void DisplayMaxSubarrayTests ()
{
  TEST_TITLE ("DisplayMaxSubarrayTests");
  int tab[4] = {4,5,6,7};
  DisplayMaxSubarray (tab);
}