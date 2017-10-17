#include "registry.h"
#include <stdio.h>
#include "./libs/array/array.h"
#ifndef _REGISTRY_READER_
#define _REGISTRY_READER_ 1

void readRegistryFile(int pageSize);

FILE *openRegistryFile(char *mode);

Array *loadChunkIntoMemory(FILE *file, int pageSize);

void readPaginated();

#endif  // !_REGISTRY_READER_
