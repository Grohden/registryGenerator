#include "registry.h"

#ifndef _REGISTRY_SORT_
#define _REGISTRY_SORT_

#define CHUNK_SIZE 10

void sortInChunks(FILE *file);

int orderByDate(void *f, void *s);

int orderByType(void *f, void *s);

int orderByValue(void *f, void *s);

#endif //!_REGISTRY_SORT_