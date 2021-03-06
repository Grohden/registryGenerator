#include "registryGenerator.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libs/random/random.h"
#include "libs/utils.h"

static int cachedSize = 0;

// FIXME: change this to unsigned long long
static int keyGenerationHolder = 0;

static int updateKeyGenerator() { return keyGenerationHolder++; }

static void clearKeys() { keyGenerationHolder = 0; }

static Date *generateRandomDate() {
  Date *date = calloc(1, sizeof(Date));
  date->day = getRandomBetweenRange(1, 30);
  date->month = getRandomBetweenRange(1, 12);
  date->year = getRandomBetweenRange(1980, 2060);
  return date;
}

static float getValuePercentage(double value, char percentage) {
  return (float) ((value / 100) * percentage);
}

void writeRegistryAtFile(FILE *file, Registry *registry) {
  fprintf(
          file,
          REGISTRY_WRITE_STRING,
          registry->key,
          registry->sold,
          registry->operationValue,
          registry->operationDate->day,
          registry->operationDate->month,
          registry->operationDate->year
  );
}

Registry *initRandomRegistry() {
  Registry *registry = calloc(1, sizeof(Registry));

  registry->key = updateKeyGenerator();
  registry->sold = (char) (getRandomBetweenRange(0, 2) == 0 ? 'C' : 'V');
  registry->operationValue = getRandomBetweenRange(100, 999999999);
  registry->operationDate = generateRandomDate();

  return registry;
}

void writeListInFile(double howMany) {
  if (howMany < 1) {
    println("%f is not a valid number", howMany);
    return;
  }

  clearKeys();

  FILE *registryFile = openRegistryFile("w");

  char percentageStep = (char) (howMany < 1000000 ? 10 : 5);
  float stepSize = getValuePercentage(howMany, percentageStep);
  int percentageCount = 0;
  int loaderCount = 0;
  int count = 0;

  //Init a counter
  time_t start_t, end_t;
  time(&start_t);

  Registry *registry;
  do {
    registry = initRandomRegistry();

    writeRegistryAtFile(registryFile, registry);

    if (loaderCount + stepSize < count) {
      println("%d %%", percentageCount);
      percentageCount += percentageStep;
      loaderCount += stepSize;
    }
    freeRegistry(registry);

  } while (count++ < howMany - 1);

  double diff_t;
  time(&end_t);
  diff_t = difftime(end_t, start_t);

  println("Generated %d registries in %.2f minutes", howMany, diff_t / 60);
  fclose(registryFile);
}

int getSizeOfRegistry() {
  if (cachedSize) {
    return cachedSize;
  }

  char *stringHolder = calloc(100, sizeof(char));
  Registry *registry = initRandomRegistry();
  sprintf(
    stringHolder,
    REGISTRY_WRITE_STRING, 
    registry->key,
    registry->sold,
    registry->operationValue,
    registry->operationDate->day,
    registry->operationDate->month,
    registry->operationDate->year
  );

  cachedSize = ((strlen(stringHolder) + 1 /* \n char */) * sizeof(char));
  free(stringHolder);

  return cachedSize;
}