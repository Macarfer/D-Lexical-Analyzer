/*Main struct where symbols are going to be stored*/

typedef struct symbol{
	char * lexeme;
	int identifier;
	short line;
}symbol;

/*Allocates resources for the symbol table*/
void initializeSymbolTable();
/*Given the parameters inserts a symbol on the table*/
symbol * insertOnSymbolTable(char * lexeme, int identifier, short line, short level);

/*Returns a symbol if the lexeme is in any symbol of the table. If not, returns NULL*/
symbol * searchSymbol(char * lexeme);
/*Prints the table in alphabetical order*/
void printSymbolTable();

/*Frees all the resources allocated for the table*/
void finalizeSymbolTable();
