#include <stdbool.h>
#include <stdio.h>
#include "registry.h"

#ifndef _REGISTRY_GENERATOR_
#define _REGISTRY_GENERATOR_ 1


Registry *initRandomRegistry();

void writeRegistryAtFile(FILE *file, Registry *registry);

void writeListInFile(double howMany);

int getSizeOfRegistry();

#endif  //!_REGISTRY_GENERATOR_