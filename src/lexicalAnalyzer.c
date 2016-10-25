#include "lexicalAnalyzer.h"

symbol * processCharacter(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);
symbol * isNonLiteralString(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer,char * workingCharacter);
symbol * isSeparator(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);
symbol * isSucessionOfPoints(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);
symbol * isComment(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);
symbol * isIntegerNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);
symbol * isStringLiteral(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);
symbol * isFloatNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);
symbol * isBinaryNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);
symbol * processLessThan(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);
symbol * processDash(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);
symbol * processAsterisk(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);
symbol * processPlus(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter);

void initializeLexicalAnalyzer(lexicalAnalyzer ** analyzer){
	if(*analyzer==NULL){
		*analyzer=malloc(sizeof(lexicalAnalyzer));
		inputInitialize(&((*analyzer)->input),PATH_TO_FILE);
		(*analyzer)->sTable=initializeTable((*analyzer)->sTable);
		(*analyzer)->actualLine=0;
		(*analyzer)->actualCharacter=0;
		(*analyzer)->auxiliarBuffer=(char *)malloc(200);

		/*
		* Now I create a new table where I'm gonna store all the reserved words
		* with this metod I can check if one word is reserved or it's a simple identifier.
		*/
		(*analyzer)->keyWordsTable=initializeTable((*analyzer)->keyWordsTable);
		char * auxiliarBuffer= malloc(200);
		char * temporalBuffer = malloc(200);
		inputSystem * tmpInput=NULL;
		int actualCharacter;
		char workingCharacter;
		inputInitialize(&tmpInput,"./keyWords.h");
		actualCharacter=0;
		for(;;){
			workingCharacter=getNextCharacter(&tmpInput);
			//printf("I'm gonna switch: %d\n",workingCharacter);
		if(workingCharacter==9){ // horizontal tab
			(auxiliarBuffer)[actualCharacter]='\0';
			strcpy(temporalBuffer,auxiliarBuffer);
			//printf("%s\n",temporalBuffer);
			actualCharacter=0;
			for(;;){
                workingCharacter=getNextCharacter(&tmpInput);
                if(workingCharacter==10){//end of line
                //getchar();
                insertOnSymbolTable(&(*analyzer)->keyWordsTable,temporalBuffer,atoi(auxiliarBuffer),0,1);
                actualCharacter=0;
                break;
                }
                (auxiliarBuffer)[actualCharacter]=workingCharacter;
                actualCharacter+=1;
			}
			//printf("%s",auxiliarBuffer);
		}else if(workingCharacter==0){
		free(auxiliarBuffer);
		free(temporalBuffer);
			//printTable((*analyzer)->keyWordsTable);
			return;
		}else{
		(auxiliarBuffer)[actualCharacter]=workingCharacter;
		actualCharacter+=1;
	}
	}

	}

}

