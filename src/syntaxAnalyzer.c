#include "lexicalAnalyzer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	lexicalAnalyzer * lexical=NULL;
	symbol * tmp;
	initializeLexicalAnalyzer(&lexical);
	for(;;){
		//printf("%s\n",getToken(&lexical)->identifier);
		tmp=getToken(&lexical);
		printf("<%d> %s\n",tmp->identifier,tmp->lexicalComponent);
		//printTable(lexical->sTable);
		//getchar();
}
	/* code */
	return 0;
}