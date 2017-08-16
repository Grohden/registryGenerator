#include <stdbool.h>
#include "libs/chainedList/chainedList.h"

typedef struct TypeRegistry {
    int key;
    char sold;
    int operationValue;
    char *operationDate;
} Registry;

Registry *initRegistry();

void writeSingleInFile(Registry *registry);

void writeListInFile(int howMany);

int getSizeOfRegistry();