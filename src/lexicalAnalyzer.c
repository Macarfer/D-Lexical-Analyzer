#include "lexicalAnalyzer.h"


struct lexicalAnalyzer{
	int actualLine;
	int actualCharacter;
	char workingCharacter;
	char * auxiliarBuffer;
	symbol temporalSymbol;

} lexicalAnalyzer;

/*Functions that represent nodes of a hypothetical automata*/
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

/*Starts the inital variables for allowing the use of the lexical analyzer*/
void initializeLexicalAnalyzer(){
	lexicalAnalyzer.actualLine=1;
	lexicalAnalyzer.actualCharacter=0;
	lexicalAnalyzer.auxiliarBuffer=malloc(MAX_WORD_SIZE);

		/*
		* I must initializate the symbol table with the reserved words of the language
		* using this method I can check wether a string is a keyword of it isn't
		*/

	FILE *lexical;
	lexical = fopen(KEY_WORDS_FILE, "r");
	char * lexeme=malloc(MAX_WORD_SIZE);
	for(;!feof(lexical);){
		fscanf(lexical, "%s\n",lexeme);
		insertOnSymbolTable(lexeme,RESERVED,lexicalAnalyzer.actualLine,1);
	}
	/*freeing the resources allocated for storing the keywords*/
	fclose(lexical);
	free(lexeme);

}

/*Initial node of the automata, it takes the first letter of the pointer, stores it and goes to the next adequate node*/
symbol * getToken(){
	lexicalAnalyzer.actualCharacter=0;
	lexicalAnalyzer.workingCharacter=getNextCharacter();
	lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;

	switch(lexicalAnalyzer.workingCharacter){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
			return isNonLiteralString();
			case 32: // space
			return getToken();
			case 10: // new line
			lexicalAnalyzer.actualLine+=1;
			return getToken();
			case 46: // point
			return isSucessionOfPoints();
			case 40: // (
			/*The parentheses is a token itself so we just return it to the syntax analyzer*/
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=PARENTHESES_OPEN;
			return &lexicalAnalyzer.temporalSymbol;
			case 41: // )
			/*The parentheses is a token itself so we just return it to the syntax analyzer*/
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=PARENTHESES_CLOSE;
			return &lexicalAnalyzer.temporalSymbol;
			case 59: // ;
			/*The semicolon is a token itself so we just return it to the syntax analyzer*/
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=SEMICOLON;
			return &lexicalAnalyzer.temporalSymbol;
			case 91: // [
			/*The square bracket is a token itself so we just return it to the syntax analyzer*/
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=SQUARE_BRACKET_OPEN;
			return &lexicalAnalyzer.temporalSymbol;
			case 93: // ]
			/*The square bracket is a token itself so we just return it to the syntax analyzer*/
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=SQUARE_BRACKET_CLOSE;
			return &lexicalAnalyzer.temporalSymbol;
			case 44: // ,
				/*The comma is a token itself so we just return it to the syntax analyzer*/
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
				lexicalAnalyzer.temporalSymbol.identifier=COMMA;
				return &lexicalAnalyzer.temporalSymbol;
			case 123: // {
				/*The curly bracket is a token itself so we just return it to the syntax analyzer*/
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
				lexicalAnalyzer.temporalSymbol.identifier=CURLY_BRACKET_OPEN;
				return &lexicalAnalyzer.temporalSymbol;
			case 125: // }
			/*The curly bracket is a token itself so we just return it to the syntax analyzer*/
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=CURLY_BRACKET_CLOSE;
			return &lexicalAnalyzer.temporalSymbol;
			case 61: // =
			/*There are only two symbols that start with = -> == and =*/
			/*If the character is an equal then it means it is a ==*/
			if(getNextCharacter()==61){
				lexicalAnalyzer.temporalSymbol.lexeme="==";
				lexicalAnalyzer.temporalSymbol.identifier=DOUBLE_EQUAL;
				return &lexicalAnalyzer.temporalSymbol;
			}else{
				/*If the character is anything else, the lexeme is = and we must return the actual character*/
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				returnCharacter();
				strcpy(lexicalAnalyzer.temporalSymbol.lexeme,lexicalAnalyzer.auxiliarBuffer);
				lexicalAnalyzer.temporalSymbol.identifier=EQUAL;
				return &lexicalAnalyzer.temporalSymbol;
			}
			/*Each character can be the beggining of a more complex string so, each of them has its own function*/

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
				/*If we reached the end of the text, then we return the end of transmission character*/
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

/*This function checks alphanumeric strings and decides if they're keywords or just identifiers*/
	symbol * isNonLiteralString(){
		for(;;){
			/*Checks in each iteration if the word size is higher than the allocated space for it*/
			if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
				showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);
			}
			/*In each iteration a we get a character until we receive one that doesn't belong to an allowed string*/
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
			/*When a strange character is received the right string is set*/
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				/*The strange character is returned to be processed next time*/
				returnCharacter();
				/*If the string selected is in the symbol table, the identifier it already has is assigned and the symbol sent to the syntax analyzer*/
				if(searchSymbol(lexicalAnalyzer.auxiliarBuffer)!=NULL){
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,lexicalAnalyzer.actualLine,searchSymbol(lexicalAnalyzer.auxiliarBuffer)->identifier,1);
				}
				else 
					/*If the string is not in the symbol table, then it means that it is an identifier and it is added and returned to the lexical analyzer*/
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);
	            break;
		}

	}
	

}

