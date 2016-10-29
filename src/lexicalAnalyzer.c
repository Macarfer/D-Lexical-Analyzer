#include "lexicalAnalyzer.h"


struct lexicalAnalyzer{
	int actualLine;
	int actualCharacter;
	char workingCharacter;
	char * auxiliarBuffer;
	symbol temporalSymbol;

} lexicalAnalyzer;


symbol * isNonLiteralString();
symbol * isSucessionOfPoints();
symbol * isComment();
symbol * isIntegerNumber();
symbol * isStringLiteral();
symbol * isFloatNumber();
symbol * isBinaryNumber();
symbol * processLessThan();
symbol * processDash();
symbol * processAsterisk();
symbol * processPlus();

void initializeLexicalAnalyzer(char const * path_to_file){
	lexicalAnalyzer.actualLine=1;
	lexicalAnalyzer.actualCharacter=0;
	lexicalAnalyzer.auxiliarBuffer=malloc(MAX_WORD_SIZE);
	inputInitialize(path_to_file);

		/*
		* I must initializate the symbol table with the reserved words of the language
		* using this method I can check wether a string is a reserved word of it isn't
		*/

	FILE *lexical;
	lexical = fopen(KEY_WORDS_FILE, "r");
	char * lexeme=malloc(MAX_WORD_SIZE);
	for(;!feof(lexical);){
		fscanf(lexical, "%s\n",lexeme);
		insertOnSymbolTable(lexeme,RESERVED,lexicalAnalyzer.actualLine,1);
	}
	fclose(lexical);
	free(lexeme);

}

symbol * getToken(){
	lexicalAnalyzer.actualCharacter=0;
	lexicalAnalyzer.workingCharacter=getNextCharacter();
	// printf("I'm gonna switch: %d\n",lexicalAnalyzer.workingCharacter);
	lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;

	switch(lexicalAnalyzer.workingCharacter){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
				 // (lexicalAnalyzer.auxiliarBuffer+lexicalAnalyzer.actualCharacter)=lexicalAnalyzer.workingCharacter;
			return isNonLiteralString();
			case 32: // space
			return getToken();
			case 10: // new line
			lexicalAnalyzer.actualLine+=1;
			return getToken();
			case 46: // point
			return isSucessionOfPoints();
			case 40: // (
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=PARENTHESES_OPEN;
			return &lexicalAnalyzer.temporalSymbol;
				//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,PARENTHESES_OPEN,lexicalAnalyzer.actualLine,1);
			case 41: // )
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=PARENTHESES_CLOSE;
			return &lexicalAnalyzer.temporalSymbol;
				//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,PARENTHESES_CLOSE,lexicalAnalyzer.actualLine,1);
			case 59: // ;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=SEMICOLON;
			return &lexicalAnalyzer.temporalSymbol;
				//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,SEMICOLON,lexicalAnalyzer.actualLine,1);
			case 91: // [
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=SQUARE_BRACKET_OPEN;
			return &lexicalAnalyzer.temporalSymbol;
				//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,SQUARE_BRACKET_OPEN,lexicalAnalyzer.actualLine,1);
			case 93: // ]
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=SQUARE_BRACKET_CLOSE;
			return &lexicalAnalyzer.temporalSymbol;
				//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,SQUARE_BRACKET_CLOSE,lexicalAnalyzer.actualLine,1);
			case 44: // ,
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=COMMA;
			return &lexicalAnalyzer.temporalSymbol;
				//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,COMMA,lexicalAnalyzer.actualLine,1);
			case 123: // {
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
				lexicalAnalyzer.temporalSymbol.identifier=CURLY_BRACKET_OPEN;
				return &lexicalAnalyzer.temporalSymbol;
				//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,CURLY_BRACKET_OPEN,lexicalAnalyzer.actualLine,1);
			case 125: // }
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=CURLY_BRACKET_CLOSE;
			return &lexicalAnalyzer.temporalSymbol;
				//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,CURLY_BRACKET_CLOSE,lexicalAnalyzer.actualLine,1);

			case 61: // =
			if(getNextCharacter()==61){
					//printf("I've inserted: ==\n");
				lexicalAnalyzer.temporalSymbol.lexeme="==";
				lexicalAnalyzer.temporalSymbol.identifier=DOUBLE_EQUAL;
				return &lexicalAnalyzer.temporalSymbol;

			}else{
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter();
				strcpy(lexicalAnalyzer.temporalSymbol.lexeme,lexicalAnalyzer.auxiliarBuffer);
				lexicalAnalyzer.temporalSymbol.identifier=EQUAL;
				return &lexicalAnalyzer.temporalSymbol;
					//insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,lexicalAnalyzer.actualLine,0,1);
			}

			case 60: // <
			return processLessThan();

			case 42: // *
			return processAsterisk();

			case 43: // +
			return processPlus();

			case 45: // -
			return processDash();

			case 47:// /
			return isComment();
			break;
			case 48: // 0
			return isBinaryNumber();
			case 49 ... 57: // [1-9]
			return isIntegerNumber();
			case 34: // 34
			return isStringLiteral();

			case 0:
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=DOLLAR;
			return &lexicalAnalyzer.temporalSymbol;
			break;
			default:
			return NULL;
			break;

		}
	}

	symbol * isNonLiteralString(){
		for(;;){
			if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
				showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

			}
			lexicalAnalyzer.workingCharacter=getNextCharacter();
			switch(lexicalAnalyzer.workingCharacter){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
			case 48 ... 57: // [0-9]
			lexicalAnalyzer.actualCharacter+=1;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			break;
			default:
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				//printf("I've inserted: %s\n",*auxiliarBuffer);
			returnCharacter();
				//printTable(*table);
			if(searchSymbol(lexicalAnalyzer.auxiliarBuffer)!=NULL){
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,lexicalAnalyzer.actualLine,searchSymbol(lexicalAnalyzer.auxiliarBuffer)->identifier,1);
			}
			else 
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);
                 //return( ( insertOnSymbolTable(table,*auxiliarBuffer,searchSymbol(*keyWords,*auxiliarBuffer)->identifier,lexicalAnalyzer.actualLine,1)) || (insertOnSymbolTable(table,*auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1)));
			break;
		}

	}
	

}

