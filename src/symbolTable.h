/*Main struct where symbols are going to be stored*/

typedef struct symbol{
	char * lexeme;
	int identifier;
	short line;
}symbol;

void initializeSymbolTable();
symbol * insertOnSymbolTable(char * lexeme, int identifier, short line, short level);
symbol * searchSymbol(char * lexeme);
void printSymbolTable();
