#include <stdio.h>
//Macros
#ifndef _ROHDEN_UTILS
#define _ROHDEN_UTILS 1

#define println(...) printf(__VA_ARGS__); printf("\n");

#define pause() system("pause")

//This should be a "macro"
#define clearScreen() system("cls")

//TODO: review this, they can't be useful without lambdas!
void forEach(void **array, size_t size, void ((*consumer)(void *)));

void forEachWithFile(void **array, size_t size, FILE *file, void ((*consumer)(void *, FILE *)));

#endif // _ROHDEN_UTILS
