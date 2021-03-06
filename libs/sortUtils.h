#include <stdio.h>

//Macros
#ifndef _SORT_UTILS_
#define _SORT_UTILS_ 1

#include <stdint.h>

typedef struct TypeSortData {
    int comparisons;
    int swaps;
} SortData;

SortData *initSortData();

void swapVariables(int *i, int *j);

void printIntArray(int array[], int size);

#endif // _SORT_UTILS_
