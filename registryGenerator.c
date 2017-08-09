#include <stdlib.h>
#include "registryGenerator.h"
#include "libs/ChainedList/chainedList.h"
#include "libs/utils.h"

#define REGISTRY_FILE_NAME "registryFile.txt"
#define REGISTRY_INTERPOLATION_STRING "%d %s"

void fprintfRegistry(FILE * f,Registry *registry);

Registry *initRegistry()
{
    Registry *registry = calloc(1, sizeof(Registry));
    registry->str = "teste";
    registry->test = 25;
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

void fprintfRegistry(FILE * f,Registry *registry)
{
    fprintf(
        f,
        REGISTRY_INTERPOLATION_STRING,
        registry->test,
        registry->str
    );
}