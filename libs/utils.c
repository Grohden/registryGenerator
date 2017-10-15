#include "utils.h"

// Consumers

void forEach(void **array, size_t size, void ((*consumer)(void *))) {
  int index = 0;
  for (index = 0; index < size; index++) {
    consumer(array[index]);
  }
}

void forEachWithFile(void **array, size_t size, FILE *file, void ((*consumer)(void *, FILE *))) {
  int index = 0;
  for (index = 0; index < size; index++) {
    consumer(array[index], file);
  }
}