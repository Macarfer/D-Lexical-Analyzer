#include "inputSystem.h"
#include "symbolTable.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define PATH_TO_FILE "../regression.d"

#define   IDENTIFIER 300
#define   STRING_LITERAL 301
#define   CHARACTER_LITERAL 302
#define   INTEGER_LITERAL 303
#define   FLOAT_LITERAL 304
#define   RESERVED 305 

typedef struct lexicalAnalyzer{
	inputSystem * input;
	symbolTable * sTable;
	symbolTable * keyWordsTable;
	int actualLine;
	int actualCharacter;
	char *auxiliarBuffer;
	char workingCharacter;

} lexicalAnalyzer;

void initializeLexicalAnalyzer(lexicalAnalyzer **);
symbol * getToken(lexicalAnalyzer **);