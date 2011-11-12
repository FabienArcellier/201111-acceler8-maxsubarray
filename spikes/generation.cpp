#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define CONFIG_RAND_MIN     -50  
#define CONFIG_RAND_MAX     50  
#define _RAND ((rand() % (CONFIG_RAND_MAX - CONFIG_RAND_MIN)) + CONFIG_RAND_MIN)  
  
using namespace std;
int main(int argc, char* argv[])
{
   int ran_num;
   srand((unsigned)time(0));

   int lengthi =atoi(argv[1]);
   int lengthj =atoi(argv[2]);

   srand((unsigned)time(0));
   for(int i = 0; i < lengthi ; i++)  
   {  
      std::cout << _RAND;  
      for(int j = 1; j < lengthj; j++)
         std::cout << ' ' << _RAND;  
      std::cout << std::endl;  
   }
}