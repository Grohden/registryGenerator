#include "main.h"
#include <malloc.h>
#include <math.h>
#include <string.h>
#include "libs/SO/specifics.h"
#include "libs/chainedList/chainedList.h"
#include "libs/textualGUI/textualGUI.h"
#include "libs/utils.h"
#include "registry.h"
#include "registryGenerator.h"
#include "registryReader.h"

#define SCREEN_RATIO 40

static const int kbToBytes = 1024;

static ChainedList *menuList = NULL;

static char readableMeasures[3][3] = {"Kb\0", "Mb\0", "Gb\0"};

void readFileForUser() { readPaginated(); }

int showGUIMainMenu() {
  // First we need to set screen size
  setScreenSize(SCREEN_RATIO * 2, 40);

  if (menuList == NULL) {
    menuList = initChain();
    // Add the items
    addToChain(menuList, (void *)"Generate File (Size)");
    addToChain(menuList, (void *)"Generate File (Number of registries)");
    addToChain(menuList, (void *)"Read File");
    addToChain(menuList, (void *)"Exit Program");
  }

  // Draw the seletable list and wait for the response
  int selected = drawSelectableList(menuList, true);

  switch (selected) {
    case 0:
      clearScreen();
      generateByUserChoosenSize();
      break;
    case 1:
      clearScreen();
      generateByNumberOfRegistries();
      break;
    case 2:
      clearScreen();
      readFileForUser();
      break;
  }

  return selected;
}

void generateByNumberOfRegistries() {
  int howMany;
  printf("How many registries:");
  scanf("%d", &howMany);

  println("\nGenerating registries");
  writeListInFile(howMany);
}

void generateByUserChoosenSize() {
  int chosenUnit;
  int howMany;

  printf("Choose measure unit - Gb(3) Mb(2) Kb(1):");
  scanf("%d", &chosenUnit);

  while (chosenUnit < 0 || chosenUnit > 3) {
    println("Invalid entry.");
    printf("Choose measure unit - Gb(3) Mb(2) Kb(1):");
    scanf("%d", &chosenUnit);
  }

  printf("How many of this measure? ");
  scanf("%d", &howMany);

  println("\nGenerating %d %s's of registries", howMany,
          readableMeasures[chosenUnit - 1]);
  writeListInFile(floor(pow(kbToBytes, chosenUnit) / getSizeOfRegistry()) *
                  howMany);
}

int main(int argc, char **argv) {
  int chosen;

  do {
    chosen = showGUIMainMenu();
  } while (chosen != getChainLength(menuList) - 1);

  return 0;
}
