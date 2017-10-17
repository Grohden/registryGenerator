#include <stdio.h>
#include <stdlib.h>
#include "registry.h"

void printRegistry(void *generic) {
  const Registry *registry = (Registry *) generic;

  printf(
          REGISTRY_WRITE_STRING,
          registry->key,
          registry->sold,
          registry->operationValue,
          registry->operationDate->day,
          registry->operationDate->month,
          registry->operationDate->year
  );
}

Registry *initRegistry() {
  Registry *registry = calloc(1, sizeof(Registry));
  Date *date = calloc(1, sizeof(Date));

  date->day = 1;
  date->month = 1;
  date->year = 1970;


  registry->key = 0;
  registry->sold = 0;
  registry->operationValue = 0;
  registry->operationDate = date;

  return registry;
}

FILE *openRegistryFile(char *mode) {
  return fopen(REGISTRY_FILE_NAME, mode);
}

void freeRegistry(Registry *registry) {
  free(registry->operationDate);
  free(registry);
}