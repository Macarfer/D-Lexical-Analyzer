#include <stdio.h>
#include "inputSystem.h"
#include <stdlib.h>
#include "symbolTable.h"
/*This is the main program of the Lexical Analyzer
basically it initializates all the components of 
the analyzer*/

int main(int argc, char const *argv[])
{
	symbolTable * sTable=NULL;
	char * buffer;
	short actualLine=0;
	int actualCharacter=0;
	buffer=initialize();
	char *auxiliarBuffer= (char *) malloc(200);


	sTable=initializeTable(sTable);
	for(;;){
		switch(*(buffer+actualCharacter)){
			case 32:
			printf("I've inserted: %s\n",insertOnSymbolTable(&sTable,auxiliarBuffer,0,1)->identifier);
				break;
			default:
				printf("Character: %c\n",*(buffer+actualCharacter));
				*(auxiliarBuffer+actualCharacter)=*(buffer+actualCharacter);
				//insert(buffer,1);
				//getchar();
				printf("Bufer: %s\n",auxiliarBuffer);

				actualCharacter++;
				getchar();
				break;
		}
	}
	/*Here we declare the variables that are going to be shared between processes*/
//	printf("Caracter: %s\n",buffer);
//	printf("asdf: %c\n",*(buffer+0));
	return 0;
}


