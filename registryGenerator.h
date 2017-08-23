#include <stdbool.h>
#include "libs/chainedList/chainedList.h"
#include "registry.h"

#ifndef _REGISTRY_GENERATOR_
#define _REGISTRY_GENERATOR_ 1


Registry *initRandomRegistry();

void writeSingleInFile(Registry *registry);

void writeListInFile(unsigned int howMany);

int getSizeOfRegistry();

#endif  //!_REGISTRY_GENERATOR_