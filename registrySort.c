#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "registrySort.h"
#include "registryGenerator.h"
#include "libs/array/array.h"
#include "registryReader.h"
#include "libs/quickSort/quickSort.h"
#include "libs/utils.h"


int orderByValue(void *f, void *s) {
  const Registry *one = (Registry *) f;
  const Registry *second = (Registry *) s;
  return one->operationValue <= second->operationValue;
}

int orderByType(void *f, void *s) {
  const Registry *one = (Registry *) f;
  const Registry *second = (Registry *) s;
  return one->sold <= second->sold;
}

int orderByDate(void *f, void *s) {
  const Date *one = ((Registry *) f)->operationDate;
  const Date *second = ((Registry *) s)->operationDate;

  const int oneSum = (one->year * 365) + (one->month * 30) + (one->day);
  const int secondSum = (second->year * 365) + (second->month * 30) + (second->day);

  return oneSum >= secondSum;
}

void registryWriteConsumer(void *registry, FILE *file) {
  writeRegistryAtFile(file, (Registry *) registry);
}

const long getFileSize(FILE *file) {
  fseek(file, 0, SEEK_END); // seek to end of file
  const long size = ftell(file); // get current file pointer
  fseek(file, 0, SEEK_SET);
  return size;
}

void sortInChunks(FILE *file) {
  const int arraySize = CHUNK_SIZE;

  if (file == NULL) {
    return;
  }

  const long registersInFile = (getFileSize(file) / getSizeOfRegistry());
  const char fileNameTemplate[] = ".sorted_%d.txt";
  char *fileNamePointer = (char *) calloc(strlen(fileNameTemplate), sizeof(char));
  int filePart = 0;
  int loopCount = 0;
  void *arrayData;
  Array *pageArray;
  size_t arrayLen;

  sprintf(fileNamePointer, fileNameTemplate, 1);
  FILE *sortedPart = fopen(fileNamePointer, "w");

  do {
    pageArray = loadPageToMemory(file, arraySize);
    arrayLen = (size_t) getArrayLength(pageArray);
    arrayData = (void *) pageArray->data;
    quickSortArray(arrayData, arrayLen, &orderByDate);
    forEach(arrayData, arrayLen, &printRegistry);
    forEachWithFile(arrayData, arrayLen, sortedPart, &registryWriteConsumer);
    loopCount++;
  } while (loopCount < registersInFile / 2);

  fclose(sortedPart);
  sprintf(fileNamePointer, fileNameTemplate, 2);
  sortedPart = fopen(fileNamePointer, "w");

  do {
    pageArray = loadPageToMemory(file, arraySize);
    arrayLen = (size_t) getArrayLength(pageArray);
    arrayData = (void *) pageArray->data;
    quickSortArray(arrayData, arrayLen, &orderByDate);
    forEach(arrayData, arrayLen, &printRegistry);
    forEachWithFile(arrayData, arrayLen, sortedPart, &registryWriteConsumer);
  } while (arraySize == arrayLen);

  fclose(sortedPart);
}