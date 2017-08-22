#include <stdio.h>
#include "registry.h"

void printRegistry(Registry *reg)
{
    printf(
        REGISTRY_INTERPOLATION_STRING,
        reg->key,
        reg->sold,
        reg->operationValue,
        reg->operationDate->day,
        reg->operationDate->month,
        reg->operationDate->year
    );
}
