#include <stdio.h>
//Macros
#ifndef _ROHDEN_UTILS
#define _ROHDEN_UTILS 1

//each, receives 2 ints and iterate the count from 0 to maxValue
#define each(count, maxVal) for(count = count; count < (maxVal); count++)
//repeat, receives 1 int and repeat the the inside code same number passed as arg
#define repeat(times) for(int i = 0; i < (times); i++)

#define println(...) printf(__VA_ARGS__); printf("\n");

#endif // _ROHDEN_UTILS
