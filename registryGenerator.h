#include <stdbool.h>
#include "registry.h"
#include "libs/chainedList/chainedList.h"

#ifndef _REGISTRY_GENERATOR_
#define _REGISTRY_GENERATOR_ 1

#define REGISTRY_FILE_NAME "registryFile.txt"


Registry *initRegistry();

Registry *initEmptyRegistry();

void writeSingleInFile(Registry *registry);

void writeListInFile(unsigned int howMany);

int getSizeOfRegistry();

#endif //!_REGISTRY_GENERATOR_