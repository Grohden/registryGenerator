#include <stdlib.h>
#include "hash.h"

#define MULTIPLIER (37)

static HashTable *cachedTable = NULL;

static void cacheTable(HashTable *table) {
  if (cachedTable != NULL) {
    destroyHashTable(cachedTable);
  }

  cachedTable = table;
};

void createCachedHashTable(size_t size) {
  HashTable *table = calloc(sizeof(HashTable), 1);
  table->elements = calloc(sizeof(void), size);
  table->size = size;
  cacheTable(table);
};

void destroyHashTable(HashTable *table) {
  free(table->elements);
  free(table);
}

unsigned long hash(const char *string) {
  unsigned long h;
  unsigned const char *us;

  us = (unsigned const char *) string;

  h = 0;
  while (*us != '\0') {
    h = h * MULTIPLIER + *us;
    us++;
  }

  return h;
}

void putIntoHashTable(char *string, void *structPointer) {
  if (cachedTable != NULL) {
    unsigned long indexForHash = hash(string);
    cachedTable->elements[indexForHash] = structPointer;
  }
};

void *getFromHashTable(char *string) {
  if (cachedTable != NULL) {
    unsigned long indexForHash = hash(string);
    return cachedTable->elements[indexForHash];
  } else {
    return NULL;
  }
};