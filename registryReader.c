#include "registryReader.h"
#include <stdio.h>
#include <stdlib.h>
#include "./libs/SO/specifics.h"
#include "./libs/utils.h"
#include "./libs/array/array.h"
#include "registry.h"
#include "registryGenerator.h"


void readPaginated() {
  int pageSize;
  int printedCount;
  bool shouldKeepReading = true;
  bool hasReadWholeFile = false;

  FILE *file;

  if((file = fopen(REGISTRY_FILE_NAME, "r")) == NULL) {
    println("Error, there's no registry file to be read.");
    pause();
    return;
  };

  Registry *registry = initRegistry();

  printf("Page size: ");
  scanf("%d", &pageSize);

  do {
    printedCount = 0;
    do {
        hasReadWholeFile =
          fscanf(file, REGISTRY_READ_STRING, 
            &registry->key,
            &registry->sold,
            &registry->operationValue,
            &registry->operationDate->day,
            &registry->operationDate->month,
            &registry->operationDate->year
          ) == EOF;
          if(!hasReadWholeFile){
            printRegistry(registry);
          }
    } while (++printedCount < pageSize && !hasReadWholeFile);

    if (!hasReadWholeFile) {
      printf("Keep reading? (y/n): ");
      getchar();                             // handles enter key buffer.
      shouldKeepReading = getchar() == 'y';  // fixme:handle insenstive.
    } else {
      println("There are no more registries to read.");
    }

  } while (shouldKeepReading && !hasReadWholeFile);

  fclose(file);
  pause();
}

Array *readPageToMemory(FILE *file, int pageSize) {
  Registry *registry;
  Array *readData = initArray(pageSize);

  int readCount = 0;
  bool hasReadWholeFile = false; 
  do {
    registry = initRegistry();

    hasReadWholeFile = fscanf(file, REGISTRY_READ_STRING, 
        &registry->key,
        &registry->sold,
        &registry->operationValue,
        &registry->operationDate->day,
        &registry->operationDate->month,
        &registry->operationDate->year
      ) == EOF;

      if(!hasReadWholeFile){
        addToArray(readData, (int) registry);
      }
    } while (++readCount < pageSize && !hasReadWholeFile);

  return readData;
}

void readRegistryFile(int pageSize) {
  FILE *file;

  if((file = fopen(REGISTRY_FILE_NAME, "r")) != NULL){
    Registry *registry = initRegistry();

    fscanf(file, REGISTRY_READ_STRING,
       &registry->key,
       &registry->sold,
       &registry->operationValue,
       &registry->operationDate->day,
       &registry->operationDate->month,
       &registry->operationDate->year
      );

    fclose(file);
  } else {
    println("Error, there's no registry file to be read.");
  }
  pause();
};
