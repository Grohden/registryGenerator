#ifndef _REGISTRY_
#define _REGISTRY_ 1

//TODO: Use time.h for this
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

#define REGISTRY_INTERPOLATION_STRING "%010d %c %09d %02d %02d %04d\n"


void printRegistry(Registry *reg);

#endif // !_REGISTRY_
