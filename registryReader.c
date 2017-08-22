#include <stdlib.h>
#include <stdio.h>
#include "./libs/SO/specifics.h"
#include "registry.h"
#include "registryReader.h"
#include "registryGenerator.h"

void readPaginated()
{
    int pageSize;
    int printedCount;
    int c;
    bool shouldKeepReading = true;

    FILE *file;

    //FIXME: handle error
    file = fopen(REGISTRY_FILE_NAME, "r");

    Registry *registry = initEmptyRegistry();

    printf("Page size: ");
    scanf("%d", &pageSize);

    do
    {
        printedCount = 0;

        do
        {
            fscanf(
                file,
                "%d %c %d %d %d %d",
                &registry->key,
                &registry->sold,
                &registry->operationValue,
                &registry->operationDate->day,
                &registry->operationDate->month,
                &registry->operationDate->year
            );
            printRegistry(registry);

        } while (++printedCount < pageSize);

        printf("Keep reading? (y/n): ");
        
        getchar(); // handles enter key buffer.

        shouldKeepReading = getchar() == 'y';
    } while (shouldKeepReading);

    fclose(file);

    pause();
}

void readRegistryFile(int pageSize)
{
    int c;
    FILE *file;
    //FIXME: handle error
    file = fopen(REGISTRY_FILE_NAME, "r");

    Registry *registry = initEmptyRegistry();

    fscanf(
        file,
        "%d %c %d %d %d %d",
        &registry->key,
        &registry->sold,
        &registry->operationValue,
        &registry->operationDate->day,
        &registry->operationDate->month,
        &registry->operationDate->year);

    fclose(file);

    pause();
};
