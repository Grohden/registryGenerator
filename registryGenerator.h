#include <stdbool.h>
#include "libs/chainedList/chainedList.h"

typedef struct TypeRegistry {
    int key;
    char sold;
    char *operationValue;
    unsigned long long operationDate;
} Registry;

Registry *initRegistry();

ChainedList* generateEntries(int howMany);

void writeSingleInFile(Registry *registry);

void writeListInFile(ChainedList *registries);