symbol * isSucessionOfPoints(){
	for(;;){
		if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
			showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
			return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

		}
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		switch(lexicalAnalyzer.workingCharacter){
			case 46: // point
			lexicalAnalyzer.actualCharacter+=1;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			break;
			default:
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			if(lexicalAnalyzer.actualCharacter<3){
				//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter();
				lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer.auxiliarBuffer;
				switch(lexicalAnalyzer.actualCharacter){
					case 0:
					lexicalAnalyzer.temporalSymbol.identifier=POINT;
					return &lexicalAnalyzer.temporalSymbol;
					case 1:
					lexicalAnalyzer.temporalSymbol.identifier=DOUBLE_POINT;
					return &lexicalAnalyzer.temporalSymbol;
					case 2:
					lexicalAnalyzer.temporalSymbol.identifier=TRIPLE_POINT;
					return &lexicalAnalyzer.temporalSymbol;
				}
			}else{
				returnCharacter();
					//printf("Too much points!\n");
				return getToken();
			}
			break;
		}
	}
	
}

symbol * isComment(){
	int nestedComments=0;
	for(;;){
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		lexicalAnalyzer.actualCharacter+=1;
		lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
		switch(lexicalAnalyzer.workingCharacter){
			case 42: // *
			for(;;){
				if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
					showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

				}
				lexicalAnalyzer.workingCharacter=getNextCharacter();
				lexicalAnalyzer.actualCharacter+=1;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
				if(lexicalAnalyzer.workingCharacter!=47 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==42 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-2]==42){// *
					nestedComments=1;
				}
				if(lexicalAnalyzer.workingCharacter==10){ //\n
					lexicalAnalyzer.actualLine+=1;
				}else if(lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]==47 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==42 && nestedComments){
					//nestedComments=0;
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
					nestedComments=0;
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,STRING_LITERAL,lexicalAnalyzer.actualLine,1);
						//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);
				}else if(lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]==47 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==42){
					return getToken();
				}else if(lexicalAnalyzer.workingCharacter==0){
					showLexicalError(COMMENT_NOT_CLOSED_ERROR,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
					returnCharacter();
					return getToken();
				}
			}
			break;
			case 43: // +

			for(;;){

				if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
					showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

				}
				lexicalAnalyzer.workingCharacter=getNextCharacter();
				lexicalAnalyzer.actualCharacter+=1;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
				if(lexicalAnalyzer.workingCharacter==10){ //\n
					lexicalAnalyzer.actualLine+=1;
				}else if(lexicalAnalyzer.workingCharacter==47 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==43 && nestedComments==0){
					return getToken();
				}else if(lexicalAnalyzer.workingCharacter==43 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==47){
					nestedComments+=1;
				}else if(lexicalAnalyzer.workingCharacter==47 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==43 && nestedComments>0){
					nestedComments-=1;
				}else if(lexicalAnalyzer.workingCharacter==0){
					showLexicalError(COMMENT_NOT_CLOSED_ERROR,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
					returnCharacter();
					return getToken();
				}
				// printf("Parella: %c%c\n",lexicalAnalyzer.auxiliarBuffer[0],lexicalAnalyzer.workingCharacter);
				// getchar();
				//lexicalAnalyzer.auxiliarBuffer[0]=lexicalAnalyzer.workingCharacter;
				//lexicalAnalyzer.workingCharacter=getNextCharacter();
			}
			break;
			case 47: // /
			for(;;){
				lexicalAnalyzer.workingCharacter=getNextCharacter();
				if(lexicalAnalyzer.workingCharacter==10){
					returnCharacter();
					return getToken();
				}
			}
			break;
			default:
			returnCharacter();
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=SLASH;
			return &lexicalAnalyzer.temporalSymbol;
			break;
		}
	}

}

