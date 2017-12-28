#include "registryReader.h"
#include <stdlib.h>
#include "./libs/utils.h"

void readPaginated() {
  int pageSize;
  int printedCount;
  bool shouldKeepReading;

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
    loadedReference = loadChunkIntoMemory(file, pageSize);
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

Array *loadChunkIntoMemory(FILE *file, int pageSize) {
  Registry *registry;
  Array *readData = initArray((size_t) pageSize);

  int readCount = 0;
  bool hasReadWholeFile;

  do {
    registry = initRegistry();

    hasReadWholeFile = loadSingleRegistry(file, registry);

      if(!hasReadWholeFile){
        addToArray(readData, (int) registry);
      }
    } while (++readCount < pageSize && !hasReadWholeFile);

  return readData;
}

bool loadSingleRegistry(FILE *openReadFile, Registry *destiny) {
  return fscanf(openReadFile, REGISTRY_READ_STRING,
                &destiny->key,
                &destiny->sold,
                &destiny->operationValue,
                &destiny->operationDate->day,
                &destiny->operationDate->month,
                &destiny->operationDate->year
  ) == EOF;
}
