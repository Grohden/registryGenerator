#include <stdbool.h>


#ifndef _ARRAY_
#define _ARRAY_

typedef struct TypeArray {
  int *data;
  int length;
  int size;
} Array;

Array *initArray(int size);

int getAtArray(Array *array, int index);

bool addToArray(Array *array, int data);

bool setAtArray(Array *array, int data, int index);

int getArrayLenght(Array *array);

bool isArrayFull(Array *array);

#endif  // !_ARRAY_
