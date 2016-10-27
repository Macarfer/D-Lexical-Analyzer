#include <stdio.h>
#include "inputSystem.h"
#include "lexicalAnalyzer.h"
#include <stdlib.h>
#include <string.h>
#include "lexical.h"

/*This is the main program of the Lexical Analyzer
basically it initializates all the components of 
the analyzer*/

int main(int argc, char const *argv[])
{
	//printf("%d\n",);
	symbol * tmp=NULL;
	initializeLexicalAnalyzer();

	//tmp=getToken();
	do{
    tmp=getToken();
	//printf("<%d> %s\n",tmp->identifier,tmp->lexeme);
	//printSymbolTable();
	}while(tmp->identifier!=DOLLAR);
	printSymbolTable();
	/* code */
	return 0;
}