#include <stdio.h>
#include "inputSystem.h"
#include "lexicalAnalyzer.h"
#include <stdlib.h>
#include <string.h>
#include "lexical.h"

/*This is the main program of the Lexical Analyzer
basically it initializates all the components of 
the analyzer*/
#define PATH_TO_FILE "./regression.d"

int main(int argc, char const *argv[])
{
	symbol * tmp=NULL;

	/*If an argument isn't used the default route is*/
	if(argc > 1)
		inputInitialize(argv[1]);
	else
		inputInitialize(PATH_TO_FILE);

	/*Initialization of all components*/
	initializeSymbolTable();
	initializeLexicalAnalyzer();
	tmp=getToken();


	printf("\n\nIdentifier\t\tLexeme\n\n");

	/*Loop that prints every token that is returned from the lexical analyzer*/
	while(tmp->identifier!=DOLLAR){
		printf("<%d>\t\t\t%s\n",tmp->identifier,tmp->lexeme);
		tmp=getToken();
	}

	/*Last the symbol table is printed. It must contain only identifiers and keywords*/
	printf("\n********************************************************************\n 			Symbol Table\n********************************************************************\n");
	printSymbolTable();

	/*All components are finalized*/
	finalizeInputSystem();
	finalizeSymbolTable();
	finalizeLexicalAnalyzer();
	return 0;
}