symbol * getToken(lexicalAnalyzer ** analyzer){
	return(processCharacter(
				&((*analyzer)->input),
				&((*analyzer)->actualCharacter),
				&((*analyzer)->sTable),
				&((*analyzer)->keyWordsTable),
				&((*analyzer)->auxiliarBuffer),
				&((*analyzer)->workingCharacter)));
}
symbol * processCharacter(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
	*(actualCharacter)=0;
	*workingCharacter=getNextCharacter(input);
	// printf("I'm gonna switch: %d\n",*workingCharacter);
	(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
		switch(*workingCharacter){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
				 // ((*auxiliarBuffer)+*actualCharacter)=*workingCharacter;
				return isNonLiteralString(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
			case 32: // space
			case 10: // new line
				return processCharacter(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
				//return NULL;
			case 46: // point
				return isSucessionOfPoints(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
			case 40: // (
			case 41: // )
			case 59: // ;
			case 91: // [
			case 93: // ]
			case 44: // ,
			case 123: // {
			case 125: // }

				(*auxiliarBuffer)[*actualCharacter+1]='\0';
				 //printf("I've inserted: %s\n",*auxiliarBuffer);
				return insertOnSymbolTable(table,(*auxiliarBuffer),searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1);


			case 61: // =
				if(getNextCharacter(input)==61){
					//printf("I've inserted: ==\n");
					return insertOnSymbolTable(table,"==",searchSymbol(*keyWords,"==")->identifier,0,1);
				}else{
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1);
				}

			case 60: // <
				return processLessThan(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);

			case 42: // *
				return processAsterisk(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);

			case 43: // +
				return processPlus(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);

			case 45: // -
				return processDash(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);

			case 47:// /
				return isComment(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
			break;
			case 48: // 0
				return isBinaryNumber(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
			case 49 ... 57: // [1-9]
				return isIntegerNumber(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
			case 34: // 34
				return isStringLiteral(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);

			case 0:
				return insertOnSymbolTable(table,"$",0,0,1);
			break;
			default:
				return isNonLiteralString(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);

	}
}

symbol * isNonLiteralString(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
			case 48 ... 57: // [0-9]
				(*actualCharacter)+=1;
				(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
			break;
			default:
				(*auxiliarBuffer)[*actualCharacter+1]='\0';
				//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				//printTable(*table);
				if(searchSymbol(*keyWords,*auxiliarBuffer)!=NULL){
					return insertOnSymbolTable(table,(*auxiliarBuffer),searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1);
				}
				else
					return insertOnSymbolTable(table,(*auxiliarBuffer),IDENTIFIER,0,1);
                 //return( ( insertOnSymbolTable(table,*auxiliarBuffer,searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1)) || (insertOnSymbolTable(table,*auxiliarBuffer,IDENTIFIER,0,1)));
			break;
		}

	}

}

symbol * isSeparator(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
		for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
			case 48 ... 57: // [0-9]
				(*actualCharacter)+=1;
				(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
			break;
			case 32: // space
			case 46: // point
			case 10: // new line
			case 59: // ;
				(*auxiliarBuffer)[*actualCharacter+1]='\0';
				//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				return insertOnSymbolTable(table,(*auxiliarBuffer),searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1);
			break;
			default:

			break;
		}

	}
}

symbol * isSucessionOfPoints(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			case 46: // point
				(*actualCharacter)+=1;
				(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
			break;
			default:
				(*auxiliarBuffer)[*actualCharacter+1]='\0';
				if((*actualCharacter)<3){
				//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				return insertOnSymbolTable(table,(*auxiliarBuffer),searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1);
				}else{
					returnCharacter(input);
					//printf("Too much points!\n");
					return processCharacter(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
				}
			break;
		}
}
}

symbol * isComment(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
	int nestedComments=0;
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			case 42: // *
			(*auxiliarBuffer)[0]='\0';
			for(;;){
				*workingCharacter=getNextCharacter(input);
				if(*workingCharacter==42){
					
				}
				if(*workingCharacter==47 && (*auxiliarBuffer)[0]==42){
					return processCharacter(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
				}
				// getchar();
				(*auxiliarBuffer)[0]=*workingCharacter;
				//*workingCharacter=getNextCharacter(input);
			}
			break;
			case 43: // +
			(*auxiliarBuffer)[0]='\0';
			for(;;){
				*workingCharacter=getNextCharacter(input);
				if(*workingCharacter==47 && (*auxiliarBuffer)[0]==43 && nestedComments==0){
					return processCharacter(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
				}else if(*workingCharacter==43 && (*auxiliarBuffer)[0]==47){
					nestedComments+=1;
				}else if(*workingCharacter==47 && (*auxiliarBuffer)[0]==43 && nestedComments>0){
					nestedComments-=1;
				}
				// printf("Parella: %c%c\n",(*auxiliarBuffer)[0],*workingCharacter);
				// getchar();
				(*auxiliarBuffer)[0]=*workingCharacter;
				//*workingCharacter=getNextCharacter(input);
		}
			break;
			case 47: // /
				for(;;){
					*workingCharacter=getNextCharacter(input);
					if(*workingCharacter==10){
						return processCharacter(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
					}
				}
			break;
			default:

				(*auxiliarBuffer)[*actualCharacter+1]='\0';
				//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				return insertOnSymbolTable(table,(*auxiliarBuffer),searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1);
			break;
	}
}
}

symbol * isBinaryNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
		*workingCharacter=getNextCharacter(input);
		if(*workingCharacter=='B' || *workingCharacter=='b'){
			(*actualCharacter)+=1;
			(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
			for(;;){
				*workingCharacter=getNextCharacter(input);
				switch(*workingCharacter){
					case 48 ... 49: // [0-1]
						(*actualCharacter)+=1;
						(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
					break;
					case 65 ... 90: // [A-Z]
					case 97 ... 122: // [a-z]
					case 50 ... 57:
						return processCharacter(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
					break;
					default:
						(*auxiliarBuffer)[*actualCharacter+1]='\0';
						//printf("I've inserted: %s\n",*auxiliarBuffer);
						returnCharacter(input);
						return insertOnSymbolTable(table,(*auxiliarBuffer),INTEGER_LITERAL,0,1);
					break;
				}

			}
		}
		else{
			returnCharacter(input);
			return isIntegerNumber(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
		}

}

symbol * isIntegerNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			case 48 ... 57: // [0-9]
				(*actualCharacter)+=1;
				(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
			break;
			case 46 :// .
				(*actualCharacter)+=1;
				(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
				return isFloatNumber(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
			break;
			case 101: //e
				returnCharacter(input);
				return isFloatNumber(input,actualCharacter,table,keyWords,auxiliarBuffer,workingCharacter);
			break;
			case 95: // _
			break;
			default:
				(*auxiliarBuffer)[*actualCharacter+1]='\0';
				//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				return insertOnSymbolTable(table,(*auxiliarBuffer),INTEGER_LITERAL,0,1);
			break;
		}

	}

}

symbol * isFloatNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			case 48 ... 57: // [0-9]
				(*actualCharacter)+=1;
				(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
			break;
			case 69: //E
			case 101: //e
				(*actualCharacter)+=1;
				(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
				*workingCharacter=getNextCharacter(input);
				if(*workingCharacter==43 || *workingCharacter==45){ //+-
					(*actualCharacter)+=1;
					(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
				}
				for(;;){
					*workingCharacter=getNextCharacter(input);
					switch(*workingCharacter){
						case 48 ... 57: // [0-9]
							(*actualCharacter)+=1;
							(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
						break;
						case 95: // _
						break;
						default:
							(*auxiliarBuffer)[*actualCharacter+1]='\0';
							//printf("I've inserted: %s\n",*auxiliarBuffer);
							returnCharacter(input);
							return insertOnSymbolTable(table,(*auxiliarBuffer),FLOAT_LITERAL,0,1);

						}
				}
			default:
				(*auxiliarBuffer)[*actualCharacter+1]='\0';
				//printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				return insertOnSymbolTable(table,(*auxiliarBuffer),FLOAT_LITERAL,0,1);

		}

	}

}

symbol * isStringLiteral(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
		for(;;){
			*workingCharacter=getNextCharacter(input);
				if(*workingCharacter==34 && (*auxiliarBuffer)[*actualCharacter]!=92){ // " "\"
					(*actualCharacter)+=1;
					(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					//returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),STRING_LITERAL,0,1);
				}
				(*actualCharacter)+=1;
				(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
			}
}

symbol *processLessThan(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			// case:
			// break;
			// case:
			// break;
			default:
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					//returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1);


		}
	}
}

symbol *processPlus(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			 case 43: // +
			 case 61: // +
			 (*actualCharacter)+=1;
			 (*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
			 (*auxiliarBuffer)[*actualCharacter+1]='\0';
			//printf("I've inserted: %s\n",*auxiliarBuffer);
			//returnCharacter(input);
			return insertOnSymbolTable(table,(*auxiliarBuffer),searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1);
			 break;
			default:
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1);


		}
	}

symbol *processAsterisk(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			// case:
			// break;
			// case:
			// break;
			default:
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1);


		}
	}
}

symbol *processDash(inputSystem **input,int *actualCharacter,symbolTable ** table,symbolTable ** keyWords,char **auxiliarBuffer, char * workingCharacter){
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			// case:
			// break;
			// case:
			// break;
			default:
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					//printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),searchSymbol(*keyWords,*auxiliarBuffer)->identifier,0,1);
			break;

		}
	}
}
