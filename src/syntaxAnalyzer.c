#include "lexicalAnalyzer.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	lexicalAnalyzer * lexical=NULL;
	initializeLexicalAnalyzer(&lexical);
	for(;;){
		getToken(&lexical);
		getchar();
}
	/* code */
	return 0;
}