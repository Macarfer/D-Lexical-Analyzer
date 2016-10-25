#include <stdio.h>
#include "inputSystem.h"
#include "lexicalAnalyzer.h"
#include <stdlib.h>
#include <string.h>

/*This is the main program of the Lexical Analyzer
basically it initializates all the components of 
the analyzer*/

int main(int argc, char const *argv[])
{
	symbol * tmp=NULL;
	initializeLexicalAnalyzer();
	do{
    tmp=getToken();
	printf("<%d> %s\n",tmp->identifier,tmp->lexeme);

	}while(strcmp(tmp->lexeme,"$")!=0);

	/* code */
	return 0;
}