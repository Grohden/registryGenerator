#include <stdio.h>
#include <stdlib.h>
#include "../sortUtils.h"
#include "quickSort.h"

int partition(void **array, int size, int pivot, int ((*predicate)(void *, void *))) {
  if (size <= 1) {
    return 0;
  }

  void *pivotValue = array[pivot];
  int start = 0;
  int end = size - 1;

  while (start <= end) {

    while (start <= end && predicate(pivotValue, array[start])) {
      start++;
    }

    while (start <= end && predicate(array[end], pivotValue)) {
      end--;
    }

    if (start <= end) {
      swapVariables((int *) &array[start], (int *) &array[end]);

      start++;
      end--;
    }
  }

  swapVariables((int *) &array[pivot], (int *) &array[end]);

  return end;
}

void delegatedQuickSort(void **array, int size, int ((*predicate)(void *, void *))) {
  if (size <= 1) {
    return;
  }

  int start = 0;
  int end = size - 1;

  if (start < end) {
    start = partition(array, size, 0, predicate);

    delegatedQuickSort(array, start, predicate);
    delegatedQuickSort(&array[start + 1], size - (start + 1), predicate);
  }
}


void quickSortArray(void **array, int size, int ((*predicate)(void *, void *))) {
  SortData *sortData = (SortData *) calloc(sizeof(SortData), 1);
  sortData->comparisons = 0;
  sortData->swaps = 0;

  delegatedQuickSort(array, size, predicate);
}
