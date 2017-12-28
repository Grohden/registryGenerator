#include <stdio.h>
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

#define REGISTRY_WRITE_STRING "%010d;%c;%09d;%02d;%02d;%04d\n"
#define REGISTRY_PRINT_STRING "%010d %c %09d %02d %02d %04d\n"
#define REGISTRY_READ_STRING "%d;%c;%d;%d;%d;%d"
#define REGISTRY_FILE_NAME "registryFile.csv"

/* Its supposed to be used as a consumer on a for each */
void printRegistry(void *generic);

Registry *initRegistry();

FILE *openRegistryFile(char *mode);

void freeRegistry(Registry *registry);

#endif // !_REGISTRY_
