#include <stdlib.h>
#include <stdio.h>
#include "./libs/SO/specifics.h"
#include "registryGenerator.h"

void readRegistryFile()
{
    int c;
    FILE *file;
    file = fopen(REGISTRY_FILE_NAME, "r");

    Registry *empty = initEmptyRegistry();
    
    fscanf(
       file,
       "%d %c %d %d %d %d",
       &empty->key,
       &empty->sold,
       &empty->operationValue,
       &empty->operationDate->day,
       &empty->operationDate->month,
       &empty->operationDate->year
    );

    fclose(file);

    pause();
};
