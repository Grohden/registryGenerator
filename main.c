#include <malloc.h>
#include <string.h>
#include <math.h>
#include "main.h"
#include "registryGenerator.h"
#include "libs/utils.h"
#include "libs/textualGUI/textualGUI.h"
#include "libs/SO/specifics.h"
#include "libs/chainedList/chainedList.h"

#define SCREEN_RATIO 40

static const int kbToBytes = 1024;
static const int sizeofRegistry = 35; //bytes

static ChainedList *menuList = NULL;

int showGUIMainMenu()
{
    //First we need to set screen size
    setScreenSize(SCREEN_RATIO * 2, 40);

    if(menuList == NULL){
        menuList = initChain();
        //Add the items
        addToChain(menuList, (void *) "Generate File");
        addToChain(menuList, (void *) "Exit Program");
    }

    //Draw the seletable list and wait for the response
    int selected = drawSelectableList(menuList, true);

    Registry *r = initRegistry();

    switch(selected){
        case 0:
            generateByUserChoosenSize();
            //writeListInFile( gbToBytes / sizeofRegistry );
            pause();
            break;
    }
    
    return selected;
}

void generateByUserChoosenSize(){
    putCursorAt(0, getScreenHeight() - 5);
    int chosenUnit;

    printf("Choose measure unit - GB(3) MB(2) KB(1):");
    scanf("%d", &chosenUnit);

    int acc =  getScreenHeight() - 4;
    while(chosenUnit < 0 || chosenUnit > 3){
        println("Invalid entry.");
        printf("Choose measure unit - GB(3) MB(2) KB(1):");
        scanf("%d", &chosenUnit);
    }

    printf("\n");

    int numberOfRegistries = pow(kbToBytes, chosenUnit) /sizeofRegistry;

    writeListInFile( numberOfRegistries );
}

int main(int argc, char **argv)
{
    int chosen;

    do {
        chosen = showGUIMainMenu();
    } while(chosen != 1);

    return 0;
}