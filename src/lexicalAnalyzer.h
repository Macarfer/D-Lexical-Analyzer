#include "symbolTable.h"
#include "lexical.h"
#include "errorManager.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORD_SIZE 200
#define KEY_WORDS_FILE "keyWords.h"

/*Initializates the lexical analyzer so it can be used*/
void initializeLexicalAnalyzer(const char *path);

/*Returns a symbol that contains a lexeme, and the line where it was in the code*/
symbol * getToken();

/*Frees memory and resources */
void finalizeLexicalAnalyzer();