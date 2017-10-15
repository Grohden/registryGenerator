#include "registryReader.h"
#include <stdlib.h>
#include "./libs/SO/specifics.h"
#include "./libs/utils.h"

void readPaginated() {
  int pageSize;
  int printedCount;
  bool shouldKeepReading = true;

  FILE *file;

  if ((file = openRegistryFile("r")) == NULL) {
    println("Error, there's no registry file to be read.");
    pause();
    return;
  };

  Array *loadedReference;
  int loadedLength = 0;

  printf("Page size: ");
  scanf("%d", &pageSize);

  do {
    printedCount = 0;
    loadedReference = loadPageToMemory(file, pageSize);
    loadedLength = getArrayLength(loadedReference);

    while (++printedCount < loadedLength) {
      printRegistry((Registry*) getAtArray(loadedReference, printedCount));
    };

    if (isArrayFull(loadedReference)) {
      printf("Keep reading? (y/n): ");
      getchar();                             // handles enter key buffer.
      shouldKeepReading = getchar() == 'y' || getchar() == 'Y';
    } else {
      shouldKeepReading = false;
      println("There are no more registries to read.");
    }

  } while (shouldKeepReading);

  fclose(file);
  pause();
}

Array *loadPageToMemory(FILE *file, int pageSize) {
  Registry *registry;
  Array *readData = initArray(pageSize);

  int readCount = 0;
  bool hasReadWholeFile;

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
