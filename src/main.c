#include <stdio.h>
#include "inputSystem.h"
#include <stdlib.h>
#include "symbolTable.h"
#include <string.h>

#define PATH_TO_FILE "../regression.d"
/*This is the main program of the Lexical Analyzer
basically it initializates all the components of 
the analyzer*/

short processCharacter(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
short isIdentifier(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer,char * workingCharacter);
short isSeparator(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);

int main(int argc, char const *argv[])
{
	symbolTable * sTable=NULL;
	char * buffer;
	short actualLine=0;
	int actualCharacter=0;
	inputSystem * input;
	inputInitialize(&input,PATH_TO_FILE);
	//buffer=initialize();
	sTable=initializeTable(sTable);
	char *auxiliarBuffer= (char *) malloc(200);
	char workingCharacter;

	// sTable=initializeTable(sTable);
	*(auxiliarBuffer)=getNextCharacter(&input);
	processCharacter(&input,&actualCharacter,&sTable,&auxiliarBuffer,&workingCharacter);
	/*Here we declare the variables that are going to be shared between processes*/
//	printf("Caracter: %s\n",buffer);
//	printf("asdf: %c\n",*(buffer+0));
	return 0;
}

short processCharacter(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
	
	free(*auxiliarBuffer);
	*auxiliarBuffer=(char *)malloc(200);
	*(actualCharacter)=0;
	printf("I'm gonna switch: %c\n",workingCharacter);
		switch(*workingCharacter){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
				 *((auxiliarBuffer)+*actualCharacter)=workingCharacter;
					*(actualCharacter)+=1;
				//(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
				//printf("Ola: %c\n",(*auxiliarBuffer)[*actualCharacter]);
				 isIdentifier(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;
			case 32: // space
			case 46: // point
			case 10: // new line
			case 59: // ;
				*workingCharacter=getNextCharacter(input);
				processCharacter(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
				
			break;
			default:
				 isIdentifier(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;


	}
}
short isIdentifier(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
	int i=0;
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
			case 48 ... 57: // [0-9]
				(*actualCharacter)+=1;
				(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
			break;
			case 32: // space
			case 46: // point
			case 10: // new line
			case 59: // ;
				printf("I'm gonna insert: %s\n",*auxiliarBuffer);
				printf("Inserted: %s\n",insertOnSymbolTable(table,(*auxiliarBuffer),0,1)->identifier);	
				getchar();
				processCharacter(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;
			default:
				// free(*auxiliarBuffer);
				// *auxiliarBuffer=(char *)malloc(200);
				printf("Default!!\n");
				for(i;i<=strlen(*auxiliarBuffer);i++)
					*auxiliarBuffer[i]='\0';
				(*auxiliarBuffer)[0]=*workingCharacter;
				processCharacter(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
				// printf("a: %s\n",*auxiliarBuffer);
				// printf("ascii: %d\n",*workingCharacter);
			//	printf("Done!\n");
			//return 0;
			break;
		}

	}

}

short isSeparator(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
	for(;;){

	}
}