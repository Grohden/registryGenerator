#include "registrySort.h"


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