symbol * isBinaryNumber(){
	lexicalAnalyzer.workingCharacter=getNextCharacter();
	if(lexicalAnalyzer.workingCharacter=='B' || lexicalAnalyzer.workingCharacter=='b'){
		lexicalAnalyzer.actualCharacter+=1;
		lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
		for(;;){
			if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
				showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

			}
			lexicalAnalyzer.workingCharacter=getNextCharacter();
			switch(lexicalAnalyzer.workingCharacter){
					case 48 ... 49: // [0-1]
					lexicalAnalyzer.actualCharacter+=1;
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
					break;
					case 65 ... 90: // [A-Z]
					case 97 ... 122: // [a-z]
					case 50 ... 57:
					return getToken();
					break;
					default:
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
						//printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter();
					lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
					lexicalAnalyzer.temporalSymbol.identifier=INTEGER_LITERAL;
					return &lexicalAnalyzer.temporalSymbol;
						//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,INTEGER_LITERAL,lexicalAnalyzer.actualLine,1);
					break;
				}

			}
		}
		else{
			returnCharacter();
			return isIntegerNumber();
		}

	}

	symbol * isIntegerNumber(){
		for(;;){
			if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
				showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

			}
			lexicalAnalyzer.workingCharacter=getNextCharacter();
			switch(lexicalAnalyzer.workingCharacter){
			case 48 ... 57: // [0-9]
			lexicalAnalyzer.actualCharacter+=1;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			break;
			case 46 :// .
			lexicalAnalyzer.actualCharacter+=1;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			return isFloatNumber();
			break;
			case 101: //e
			returnCharacter();
			return isFloatNumber();
			break;
			case 95: // _
			break;
			default:
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				//printf("I've inserted: %s\n",*auxiliarBuffer);
			returnCharacter();
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=INTEGER_LITERAL;
			return &lexicalAnalyzer.temporalSymbol;
				//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,INTEGER_LITERAL,lexicalAnalyzer.actualLine,1);
			break;
		}

	}
	
}

