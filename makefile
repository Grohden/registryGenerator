CC=gcc
GCCFLAGS=-Wall

##################### TASKS #####################

build: MAIN
	$(CC) $(GCCFLAGS) *.o -o main

debug: MAIN
	$(CC) $(GCCFLAGS) -g *.o -o main

MAIN: GENERATOR TEXTUAL_GUI
	$(CC) -g -c main.c

GENERATOR:
	$(CC) -g -c registryGenerator.c

######### TEXTUAL GUI AND ITS DEPENDENCYS ########

TextualGUIBasePath = ./libs

TEXTUAL_GUI: UTILS SO CHAINED_LIST 
	$(CC) -c $(TextualGUIBasePath)/textualGUI/textualGUI.c

CHAINED_LIST:
	$(CC) -c $(TextualGUIBasePath)/chainedList/chainedList.c

UTILS:
	$(CC) -c $(TextualGUIBasePath)/random/random.c

SO:
	$(CC) -c $(TextualGUIBasePath)/SO/specifics.c

######################## ########################