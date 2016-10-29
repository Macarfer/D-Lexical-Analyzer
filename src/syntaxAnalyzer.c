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
	symbol * tmp=NULL;
	if(argc > 1)
		initializeLexicalAnalyzer(argv[1]);
	else
	initializeLexicalAnalyzer("../regression.d");
	
	printf("\n\nIdentifier\t\tLexeme\n\n");
	tmp=getToken();
	while(tmp->identifier!=DOLLAR){
	printf("<%d>\t\t\t%s\n",tmp->identifier,tmp->lexeme);
	tmp=getToken();
	//printSymbolTable();
	}

	printf("\n********************************************************************\n 			Symbol Table\n********************************************************************\n");
	printSymbolTable();

	finalizeInputSystem();
	/* code */
	return 0;
}