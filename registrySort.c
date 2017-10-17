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
  free(((Registry *) registry)->operationDate);
  free((Registry *) registry);

}

const long getFileSize(FILE *file) {
  fseek(file, 0, SEEK_END); // seek to end of file
  const long size = ftell(file); // get current file pointer
  fseek(file, 0, SEEK_SET);
  return size;
}

void doSortAndWrite(Array *pageArray, FILE *sortedPart){

  size_t arrayLen = (size_t) getArrayLength(pageArray);
  void* arrayData = (void *) pageArray->data;

  println("Sorting chunk..");
  quickSortArray(arrayData, arrayLen, &orderByDate);
  //forEach(arrayData, arrayLen, &printRegistry);
  println("Writing chunk to disk..");
  forEachWithFile(arrayData, arrayLen, sortedPart, &registryWriteConsumer);
  println("Finished chunk write to disk..");
}

void sortInChunks(FILE *file) {
  if (file == NULL) {
    return;
  }

  const long registriesQuantity = (getFileSize(file) / getSizeOfRegistry());


  //sprintf(fileNamePointer, fileNameTemplate, 1);
  FILE *sortedPartOne = fopen(".sorted_1.txt", "w");
  FILE *sortedPartTwo = fopen(".sorted_2.txt", "w");

  println("Loading first chunk to memory");
  Array *firstChunkArray = loadChunkIntoMemory(file, registriesQuantity / 2);
  doSortAndWrite(firstChunkArray, sortedPartOne);
  free(firstChunkArray->data);
  free(firstChunkArray);

  println("Loading second chunk to memory");
  Array *secondChunkArray = loadChunkIntoMemory(file, registriesQuantity / 2);
  doSortAndWrite(secondChunkArray, sortedPartTwo);
  free(secondChunkArray->data);
  free(secondChunkArray);

  fclose(sortedPartOne);
  fclose(sortedPartTwo);
}