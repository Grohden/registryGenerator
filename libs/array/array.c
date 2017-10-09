#include "array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Array *initArray(int size) {
  Array *arr = (Array *) calloc(sizeof(Array), 1);

  arr->data = (int *) calloc(sizeof(int), size);
  arr->length = 0;
  arr->size = size;

  return arr;
}

int getAtArray(Array *array, int index) { return array->data[index]; }

bool addToArray(Array *array, int data) {
  if (isArrayFull(array)) {
    return false;
  } else {
    array->data[array->length] = data;
    array->length++;
    return true;
  }
}

bool setAtArray(Array *array, int data, int index) {
  if (index > getArrayLenght(array)) {
    return false;
  } else {
    array->data[index] = data;
    return true;
  }
}

int getArrayLenght(Array *array) { return array->length; }

bool isArrayFull(Array *array) {
  return getArrayLenght(array) >= array->size - 1;
}