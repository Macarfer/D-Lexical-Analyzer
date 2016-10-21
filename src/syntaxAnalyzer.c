#include "lexicalAnalyzer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	lexicalAnalyzer * lexical=NULL;
	symbolTable  * lexicalt=NULL;

	lexicalt = initializeTable(lexicalt);
	insertOnSymbolTable(&lexicalt,"abstract",0,0);
	searchSymbol(lexicalt,"abstract");
// 	initializeLexicalAnalyzer(&lexical);
// 	for(;;){
// 		//printf("%s\n",getToken(&lexical)->identifier);
// 		getToken(&lexical);
// 		getchar();
// 		printTable(lexical->sTable);
// }
	/* code */
	return 0;
}