#include "registry.h"

#ifndef _REGISTRY_SORT_
#define _REGISTRY_SORT_

void sortInChunks(FILE *file, int ((*predicate)(void *, void *)));

void mergeSortedFiles(char *one, char *second, char *destiny, int ((*predicate)(void *, void *)));

int orderByDate(void *f, void *s);

int orderByType(void *f, void *s);

int orderByValue(void *f, void *s);

#endif //!_REGISTRY_SORT_