#include <stdlib.h>
#include "registryGenerator.h"
#include "libs/ChainedList/chainedList.h"
#include "libs/utils.h"

Registry *initRegistry(){
    Registry *registry = calloc(1,sizeof(Registry));

    return registry;
}

void generateEntries(int howMany){
    ChainedList * list = initChain();
    repeat(howMany) {
        addToChain(list, initRegistry());
    }
};