#include <malloc.h>
#include <string.h>
#include "registryGenerator.h"
#include "libs/utils.h"
#include "libs/textualGUI/textualGUI.h"
#include "libs/SO/specifics.h"
#include "libs/chainedList/chainedList.h"

#define SCREEN_RATIO 40

const int kbToBytes = 1024;
const int mbToBytes = 1024 * 1024;
const int gbToBytes = 1024 * 1024 * 1024;

void showGUIMainMenu()
{
    //First we need to set screen size
    setScreenSize(SCREEN_RATIO * 2, 40);

    //We init the chained list
    ChainedList *c = initChain();

    //Add the items
    addToChain(c, (void *) "Generate File");
    addToChain(c, (void *) "Exit Program");

    //Draw the seletable list and wait for the response
    int selected = drawSelectableList(c, true);

    Registry *r = initRegistry();

    switch(selected){
        case 0:
            writeListInFile( mbToBytes / 33 );
            pause();
            break;
        case 1:
            break;
    }
}


int main(int argc, char **argv)
{
    showGUIMainMenu();
    return 0;
}