/*Checks if a sucession of points is valid or not*/
symbol * isSucessionOfPoints(){
	for(;;){
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		switch(lexicalAnalyzer.workingCharacter){
			/*Reads points up to three*/
			case 46: // point
			/*While points are being read, this code separates them in groups of three and returns them*/
				lexicalAnalyzer.actualCharacter+=1;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
				if(lexicalAnalyzer.actualCharacter==2){
				lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer.auxiliarBuffer;
				lexicalAnalyzer.temporalSymbol.identifier=TRIPLE_POINT;
				return &lexicalAnalyzer.temporalSymbol;
				}
			break;
			/*In case a character different than a point is received, we evaluate the number of points received previously
			and return the right symbol*/
			default:
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			if(lexicalAnalyzer.actualCharacter<3){
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
				return getToken();
			}
			break;
		}
	}
	
}

/*This functions handles the comments*/
symbol * isComment(){
	int nestedComments=0;
	for(;;){
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		lexicalAnalyzer.actualCharacter+=1;
		lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
		/*This switch allows to choose between the different kind of comments that are possible*/
		switch(lexicalAnalyzer.workingCharacter){
			/*This comments are ignored except when the substring that starts a comment is reached */
			case 42: // *
			for(;;){
				/*Checks in each iteration if the word size is higher than the allocated space for it*/
				if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
					showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

				}
				/*Stores all the characters so, if there's an error it can be shown where it happened*/
				lexicalAnalyzer.workingCharacter=getNextCharacter();
				lexicalAnalyzer.actualCharacter+=1;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
				/*If the string  slash_asterisk_asterisk is reached then we trigger the nestedComments value to 1*/
				if(lexicalAnalyzer.workingCharacter!=47 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==42 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-2]==42){// *
					nestedComments=1;
				}
				/*If we reach an end of line, the line counter is increased*/
				if(lexicalAnalyzer.workingCharacter==10){ //\n
					lexicalAnalyzer.actualLine+=1;
					/*If we reach the end of the comment and the string slash_asterisk_asterisk was on it, then we store it as a STRING_LITERAL*/
				}else if(lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]==47 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==42 && nestedComments){
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
					nestedComments=0;
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,STRING_LITERAL,lexicalAnalyzer.actualLine,1);
					/*If we reach the end of the comment but, the string  slash_asterisk_asterisk wasn't present on the comment, then we don't save the string*/
				}else if(lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]==47 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==42){
					return getToken();
					/*If we reach the end of the file without closing the comment, then an error has ocurred*/
				}else if(lexicalAnalyzer.workingCharacter==0){
					showLexicalError(COMMENT_NOT_CLOSED_ERROR,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
					returnCharacter();
					return getToken();
				}
			}
			break;
			case 43: // +
			/*This comments can be stacked so, the proccess of proccessing them must have this in account*/
			for(;;){
				/*Checks in each iteration if the word size is higher than the allocated space for it*/
				if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
					showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

				}
				lexicalAnalyzer.workingCharacter=getNextCharacter();
				lexicalAnalyzer.actualCharacter+=1;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
				if(lexicalAnalyzer.workingCharacter==10){ //\n
					lexicalAnalyzer.actualLine+=1;
				/*While we're processing the string, if whe reach the substring +/ and there aren't nested comments open then we end the process*/
				}else if(lexicalAnalyzer.workingCharacter==47 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==43 && nestedComments==0){
					return getToken();
				/*If there are a sequence that opens a new comment, then we increase the value of nestedComments*/
				}else if(lexicalAnalyzer.workingCharacter==43 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==47){
					nestedComments+=1;
				/*If we found a closing sequence and, nestedComments is higher than 0, then we decrease it's value*/
				}else if(lexicalAnalyzer.workingCharacter==47 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter-1]==43 && nestedComments>0){
					nestedComments-=1;
				/*Any other combination is incorrect and should generate an error*/
				}else if(lexicalAnalyzer.workingCharacter==0){
					showLexicalError(COMMENT_NOT_CLOSED_ERROR,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
					returnCharacter();
					return getToken();
				}
			}
			break;
			case 47: // /
			/*If whe find an / then we just skip all until we find an end of line*/
			for(;;){
				lexicalAnalyzer.workingCharacter=getNextCharacter();
				if(lexicalAnalyzer.workingCharacter==10){
					returnCharacter();
					return getToken();
				}
			}
			break;
			/*If none of the previous values are entered, then we are  in a position where the lexeme we're expecting is / and the following one belongs to another
			string*/
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

