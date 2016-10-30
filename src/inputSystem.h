#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errorManager.h"

/*Sets the block size of the fileSystem*/
#define N 4

/*Initializes all necessary structures for reading from the file*/
void inputInitialize(char const *);

/*Sends actual character to the lexical analyzer*/
char getNextCharacter();


/*Allows the lexicalAnalyzer to return a character to the input system*/
void returnCharacter();

/*Finalizes all structures used on this program and frees memory and structures*/
short finalizeInputSystem();

