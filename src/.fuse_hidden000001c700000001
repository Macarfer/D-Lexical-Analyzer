#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

/*Text array of the document to read*/
//const char * fileToOpen = "../regression.d";
/*Initializes all necessary structures for reading from the file*/
void inputInitialize();
/*Indicate the relative path to the file that is gonna be openned*/
short open(char * fileRoute);
/*Sends actual character to the lexical analyzer*/
char getNextCharacter();

void returnCharacter();
/*Finalizes all structures used on this program and frees memory and structures*/
short finalize();

char * getLexeme();
