#include <stdio.h>
#include "entrySystem.h"
/*This is the main program of the Lexical Analyzer
basically it initializates all the components of 
the analyzer*/

int main(int argc, char const *argv[])
{
	char * buffer;
	short actualLine=0;
	int actualCharacter=0;
	buffer=initialize();
	for(;;){
		switch(*(buffer+actualCharacter)){
			case 0 ... 47:
				break;
			default:
				printf("Character: %c",*(buffer+actualCharacter));
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


