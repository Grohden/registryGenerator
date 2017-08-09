#include "libs/chainedList/chainedList.h"

typedef struct TypeRegistry {
    int test;
    char * str;
} Registry;

Registry *initRegistry();

void generateEntries(int howMany);

void writeSingleInFile(Registry *registry);

void writeListInFile(ChainedList *registries);