#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4096

typedef struct inputSystem{
	FILE * fileToOpen;
	char * doubleBuffer;
	char * initialPointer;
	char * frontPointer;
	int readNumber;
}inputSystem;
/*Text array of the document to read*/
//const char * fileToOpen = "../regression.d";
/*Initializes all necessary structures for reading from the file*/
void inputInitialize(inputSystem **,const char *);
/*Indicate the relative path to the file that is gonna be openned*/
short open(char * fileRoute);
/*Sends actual character to the lexical analyzer*/
char getNextCharacter(inputSystem ** system);

void returnCharacter(inputSystem ** system);
/*Finalizes all structures used on this program and frees memory and structures*/
short finalize();

char * getLexeme();
