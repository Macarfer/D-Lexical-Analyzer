#include <stdio.h>
#include "entrySystem.h"
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


	sTable=initializeTable(sTable);
	printf("Table direction from main: %p\n",sTable);
	sTable=insertOnSymbolTable(sTable,"include",0,1);
	printf("Level: %d\n",(sTable->first->level));
	sTable=insertOnSymbolTable(sTable,"anclude",0,1);
	printf("Levels: %p\n",(sTable->first->firstSymbolOfLevel));
	/*for(;;){
		switch(*(buffer+actualCharacter)){
			case 0 ... 47:
				break;
			default:
				//printf("Character: %c",*(buffer+actualCharacter));
				actualCharacter++;
				//insert(buffer,1);
				getchar();
				break;
		}
	}
	/*Here we declare the variables that are going to be shared between processes*/
//	printf("Caracter: %s\n",buffer);
//	printf("asdf: %c\n",*(buffer+0));
	return 0;
}


