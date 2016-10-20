#include "inputSystem.h"
#include "symbolTable.h"

#define PATH_TO_FILE "../regression.d"
typedef struct lexicalAnalyzer{
	inputSystem * input;
	symbolTable * sTable;
	int actualLine;
	int actualCharacter;
	char *auxiliarBuffer;
	char workingCharacter;
} lexicalAnalyzer;

void initializeLexicalAnalyzer(lexicalAnalyzer **);
symbol * getToken(lexicalAnalyzer **);