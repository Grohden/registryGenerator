#include <stdbool.h>
#include "libs/chainedList/chainedList.h"

typedef struct TypeRegistry {
    char key;
    char sold;
    char *operationValue;
    char *operationDate;
} Registry;

Registry *initRegistry();

void generateEntries(int howMany);

void writeSingleInFile(Registry *registry);

void writeListInFile(ChainedList *registries);