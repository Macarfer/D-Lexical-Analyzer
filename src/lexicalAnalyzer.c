#include "lexicalAnalyzer.h"
#include "lex.yy.c"

struct lexicalAnalyzer{
	int actualLine;
	int actualCharacter;
	char workingCharacter;
	char * auxiliarBuffer;
	symbol temporalSymbol;

} lexicalAnalyzer;


/*Starts the inital variables for allowing the use of the lexical analyzer*/
void initializeLexicalAnalyzer(const char *path){
	/*Just opens the file with the input parameter of lex*/
	if((yyin = fopen(path,"r"))==0){
		/*If the file does'nt exist we just sho an error*/
		showInputError(FILE_NOT_FOUND,path);
	}
}

/*Initial node of the automata, it takes the first letter of the pointer, stores it and goes to the next adequate node*/
symbol * getToken(){
			lexicalAnalyzer.temporalSymbol.identifier=yylex();
			lexicalAnalyzer.temporalSymbol.lexeme=yytext;
			/*If the received element is an identifier or a keyword we store it and return a pointer to it's position*/
			if(lexicalAnalyzer.temporalSymbol.identifier==IDENTIFIER || lexicalAnalyzer.temporalSymbol.identifier==KEYWORD){
				return insertOnSymbolTable(lexicalAnalyzer.temporalSymbol.lexeme,lexicalAnalyzer.temporalSymbol.identifier,lines,1);
				/*If not we just return an element containing the received parameters*/
			}else
			return &lexicalAnalyzer.temporalSymbol;
	}

/*Frees the allocated space for the lexical analyzer components*/
void finalizeLexicalAnalyzer(){
	free(lexicalAnalyzer.auxiliarBuffer);
}