/*This function takes a number and checks if it can be a binary one*/
symbol * isBinaryNumber(){
	lexicalAnalyzer.workingCharacter=getNextCharacter();
	/*In a binary number, after the first 0 there must be a B or b if there's not, it is something else*/
	if(lexicalAnalyzer.workingCharacter=='B' || lexicalAnalyzer.workingCharacter=='b'){
		lexicalAnalyzer.actualCharacter+=1;
		lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
		for(;;){
			/*Checks in each iteration if the word size is higher than the allocated space for it*/
			if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
				showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

			}
			lexicalAnalyzer.workingCharacter=getNextCharacter();
			switch(lexicalAnalyzer.workingCharacter){
				/*If we receive a 0 or a 1 then we add it to the lexeme*/
					case 48 ... 49: // [0-1]
					lexicalAnalyzer.actualCharacter+=1;
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
					break;
					/*When we receive something different, it means the string is over and we reached the beggining of another*/
					default:
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
					returnCharacter();
					lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
					lexicalAnalyzer.temporalSymbol.identifier=INTEGER_LITERAL;
					return &lexicalAnalyzer.temporalSymbol;
					break;
				}

			}
		}
		/*If the second value isn't a b or B, then the number we're processing isn't a binary one*/
		else{
			returnCharacter();
			return isIntegerNumber();
		}

	}

	symbol * isIntegerNumber(){
		for(;;){
			/*Checks in each iteration if the word size is higher than the allocated space for it*/
			if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
				showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

			}
			lexicalAnalyzer.workingCharacter=getNextCharacter();
			switch(lexicalAnalyzer.workingCharacter){
				/*While we receive numbers from 0 to 9 we store them*/
			case 48 ... 57: // [0-9]
			lexicalAnalyzer.actualCharacter+=1;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			break;
			/*When we receive a point we asume that it's gonna be a float point number*/
			case 46 :// .
			lexicalAnalyzer.actualCharacter+=1;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			return isFloatNumber();
			break;
			/*We can also accept e as an indicator that we're working with a float number*/
			case 101: //e
			returnCharacter();
			return isFloatNumber();
			break;
			/*underscore can be used in numbers, but it isn't processed cause it doesn't adds information*/
			case 95: // _
			break;
			/*When we receive something different from the previous contemplations then it means that we've reached the end of
			the number, so we store it.*/
			default:
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			returnCharacter();
			lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			lexicalAnalyzer.temporalSymbol.identifier=INTEGER_LITERAL;
			return &lexicalAnalyzer.temporalSymbol;
			break;
		}

	}
	
}

/*This function handles the detection of float point numbers and scientific notation ones*/
symbol * isFloatNumber(){
	for(;;){
		/*Checks in each iteration if the word size is higher than the allocated space for it*/
		if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
			showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
			return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

		}
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		switch(lexicalAnalyzer.workingCharacter){
			/*If we find numbers between 0 and 9 then we add them to the detected value*/
			case 48 ... 57: // [0-9]
			lexicalAnalyzer.actualCharacter+=1;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			break;
			/*If we find an e or E then we know we're dealing with a scientific expression and we switch to the exponential part of the number*/
			case 69: //E
			case 101: //e
			lexicalAnalyzer.actualCharacter+=1;
			lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			lexicalAnalyzer.workingCharacter=getNextCharacter();
			/*After the e/E there can be a + or a - or none of them, so with this if whe take that into account*/
				if(lexicalAnalyzer.workingCharacter==43 || lexicalAnalyzer.workingCharacter==45){ //+-
					lexicalAnalyzer.actualCharacter+=1;
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
				}
				for(;;){
					/*After that, we just have to proccess the number that indicates the exponencial value as an integer*/
					lexicalAnalyzer.workingCharacter=getNextCharacter();
					switch(lexicalAnalyzer.workingCharacter){
						case 48 ... 57: // [0-9]
						lexicalAnalyzer.actualCharacter+=1;
						lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
						break;
						case 95: // _
						break;
						/*When a value not valid is detected we stop the number recognition and return the last character to the input system*/
						default:
						lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
						returnCharacter();
						lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
						lexicalAnalyzer.temporalSymbol.identifier=FLOAT_LITERAL;
						return &lexicalAnalyzer.temporalSymbol;
					}
				}
				/*When a value not valid is detected we stop the number recognition and return the last character to the input system*/
				default:
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				returnCharacter();
				lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
				lexicalAnalyzer.temporalSymbol.identifier=FLOAT_LITERAL;
				return &lexicalAnalyzer.temporalSymbol;

			}

		}


	}

