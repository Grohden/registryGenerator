#include "main.h"
#include <malloc.h>
#include <math.h>
#include "libs/SO/specifics.h"
#include "libs/quickSort/quickSort.h"
#include "libs/utils.h"
#include "registryGenerator.h"
#include "registryReader.h"
#include "registrySort.h"

#define MENU_OPTIONS_NUMBER 4

static const int kbToBytes = 1024;

static char readableMeasures[3][3] = {"Kb\0", "Mb\0", "Gb\0"};

void readFileForUser() { readPaginated(); }

void printMainMenuOptions() {
  println("1 - Generate File (Size)");
  println("2 - Generate File (Number of registries)");
  println("3 - Read File");
  println("4 - Exit Program");
}

int showGUIMainMenu() {

  clearScreen();
  printMainMenuOptions();

  // Draw the seletable list and wait for the response
  int selected;
  printf("Option:");
  scanf("%d", &selected);

  while (selected > MENU_OPTIONS_NUMBER || selected < 1) {
    clearScreen();
    println("Invalid number. Provide a valid one!");
    printf("Option:");
    printMainMenuOptions();

    scanf("%d", &selected);
  }

  clearScreen();
  switch (selected) {
    case 1:
      generateByUserChosenSize();
      break;
    case 2:
      generateByNumberOfRegistries();
      break;
    case 3:
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
  writeListInFile((unsigned int) howMany);
}

void generateByUserChosenSize() {
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
  writeListInFile(floor(pow(kbToBytes, chosenUnit) / getSizeOfRegistry()) * howMany);
}

int main(int argc, char **argv) {
  writeListInFile(floor(pow(kbToBytes, 3) / getSizeOfRegistry()) * 1);
  sortInChunks(openRegistryFile("r"));
  /*
  int chosen;
  do {
    chosen = showGUIMainMenu();
  } while (chosen != 4);
  return 0;
  */
}