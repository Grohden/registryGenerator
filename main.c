#include "main.h"
#include <malloc.h>
#include <math.h>
#include "libs/quickSort/quickSort.h"
#include "libs/utils.h"
#include "registryGenerator.h"
#include "registryReader.h"
#include "registrySort.h"

#define IMPOSSIBLE_MESSAGE "Woa men, how did you get here? :o"

//Order menu consts
#define BY_VALUE 1
#define BY_TYPE 2
#define BY_DATE 3

//Main menu consts
#define GENERATE_SIZE 1
#define GENERATE_NUMBER 2
#define READ_MENU 3
#define SORT_MENU 4
#define EXIT_MENU 5

static const int kbToBytes = 1024;

static char readableMeasures[3][3] = {"Kb\0", "Mb\0", "Gb\0"};

void readFileForUser() { readPaginated(); }

void printMainMenuOptions() {
  println("%d - Generate File (Size)", GENERATE_SIZE);
  println("%d - Generate File (Number of registries)", GENERATE_NUMBER);
  println("%d - Read File", READ_MENU);
  println("%d - Sort File", SORT_MENU);
  println("%d - Exit Program", EXIT_MENU);
}

int showGUIMainMenu() {

  clearScreen();
  printMainMenuOptions();

  // Draw the selectable list and wait for the response
  int selected;
  printf("Option:");
  scanf("%d", &selected);

  while (selected > EXIT_MENU || selected < 1) {
    clearScreen();
    println("Invalid number. Provide a valid one!");

    printf("Option:");
    printMainMenuOptions();

    scanf("%d", &selected);
  }

  clearScreen();
  switch (selected) {
    case GENERATE_SIZE:
      generateByUserChosenSize();
      break;
    case GENERATE_NUMBER:
      generateByNumberOfRegistries();
      break;
    case READ_MENU:
      readFileForUser();
      break;
    case SORT_MENU:
      sortFileMenu();
      break;
    default:
      return EXIT_MENU;
  }

  return selected;
}

void sortFileMenu() {
  int chosenOption;

  printf("%d - Sort by transaction value\n", BY_VALUE);
  printf("%d - Sort by transaction type\n", BY_TYPE);
  printf("%d - Sort by transaction date\n", BY_DATE);
  scanf("%d", &chosenOption);

  while (chosenOption < 0 || chosenOption > 3) {
    clearScreen();
    println("Invalid option, provide a valid one:");
    printf("%d - Sort by transaction value\n", BY_VALUE);
    printf("%d - Sort by transaction type\n", BY_TYPE);
    printf("%d - Sort by transaction date\n", BY_DATE);
  }
  const int correctChoice = chosenOption;

  switch (correctChoice) {
    case BY_VALUE:
      sortInChunks(openRegistryFile("r"), &orderByValue);
      break;
    case BY_TYPE:
    println("Warning, this may take a while")
      sortInChunks(openRegistryFile("r"), &orderByType);
      break;
    case BY_DATE:
      sortInChunks(openRegistryFile("r"), &orderByDate);
      break;
    default:
    println(IMPOSSIBLE_MESSAGE);
      break;
  }

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
  int chosen;
  do {
    chosen = showGUIMainMenu();
  } while (chosen != EXIT_MENU);
  return 0;

}