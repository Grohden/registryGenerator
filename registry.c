#include <stdio.h>
#include <stdlib.h>
#include "registry.h"

void printRegistry(Registry *reg)
{
    printf(
        REGISTRY_WRITE_STRING,
        reg->key,
        reg->sold,
        reg->operationValue,
        reg->operationDate->day,
        reg->operationDate->month,
        reg->operationDate->year
    );
}

Registry *initRegistry()
{
    Registry *registry = calloc(1, sizeof(Registry));
    Date *date = calloc(1,sizeof(Date));

    date->day   = 1;
    date->month = 1;
    date->year  = 1970;
    
    
    registry->key = 0;
    registry->sold = 0;
    registry->operationValue = 0;
    registry->operationDate = date;

    return registry;
}
