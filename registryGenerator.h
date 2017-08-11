#include <stdbool.h>
#include "libs/chainedList/chainedList.h"

typedef struct TypeRegistry {
    int key;
    char sold;
    char *operationValue;
    unsigned long long operationDate;
} Registry;

Registry *initRegistry();

void writeSingleInFile(Registry *registry);

void writeListInFile(int howMany);