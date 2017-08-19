#include <stdbool.h>
#include "libs/chainedList/chainedList.h"

#ifndef _REGISTRY_GENERATOR_
#define _REGISTRY_GENERATOR_ 1

#define REGISTRY_FILE_NAME "registryFile.txt"

//TODO: create date lib for this struct
typedef struct TypeDate {
    char day;
    char month;
    int year;
} Date;

typedef struct TypeRegistry {
    int key;
    char sold;
    int operationValue;
    Date *operationDate;
} Registry;

Registry *initRegistry();

Registry *initEmptyRegistry();

void writeSingleInFile(Registry *registry);

void writeListInFile(int howMany);

int getSizeOfRegistry();

#endif //!_REGISTRY_GENERATOR_