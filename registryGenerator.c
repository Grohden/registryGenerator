#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "registryGenerator.h"
#include "libs/chainedList/chainedList.h"
#include "libs/SO/specifics.h"
#include "libs/random/random.h"
#include "libs/utils.h"

static const char *REGISTRY_INTERPOLATION_STRING = "%010d %c %09d %02d %02d %04d\n";
static int cachedSize = 0;

//FIXME: change this to unsigned long long
static int keyGenerationHolder = 0;

Date *generateRandomDate();

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
        registry->operationDate->day,
        registry->operationDate->month,
        registry->operationDate->year
    );
}

int updateKeyGenerator(){
    return keyGenerationHolder++;
}

Registry *initRegistry()
{
    Registry *registry = calloc(1, sizeof(Registry));

    registry->key = updateKeyGenerator();
    registry->sold = getRandomBetweenRange(0,2) == 0 ? 'C' : 'V';
    registry->operationValue = getRandomBetweenRange(100, 999999999);
    registry->operationDate = generateRandomDate();

    return registry;
}

Registry *initEmptyRegistry()
{
    Registry *registry = calloc(1, sizeof(Registry));
    Date *date = calloc(1,sizeof(Date));

    date->day   = 1;
    date->month = 1;
    date->year  = 1970;
    
    
    registry->key = 0;
    registry->sold = 0;
    registry->operationValue = 0;
    registry->operationDate = date;

    return registry;
}

void writeSingleInFile(Registry *registry)
{
    FILE *registryFile = fopen(REGISTRY_FILE_NAME, "w");

    fprintfRegistry(registryFile, registry);
    fclose(registryFile);
}

void writeListInFile(unsigned int howMany){
    if(!howMany){
        println("0 is not a valid number");
        return;
    }

    FILE *registryFile = fopen(REGISTRY_FILE_NAME, "w");

    Registry * registry;

    const int percentageStep = 10;
    float stepSize = getValuePercentage(howMany, percentageStep); 
    int percentageCount = 0;
    int loaderCount = 0;
    int count = 0;

    time_t start_t, end_t;
    time(&start_t);

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

    double diff_t;
    time(&end_t);
    diff_t = difftime(end_t, start_t);

    printAtBottom("Generated %d registries in %.2f minutes", howMany, diff_t/60);
    pause();
    fclose(registryFile);
}

Date *generateRandomDate(){
    Date *date   = calloc(1,sizeof(Date));
    date->day    = getRandomBetweenRange(1,30);
    date->month  = getRandomBetweenRange(1,12);
    date->year   = getRandomBetweenRange(1980,2060);
    return date;
}


int getSizeOfRegistry(){
    if(cachedSize){
        return cachedSize;
    }

    char *stringHolder = calloc(100,1);
    Registry *registry = initRegistry();
    sprintf(
        stringHolder,
        REGISTRY_INTERPOLATION_STRING,
        registry->key,
        registry->sold,
        registry->operationValue,
        registry->operationDate 
    );

    return cachedSize = strlen(stringHolder) * sizeof(char);
}