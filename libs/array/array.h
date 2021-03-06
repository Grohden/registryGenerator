#include <stdbool.h>
#include <stdio.h>


#ifndef _ARRAY_
#define _ARRAY_

typedef struct TypeArray {
  int *data;
  int length;
  int size;
} Array;

Array *initArray(size_t size);

int getAtArray(Array *array, int index);

bool addToArray(Array *array, int data);

bool setAtArray(Array *array, int data, int index);

int getArrayLength(Array *array);

bool isArrayFull(Array *array);

void freeArray(Array *array);

#endif  // !_ARRAY_
