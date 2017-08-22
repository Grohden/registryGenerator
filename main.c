#include <malloc.h>
#include <string.h>
#include <math.h>
#include "main.h"
#include "registry.h"
#include "registryGenerator.h"
#include "registryReader.h"
#include "libs/utils.h"
#include "libs/textualGUI/textualGUI.h"
#include "libs/SO/specifics.h"
#include "libs/chainedList/chainedList.h"

#define SCREEN_RATIO 40

static const int kbToBytes = 1024;

static ChainedList *menuList = NULL;

void readFileForUser(){
    readPaginated();
}

int showGUIMainMenu()
{
    //First we need to set screen size
    setScreenSize(SCREEN_RATIO * 2, 40);

    if(menuList == NULL){
        menuList = initChain();
        //Add the items
        addToChain(menuList, (void *) "Generate File (Size)");
        addToChain(menuList, (void *) "Generate File (Number of registries)");
        addToChain(menuList, (void *) "Read File");
        addToChain(menuList, (void *) "Exit Program");
    }

    //Draw the seletable list and wait for the response
    int selected = drawSelectableList(menuList, true);

    switch(selected){
        case 0:
            generateByUserChoosenSize();
            break;
        case 1:
            generateByNumberOfRegistries();
        break;
        case 2:
            readFileForUser();
            break;
    }
    
    return selected;
}

void generateByNumberOfRegistries(){

    int howMany; 
    printf("How many registries:");
    scanf("%d", &howMany);

    printf("\nGenerating registries");
    writeListInFile( howMany );
}

void generateByUserChoosenSize(){
    putCursorAt(0, getScreenHeight() - 5);
    int chosenUnit;

    printf("Choose measure unit - GB(3) MB(2) KB(1):");
    scanf("%d", &chosenUnit);

    while(chosenUnit < 0 || chosenUnit > 3){
        println("Invalid entry.");
        printf("Choose measure unit - GB(3) MB(2) KB(1):");
        scanf("%d", &chosenUnit);
    }
    printf("\nGenerating registries");

    int numberOfRegistries = floor(pow(kbToBytes, chosenUnit) / getSizeOfRegistry());

    writeListInFile( numberOfRegistries );
}

int main(int argc, char **argv)
{
    int chosen;

    do {
        chosen = showGUIMainMenu();
    } while(chosen != getChainLength(menuList) - 1);

    return 0;
}
