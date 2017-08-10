#include <stdlib.h>
#include <stdbool.h>
#include "registryGenerator.h"
#include "libs/ChainedList/chainedList.h"
#include "libs/utils.h"

#define REGISTRY_FILE_NAME "registryFile.txt"
#define REGISTRY_INTERPOLATION_STRING "%c %c %s %s"

char keyGenerationHolder = 0;

void fprintfRegistry(FILE * f,Registry *registry)
{
    fprintf(
        f,
        REGISTRY_INTERPOLATION_STRING,
        registry->key,
        registry->sold,
        registry->operationValue,
        registry->operationDate 
    );
}

char updateKeyGenerator(){
    return (keyGenerationHolder++) - 1;
}

Registry *initRegistry()
{
    Registry *registry = calloc(1, sizeof(Registry));

    registry->operationDate = "1502334751265"; // Thu Aug 10 2017 00:12:31 GMT-0300 (Hora oficial do Brasil)
    registry->operationValue = "1000";
    registry->key = updateKeyGenerator();
    registry->sold = 'C';

    return registry;
}

void generateEntries(int howMany)
{
    ChainedList *list = initChain();
    repeat(howMany)
    {
        addToChain(list, initRegistry());
    }
};

void writeSingleInFile(Registry *registry)
{
    FILE *registryFile = fopen(REGISTRY_FILE_NAME, "w");

    fprintfRegistry(registryFile, registry);
    fclose(registryFile);
}

void writeListInFile(ChainedList *registries)
{
    if (isChainEmpty(registries))
    {
        println("Skippin write for empty chain list");
        return;
    }

    int len = getChainLength(registries);
    int i = 0;

    FILE *registryFile = fopen(REGISTRY_FILE_NAME, "w");
    each(i, len)
    {
        fprintfRegistry(registryFile, (Registry *) getChainDataAt(registries, i));
    }
    fclose(registryFile);
}

