#include <stdlib.h>

/*Standart errors for using during the execution of the compiler*/
#define COMMENT_NOT_CLOSED_ERROR 0
#define STRING_TOO_LONG 1
#define FILE_NOT_FOUND 2

/*Meant for displaying and handling errors of the lexicalAnalyzer*/
void showLexicalError(int code,int line,char * string);

/*Meant for displaying and handling errors of the inputSystem*/
void showInputError(int code,char const *string);