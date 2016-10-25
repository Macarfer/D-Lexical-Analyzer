#include "lexicalAnalyzer.h"



struct lexicalAnalyzer{
	int actualLine;
	int actualCharacter;
	char workingCharacter;
	char * auxiliarBuffer;

} lexicalAnalyzer;


//symbol * getToken();
symbol * isNonLiteralString();
symbol * isSeparator();
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

void initializeLexicalAnalyzer(){
		lexicalAnalyzer.actualLine=0;
		lexicalAnalyzer.actualCharacter=0;
		lexicalAnalyzer.auxiliarBuffer=malloc(200);
		inputInitialize();

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
			case 10: // new line
				return getToken();
				//
			case 46: // point
				return isSucessionOfPoints();
			case 40: // (
			case 41: // )
			case 59: // ;
			case 91: // [
			case 93: // ]
			case 44: // ,
			case 123: // {
			case 125: // }

				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				 //printf("I've inserted: %s\n",lexicalAnalyzer.auxiliarBuffer);
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,0,0,1);

			case 61: // =
				if(getNextCharacter()==61){
					//printf("I've inserted: ==\n");
					return insertOnSymbolTable("==",0,0,1);
				}else{
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter();
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,0,0,1);
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
				return insertOnSymbolTable("$",0,0,1);
			break;
			default:
				return NULL;
				break;

	}
}

symbol * isNonLiteralString(){
	for(;;){
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
				// if(searchSymbol(lexicalAnalyzer.auxiliarBuffer)!=NULL){
				// 	return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,0,0,1);
				// }
				// else
			return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,IDENTIFIER,0,1);
                 //return( ( insertOnSymbolTable(table,*auxiliarBuffer,searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1)) || (insertOnSymbolTable(table,*auxiliarBuffer,IDENTIFIER,0,1)));
			break;
		}

 	}
	

 }

symbol * isSeparator(){
		for(;;){
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		switch(lexicalAnalyzer.workingCharacter){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
			case 48 ... 57: // [0-9]
				lexicalAnalyzer.actualCharacter+=1;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			break;
			case 32: // space
			case 46: // point
			case 10: // new line
			case 59: // ;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter();
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,0,0,1);
			break;
			default:

			break;
		}

	}
	
}

symbol * isSucessionOfPoints(){
	for(;;){
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
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,0,0,1);
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
		switch(lexicalAnalyzer.workingCharacter){
			case 42: // *
			lexicalAnalyzer.auxiliarBuffer[0]='\0';
			for(;;){
				lexicalAnalyzer.workingCharacter=getNextCharacter();
				if(lexicalAnalyzer.workingCharacter==42){
					
				}
				if(lexicalAnalyzer.workingCharacter==47 && lexicalAnalyzer.auxiliarBuffer[0]==42){
					return getToken();
				}
				// getchar();
				lexicalAnalyzer.auxiliarBuffer[0]=lexicalAnalyzer.workingCharacter;
				//lexicalAnalyzer.workingCharacter=getNextCharacter();
			}
			break;
			case 43: // +
			lexicalAnalyzer.auxiliarBuffer[0]='\0';
			for(;;){
				lexicalAnalyzer.workingCharacter=getNextCharacter();
				if(lexicalAnalyzer.workingCharacter==47 && lexicalAnalyzer.auxiliarBuffer[0]==43 && nestedComments==0){
					return getToken();
				}else if(lexicalAnalyzer.workingCharacter==43 && lexicalAnalyzer.auxiliarBuffer[0]==47){
					nestedComments+=1;
				}else if(lexicalAnalyzer.workingCharacter==47 && lexicalAnalyzer.auxiliarBuffer[0]==43 && nestedComments>0){
					nestedComments-=1;
				}
				// printf("Parella: %c%c\n",lexicalAnalyzer.auxiliarBuffer[0],lexicalAnalyzer.workingCharacter);
				// getchar();
				lexicalAnalyzer.auxiliarBuffer[0]=lexicalAnalyzer.workingCharacter;
				//lexicalAnalyzer.workingCharacter=getNextCharacter();
		}
			break;
			case 47: // /
				for(;;){
					lexicalAnalyzer.workingCharacter=getNextCharacter();
					if(lexicalAnalyzer.workingCharacter==10){
						return getToken();
					}
				}
			break;
			default:

				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter();
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,0,0,1);
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
						return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,INTEGER_LITERAL,0,1);
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
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,INTEGER_LITERAL,0,1);
			break;
		}

	}
	
}

symbol * isFloatNumber(){
	for(;;){
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
							return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,FLOAT_LITERAL,0,1);

						}
				}
			default:
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
				//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter();
				return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,FLOAT_LITERAL,0,1);

		}

	}

	
}

symbol * isStringLiteral(){
		for(;;){
			lexicalAnalyzer.workingCharacter=getNextCharacter();
				if(lexicalAnalyzer.workingCharacter==34 && lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]!=92){ // " "\"
					lexicalAnalyzer.actualCharacter+=1;
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					//returnCharacter();
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,STRING_LITERAL,0,1);
				}
				lexicalAnalyzer.actualCharacter+=1;
				lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			}
	
 }

symbol *processLessThan(){
	for(;;){
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		switch(lexicalAnalyzer.workingCharacter){
			// case:
			// break;
			// case:
			// break;
			default:
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					//returnCharacter();
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,0,0,1);


		}
	}
	
}

symbol *processPlus(){
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		switch(lexicalAnalyzer.workingCharacter){
			 case 43: // +
			 case 61: // +
			 lexicalAnalyzer.actualCharacter+=1;
			 lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter]=lexicalAnalyzer.workingCharacter;
			 lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
			//printf("I've inserted: %s\n",*auxiliarBuffer);
			//returnCharacter();
			return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,0,0,1);
			 break;
			default:
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter();
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,0,0,1);


		}
	
	}

symbol *processAsterisk(){
	for(;;){
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		switch(lexicalAnalyzer.workingCharacter){
			// case:
			// break;
			// case:
			// break;
			default:
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter();
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,0,0,1);


		}
	}
	
}

symbol *processDash(){
	for(;;){
		lexicalAnalyzer.workingCharacter=getNextCharacter();
		switch(lexicalAnalyzer.workingCharacter){
			// case:
			// break;
			// case:
			// break;
			default:
					lexicalAnalyzer.auxiliarBuffer[lexicalAnalyzer.actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter();
					return insertOnSymbolTable(lexicalAnalyzer.auxiliarBuffer,0,0,1);
			break;

		}
	}
	
}
