/*Main struct where symbols are going to be stored*/


typedef struct symbol{
	char * lexicalComponent;
	int identifier;
	short line;
	struct symbol * left;
	struct symbol * right;
} symbol;


typedef struct levelNode{
	short level;
	struct levelNode * nextNode;
	symbol * firstSymbolOfLevel;
}levelNode;

typedef struct symbolTable{
	levelNode * first;
}symbolTable;

symbolTable * initializeTable(symbolTable *);
symbol * insertOnSymbolTable(symbolTable ** table,const char * lexicalComponent, int identifier, short line, short level);

short deleteTable(symbolTable *);
//void modify();

symbol * searchSymbol(symbolTable * ,char * indentifier);

void printTable(symbolTable *table);
