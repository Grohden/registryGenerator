CC=gcc
GCCFLAGS=-Wall -std=c99

##################### TASKS #####################

build: MAIN
	$(CC) $(GCCFLAGS) *.o -o main

debug: MAIN
	$(CC) $(GCCFLAGS) -g *.o -o main

MAIN: READER GENERATOR TEXTUAL_GUI
	$(CC) $(GCCFLAGS) -g -c main.c

REGISTRY:
	$(CC) $(GCCFLAGS) -g -c registry.c

GENERATOR: REGISTRY
	$(CC) $(GCCFLAGS) -g -c registryGenerator.c

READER: REGISTRY
	$(CC) $(GCCFLAGS) -g -c registryReader.c


######### TEXTUAL GUI AND ITS DEPENDENCIES ########

TextualGUIBasePath = ./libs

TEXTUAL_GUI: UTILS SO CHAINED_LIST 
	$(CC) $(GCCFLAGS) -c $(TextualGUIBasePath)/textualGUI/textualGUI.c

CHAINED_LIST:
	$(CC) $(GCCFLAGS) -c $(TextualGUIBasePath)/chainedList/chainedList.c

UTILS:
	$(CC) $(GCCFLAGS) -c $(TextualGUIBasePath)/random/random.c

SO:
	$(CC) $(GCCFLAGS) -c $(TextualGUIBasePath)/SO/specifics.c

######################## ########################
