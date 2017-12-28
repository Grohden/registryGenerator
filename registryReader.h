#include "registry.h"
#include <stdio.h>
#include "./libs/array/array.h"
#ifndef _REGISTRY_READER_
#define _REGISTRY_READER_ 1

FILE *openRegistryFile(char *mode);

bool loadSingleRegistry(FILE *openReadFile, Registry *destiny);

Array *loadChunkIntoMemory(FILE *file, int pageSize);

void readPaginated();

#endif  // !_REGISTRY_READER_
