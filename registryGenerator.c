#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "registryGenerator.h"
#include "libs/chainedList/chainedList.h"
#include "libs/SO/specifics.h"
#include "libs/random/random.h"
#include "libs/utils.h"

static const char *REGISTRY_FILE_NAME = "registryFile.txt";
static const char *REGISTRY_INTERPOLATION_STRING = "%010d %c %09d %s\n";
static const char *DATE_INTERPOLATION_STRING = "%02d/%02d/%04d";

static int keyGenerationHolder = 0;


char *generateRandomDate();

float getValuePercentage(int value, char percentage){
    return ((value/100) * percentage);
}

void fprintfRegistry(FILE * f,Registry *registry)
{
    fprintf(
        f,
        REGISTRY_INTERPOLATION_STRING,
        registry->key,
        registry->sold,
        registry->operationValue,
        registry->operationDate 
    );
}

int updateKeyGenerator(){
    return keyGenerationHolder++;
}

unsigned long long getRandomDate(){
    return getRandomNumber();
}

Registry *initRegistry()
{
    Registry *registry = calloc(1, sizeof(Registry));

    registry->key = updateKeyGenerator();
    registry->sold = getRandomBetweenRange(0,2) == 0 ? 'C' : 'V';
    registry->operationValue = getRandomBetweenRange(100,999999999);
    registry->operationDate = generateRandomDate();

    return registry;
}

void writeSingleInFile(Registry *registry)
{
    FILE *registryFile = fopen(REGISTRY_FILE_NAME, "w");

    fprintfRegistry(registryFile, registry);
    fclose(registryFile);
}

void writeListInFile(int howMany){
    FILE *registryFile = fopen(REGISTRY_FILE_NAME, "w");

    Registry * registry;

    const int percentageStep = 10;
    float stepSize = getValuePercentage(howMany, percentageStep); 
    int percentageCount = 0;
    int loaderCount = 0;
    int count = 0;
    
    do {
        registry = initRegistry();

        fprintfRegistry(registryFile, registry);
        if(loaderCount + stepSize < count){
            printAtBottom("%d %%", percentageCount);
            percentageCount +=  percentageStep;
            loaderCount += stepSize;
        }

        free(registry);    
    } while(count++ < howMany - 1);

    printAtBottom("Generated %d registries", howMany);
    fclose(registryFile);
}

char *generateRandomDate(){
    int day = getRandomBetweenRange(1,30);
    int month = getRandomBetweenRange(1,12);
    int year = getRandomBetweenRange(1980,2060);
    char *date = calloc(10,sizeof(char));
    
    sprintf(
        date,
        DATE_INTERPOLATION_STRING,
        day,
        month,
        year
    );

    return date;
}
