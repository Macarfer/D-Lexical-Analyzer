#include <stdio.h>
#include "inputSystem.h"
#include <stdlib.h>
#include "symbolTable.h"

#define PATH_TO_FILE "../regression.d"
/*This is the main program of the Lexical Analyzer
basically it initializates all the components of 
the analyzer*/

short processCharacter(char *buffer,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer);
short isIdentifier(char *buffer,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer);

int main(int argc, char const *argv[])
{
	symbolTable * sTable=NULL;
	char * buffer;
	short actualLine=0;
	int actualCharacter=0;
	inputSystem * input;
	inputInitialize(&input,PATH_TO_FILE);
	printf("Next character: %c",getNextCharacter(&input));
	//buffer=initialize();
	// char *auxiliarBuffer= (char *) malloc(200);


	// sTable=initializeTable(sTable);
	
	// processCharacter(buffer,&actualCharacter,&sTable,&auxiliarBuffer);
	/*Here we declare the variables that are going to be shared between processes*/
//	printf("Caracter: %s\n",buffer);
//	printf("asdf: %c\n",*(buffer+0));
	return 0;
}

short processCharacter(char *buffer,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer){
		switch(*(buffer+*actualCharacter)){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
				*((*auxiliarBuffer)+*actualCharacter)=*(buffer+*actualCharacter);
				isIdentifier(buffer,actualCharacter,table,auxiliarBuffer);
				break;
	}
}
short isIdentifier(char *buffer,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer){

	for(;;){
		switch(*(buffer+*actualCharacter)){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
			case 48 ... 57: // [0-9]
			*((*auxiliarBuffer)+*actualCharacter)=*(buffer+*actualCharacter);
			(*actualCharacter)+=1;
			break;
			default:
			printf("Inserted: %s\n",insertOnSymbolTable(table,(*auxiliarBuffer),0,1)->identifier);
			printf("Done!\n");
			return 0;
			break;
		}

	}

}