/*This function processes string litterals, this is, strings between "" */
	symbol * isStringLiteral(){
		for(;;){
			/*Checks in each iteration if the word size is higher than the allocated space for it*/
			if(lexicalAnalyzer.actualCharacter==MAX_WORD_SIZE-1){
				showLexicalError(STRING_TOO_LONG,lexicalAnalyzer.actualLine,lexicalAnalyzer.auxiliarBuffer);
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,lexicalAnalyzer.actualLine,1);

			}
			/*We select a new character*/
			lexicalAnalyzer.workingCharacter=getNextCharacter();
			/*If the actual character is a " and the previous one is different than \ it means we've reached the end of the string
			If the previous character where \ then, the " should be added as a normal character to the string*/
			if(lexicalAnalyzer.workingCharacter==34 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]!=92){ // " "\"
				lexicalAnalyzer.actualCharacter+=1;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,STRING_LITERAL,lexicalAnalyzer.actualLine,1);
			}
				lexicalAnalyzer.actualCharacter+=1;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
		}

	}

/*This function processes all the strings begining with the < character*/
	symbol *processLessThan(){
		for(;;){
			lexicalAnalyzer.workingCharacter=getNextCharacter();
			switch(lexicalAnalyzer.workingCharacter){
				/*If the next character is = then we have a valid string*/
			 case 61:// =
			 lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
			 lexicalAnalyzer.temporalSymbol.identifier=LESS_THAN_EQUAL;
			 return &lexicalAnalyzer.temporalSymbol;
			case 60:// <
			/*If the next character is < then we've got two options*/
			lexicalAnalyzer.workingCharacter=getNextCharacter();
				/*If we have an equal, then we've got the symbol <<=*/
				if(lexicalAnalyzer.workingCharacter==61){//equal
					lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
					lexicalAnalyzer.temporalSymbol.identifier=DOUBLE_LESS_THAN_EQUAL;
					return &lexicalAnalyzer.temporalSymbol;
					/*If not, we just have the lexeme << and we must return the actual character*/
				}else{
					returnCharacter();
					lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
					lexicalAnalyzer.temporalSymbol.identifier=DOUBLE_LESS_THAN;
					return &lexicalAnalyzer.temporalSymbol;
				}
			case 62: // >
			/*Same as before, if we have > then, we have two options*/
			lexicalAnalyzer.workingCharacter=getNextCharacter();
			/*An equal and we have the lexeme <>= */
				if(lexicalAnalyzer.workingCharacter==61){//equal
					lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
					lexicalAnalyzer.temporalSymbol.identifier=LESS_THAN_MORE_THAN_EQUAL;
					return &lexicalAnalyzer.temporalSymbol;
					/*Or something else and we have just the lexeme <>*/
				}else{
					returnCharacter();
					lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
					lexicalAnalyzer.temporalSymbol.identifier=LESS_THAN_MORE_THAN;
					return &lexicalAnalyzer.temporalSymbol;
				}
				/*If we don't have any of the characters shown before, then the lexeme we're searching for is just < and we have to return the actual character*/
				default:
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				returnCharacter();
				lexicalAnalyzer.temporalSymbol.lexeme=lexicalAnalyzer .auxiliarBuffer;
				lexicalAnalyzer.temporalSymbol.identifier=LESS_THAN;
				return &lexicalAnalyzer.temporalSymbol;


			}
		}

	}
	/*Processes lexemes begining with + character.
	It compares the next character with allowed values and returns them. If the character adquired is none
	of the valid ones it is returned and the symbol + is returned*/
	symbol *processPlus(){
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
/*Processes lexemes begining with * character.
	It compares the next character with allowed values and returns them. If the character adquired is none
	of the valid ones it is returned and the symbol * is returned*/
		symbol *processAsterisk(){
			for(;;){
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
	/*Processes lexemes begining with - character.
	It compares the next character with allowed values and returns them. If the character adquired is none
	of the valid ones it is returned and the symbol - is returned*/
symbol *processDash(){
	for(;;){
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

/*Frees the allocated space for the lexical analyzer components*/
void finalizeLexicalAnalyzer(){
	free(lexicalAnalyzer.auxiliarBuffer);
}