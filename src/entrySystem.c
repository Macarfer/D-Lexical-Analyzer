#include "entrySystem.h"
#include <stdio.h>

/*Initializes all necessary structures for reading from the file*/
short initialize(){
	printf("Hello!\n");
	return 1;
};
/*Indicate the relative path to the file that is gonna be openned*/
short open(char * fileRoute);
/*Sends actual character to the lexical analyzer*/
char getNextCharacter();
/*Finalizes all structures used on this program and frees memory and structures*/
short finalize();