symbol * isFloatNumber(){
	for(;;){
		if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
			showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
			return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

		}
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		switch(lexicalAnalyzer.workingCharacter){
			case 48 ... 57: // [0-9]
			lexicalAnalyzer.actualCharacter+=1;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			break;
			case 69: //E
			case 101: //e
			lexicalAnalyzer.actualCharacter+=1;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			lexicalAnalyzer.workingCharacter=getNextCharacter();
				if(lexicalAnalyzer.workingCharacter==43 || lexicalAnalyzer.workingCharacter==45){ //+-
					lexicalAnalyzer.actualCharacter+=1;
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
				}
				for(;;){
					lexicalAnalyzer.workingCharacter=getNextCharacter();
					switch(lexicalAnalyzer.workingCharacter){
						case 48 ... 57: // [0-9]
						lexicalAnalyzer.actualCharacter+=1;
						lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
						break;
						case 95: // _
						break;
						default:
						lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
							//printf("I've inserted: %s\n",*auxiliarBuffer);
						returnCharacter();
						lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
						lexicalAnalyzer.temporalSymbol.identifier=FLOAT_LITERAL;
						return &lexicalAnalyzer.temporalSymbol;
							//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,FLOAT_LITERAL,lexicalAnalyzer.actualLine,1);

					}
				}
				default:
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter();
				lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
				lexicalAnalyzer.temporalSymbol.identifier=FLOAT_LITERAL;
				return &lexicalAnalyzer.temporalSymbol;
				//return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,FLOAT_LITERAL,lexicalAnalyzer.actualLine,1);

			}

		}


	}

	symbol * isStringLiteral(){
		for(;;){
			if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
				showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

			}
			lexicalAnalyzer.workingCharacter=getNextCharacter();
				if(lexicalAnalyzer.workingCharacter==34 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]!=92){ // " "\"
					lexicalAnalyzer.actualCharacter+=1;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					//returnCharacter();
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,STRING_LITERAL,lexicalAnalyzer.actualLine,1);
			}
			lexicalAnalyzer.actualCharacter+=1;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
		}

	}

	symbol *processLessThan(){
		for(;;){
			if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
				showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

			}
			lexicalAnalyzer.workingCharacter=getNextCharacter();
			switch(lexicalAnalyzer.workingCharacter){
			 case 61:// =
			 lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			 lexicalAnalyzer.temporalSymbol.identifier=LESS_THAN_EQUAL;
			 return &lexicalAnalyzer.temporalSymbol;
			case 60:// <
			lexicalAnalyzer.workingCharacter=getNextCharacter();
				if(lexicalAnalyzer.workingCharacter==61){//equal
					lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
					lexicalAnalyzer.temporalSymbol.identifier=DOUBLE_LESS_THAN_EQUAL;
					return &lexicalAnalyzer.temporalSymbol;
				}else{
					returnCharacter();
					lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
					lexicalAnalyzer.temporalSymbol.identifier=DOUBLE_LESS_THAN;
					return &lexicalAnalyzer.temporalSymbol;
				}
			case 62: // >
			lexicalAnalyzer.workingCharacter=getNextCharacter();
				if(lexicalAnalyzer.workingCharacter==61){//equal
					lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
					lexicalAnalyzer.temporalSymbol.identifier=LESS_THAN_MORE_THAN_EQUAL;
					return &lexicalAnalyzer.temporalSymbol;
				}else{
					returnCharacter();
					lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
					lexicalAnalyzer.temporalSymbol.identifier=LESS_THAN_MORE_THAN;
					return &lexicalAnalyzer.temporalSymbol;
				}
				default:
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				returnCharacter();
				lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
				lexicalAnalyzer.temporalSymbol.identifier=LESS_THAN;
				return &lexicalAnalyzer.temporalSymbol;


			}
		}

	}

	symbol *processPlus(){
		if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
			showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
			return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

		}
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		switch(lexicalAnalyzer.workingCharacter){
			 case 43: // +
			 lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			 lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			 lexicalAnalyzer.temporalSymbol.identifier=DOUBLE_PLUS;
			 return &lexicalAnalyzer.temporalSymbol;
			 case 61: // =
			 lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			 lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			 lexicalAnalyzer.temporalSymbol.identifier=PLUS_EQUAL;
			 return &lexicalAnalyzer.temporalSymbol;
			 default:
			 returnCharacter();
			 lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			 lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			 lexicalAnalyzer.temporalSymbol.identifier=DOUBLE_PLUS;
			 return &lexicalAnalyzer.temporalSymbol;


			}

		}

		symbol *processAsterisk(){
			for(;;){
				if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
					showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

				}
				lexicalAnalyzer.workingCharacter=getNextCharacter();
				switch(lexicalAnalyzer.workingCharacter){
			case 61: // =
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=ASTERISK_EQUAL;
			return &lexicalAnalyzer.temporalSymbol;
			default:
			returnCharacter();
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=ASTERISK;
			return &lexicalAnalyzer.temporalSymbol;


		}
	}
	
}

symbol *processDash(){
	for(;;){
		if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
			showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
			return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

		}
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		switch(lexicalAnalyzer.workingCharacter){
			 case 61: // =
			 lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			 lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			 lexicalAnalyzer.temporalSymbol.identifier=HORIZONTAL_BAR_EQUAL;
			 return &lexicalAnalyzer.temporalSymbol;
			 case 45:// -
			 lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			 lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			 lexicalAnalyzer.temporalSymbol.identifier=DOUBLE_HORIZONTAL_BAR;
			 return &lexicalAnalyzer.temporalSymbol;
			 default:
			 returnCharacter();
			 lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			 lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			 lexicalAnalyzer.temporalSymbol.identifier=HORIZONTAL_BAR;
			 return &lexicalAnalyzer.temporalSymbol;
			 break;

			}
		}

	}
