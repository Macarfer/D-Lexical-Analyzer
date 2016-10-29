#include "inputSystem.h"
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

void initializeLexicalAnalyzer(char const *);
symbol * getToken();
