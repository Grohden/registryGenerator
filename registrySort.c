#include <stdio.h>
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
  freeRegistry((Registry *) registry);

}

const long getFileSize(FILE *file) {
  fseek(file, 0, SEEK_END); // seek to end of file
  const long size = ftell(file); // get current file pointer
  fseek(file, 0, SEEK_SET);
  return size;
}

void doSortAndWrite(Array *pageArray, FILE *sortedPart, int (*predicate)(void *, void *)) {

  size_t arrayLen = (size_t) getArrayLength(pageArray);
  void *arrayData = (void *) pageArray->data;

  println("Sorting chunk..");
  quickSortArray(arrayData, arrayLen, predicate);
  //forEach(arrayData, arrayLen, &printRegistry);
  println("Writing chunk to disk..");
  forEachWithFile(arrayData, arrayLen, sortedPart, &registryWriteConsumer);
  println("Finished chunk write to disk..");
}

void sortInChunks(FILE *file, int ((*predicate)(void *, void *))) {
  if (file == NULL) {
    return;
  }

  const long registriesQuantity = (getFileSize(file) / getSizeOfRegistry());

  FILE *sortedPartOne = fopen(".sorted_1.txt", "w");
  FILE *sortedPartTwo = fopen(".sorted_2.txt", "w");

  println("Loading first chunk to memory");
  Array *firstChunkArray = loadChunkIntoMemory(file, registriesQuantity / 2);
  doSortAndWrite(firstChunkArray, sortedPartOne, predicate);
  freeArray(firstChunkArray);

  println("Loading second chunk to memory");
  Array *secondChunkArray = loadChunkIntoMemory(file, registriesQuantity / 2);
  doSortAndWrite(secondChunkArray, sortedPartTwo, predicate);
  freeArray(secondChunkArray);

  fclose(sortedPartOne);
  fclose(sortedPartTwo);

  mergeSortedFiles(".sorted_1.txt", ".sorted_2.txt", REGISTRY_FILE_NAME, predicate);
}


void mergeSortedFiles(char *one, char *second, char *destiny, int ((*predicate)(void *, void *))) {
  const char *readMode = "r";
  FILE *sortedPartOne = fopen(one, readMode);
  FILE *sortedPartTwo = fopen(second, readMode);
  FILE *destinyFile = fopen(destiny, "w");

  Registry *fromFirstFile = initRegistry();
  Registry *fromSecondFile = initRegistry();

  //Load first registries
  bool hasLoadedAllFirst = loadSingleRegistry(sortedPartOne, fromFirstFile);
  bool hasLoadedAllSecond = loadSingleRegistry(sortedPartOne, fromSecondFile);

  int countInFirst = 0;
  int countInSecond = 0;


  println("Merging %s  and %s to %s", one, second, destiny);
  do {
    if (predicate(fromSecondFile, fromFirstFile)) {
      writeRegistryAtFile(destinyFile, fromFirstFile);
      countInFirst++;
      hasLoadedAllFirst = loadSingleRegistry(sortedPartOne, fromFirstFile);
    } else {
      writeRegistryAtFile(destinyFile, fromSecondFile);
      countInSecond++;
      hasLoadedAllSecond = loadSingleRegistry(sortedPartTwo, fromSecondFile);
    }
  } while (!hasLoadedAllFirst && !hasLoadedAllSecond);

  //Writes any remaining registry in ONE of the files
  while (!hasLoadedAllFirst) {
    writeRegistryAtFile(destinyFile, fromFirstFile);
    hasLoadedAllFirst = loadSingleRegistry(sortedPartOne, fromFirstFile);
  }

  while (!hasLoadedAllSecond) {
    writeRegistryAtFile(destinyFile, fromSecondFile);
    hasLoadedAllSecond = loadSingleRegistry(sortedPartTwo, fromSecondFile);
  }

  freeRegistry(fromFirstFile);
  freeRegistry(fromSecondFile);
}
