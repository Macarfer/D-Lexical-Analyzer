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
	inputInitialize();
	printf("%c\n",getNextCharacter());
	printf("%c\n",getNextCharacter());
	printf("%c\n",getNextCharacter());
	printf("%c\n",getNextCharacter());
	printf("%c\n",getNextCharacter());
	printf("%c\n",getNextCharacter());
	printf("%c\n",getNextCharacter());
	printf("%c\n",getNextCharacter());

	printf("%s\n",getLexeme());
	/* code */
	return 0;
}