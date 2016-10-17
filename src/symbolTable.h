/*Main struct where symbols are going to be stored*/


typedef struct symbol{
	char * identifier;
	short line;
	struct symbol * left;
	struct symbol * right;
} sybmol;


typedef struct levelNode{
	short level;
	levelNode * nextNode;
	symbol * firstSymbolOfLevel;
}levelNode;

typedef struct symbolTable{
	levelNode * first;
}symbolTable;

symbolTable * initializeTable(symbolTable *);
symbolTable * insertOnSymbolTable(symbolTable * table,const char * indentifier, short line, short level);

short deleteTable(symbolTable *);
//void modify();

//void search():