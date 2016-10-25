#include "lexicalAnalyzer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	lexicalAnalyzer * lexical=NULL;
	symbol * tmp;
	initializeLexicalAnalyzer(&lexical);
	//tmp=getToken(&lexical);
	do{
    tmp=getToken(&lexical);
	printf("<%d> %s\n",tmp->identifier,tmp->lexicalComponent);

	}while(tmp->identifier!=0);
	printf("Taboa de simbolos: \n");
	printTable(lexical->sTable);
	/* code */
	return 0;
}
