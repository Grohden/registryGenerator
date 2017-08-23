#ifndef _REGISTRY_
#define _REGISTRY_ 1

//TODO: Use time.h for this
typedef struct TypeDate {
    int day;
    int month;
    int year;
} Date;

typedef struct TypeRegistry {
    int key;
    char sold;
    int operationValue;
    Date *operationDate;
} Registry;

#define REGISTRY_WRITE_STRING "%010d %c %09d %02d %02d %04d\n"
#define REGISTRY_READ_STRING "%d %c %d %d %d %d"
#define REGISTRY_FILE_NAME "registryFile.txt"

void printRegistry(Registry *reg);

Registry *initRegistry();

#endif // !_REGISTRY_
