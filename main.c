#include <malloc.h>
#include <string.h>
#include <math.h>
#include "main.h"
#include "registryGenerator.h"
#include "registryReader.h"
#include "libs/utils.h"
#include "libs/SO/specifics.h"
#include "libs/chainedList/chainedList.h"

static const int kbToBytes = 1024;

static ChainedList *menuList = NULL;

void readFileForUser(){
    readPaginated();
}

void generateByNumberOfRegistries(){

    int howMany; 
    printf("How many registries:");
    scanf("%d", &howMany);

    printf("\nGenerating registries");
    writeListInFile( howMany );
}

void generateByUserChoosenSize(){
    int chosenUnit;

    printf("Choose measure unit - GB(3) MB(2) KB(1):");
    scanf("%d", &chosenUnit);

    int acc =  getScreenHeight() - 4;
    while(chosenUnit < 0 || chosenUnit > 3){
        println("Invalid entry.");
        printf("Choose measure unit - GB(3) MB(2) KB(1):");
        scanf("%d", &chosenUnit);
    }
    printf("\nGenerating registries");

    int numberOfRegistries = pow(kbToBytes, chosenUnit) / getSizeOfRegistry();

    writeListInFile( numberOfRegistries );
}

int main(int argc, char **argv)
{
    int chosen;
    return 0;
}
