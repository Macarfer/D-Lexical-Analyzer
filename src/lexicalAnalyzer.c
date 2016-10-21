#include "lexicalAnalyzer.h"
#include <string.h>

symbol * processCharacter(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol * isNonLiteralString(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer,char * workingCharacter);
symbol * isSeparator(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol * isSucessionOfPoints(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol * isComment(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol * isIntegerNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol * isStringLiteral(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol * isFloatNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol * isBinaryNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol *processLessThan(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol *processDash(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol *processAsterisk(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol *processPlus(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);

void initializeLexicalAnalyzer(lexicalAnalyzer ** analyzer){
	if(*analyzer==NULL){
		*analyzer=(lexicalAnalyzer *)malloc(sizeof(lexicalAnalyzer));
		inputInitialize(&((*analyzer)->input),PATH_TO_FILE);
		(*analyzer)->sTable=initializeTable((*analyzer)->sTable);
		(*analyzer)->actualLine=0;
		(*analyzer)->actualCharacter=0;
		(*analyzer)->auxiliarBuffer=(char *)malloc(200);
		
	}

}

symbol * getToken(lexicalAnalyzer ** analyzer){
	return(processCharacter(
				&((*analyzer)->input),
				&((*analyzer)->actualCharacter),
				&((*analyzer)->sTable),
				&((*analyzer)->auxiliarBuffer),
				&((*analyzer)->workingCharacter)));
}
symbol * processCharacter(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
	
	*(actualCharacter)=0;
	*workingCharacter=getNextCharacter(input);
	//printf("I'm gonna switch: %c\n",*workingCharacter);
	(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
		switch(*workingCharacter){
			case 65 ... 90: // [A-Z]
			case 97 ... 122: // [a-z]
			case 95: // _
				 // ((*auxiliarBuffer)+*actualCharacter)=*workingCharacter;
				return isNonLiteralString(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;
			case 32: // space
			case 10: // new line
				return processCharacter(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;
			case 46: // point
				return isSucessionOfPoints(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
				break;
			case 40: // (
			case 41: // )
			case 59: // ;
			case 91: // [
			case 93: // ]
			case 44: // ,
			case 123: // {
			case 125: // }

				(*auxiliarBuffer)[*actualCharacter+1]='\0';
				 printf("I've inserted: %s\n",*auxiliarBuffer);
				return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);
				
			break;

			case 61: // =
				if(getNextCharacter(input)==61){
					printf("I've inserted: ==\n");
					return insertOnSymbolTable(table,"==",0,1);
				}else{
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
				}

			break;

			case 60: // <
				return processLessThan(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;

			case 42: // *
				return processAsterisk(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;

			case 43: // +
				return processPlus(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;

			case 45: // -
				return processDash(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;

			case 47:// /
				return isComment(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;
			case 48: // 0
				return isBinaryNumber(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;
			case 49 ... 57: // [1-9]
				return isIntegerNumber(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;
			case 34: // 34
				return isStringLiteral(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;

			case 3:
				printf("End of file!\n ");
			break;
			default:
				printf("error!\n");
				return NULL;
			break;


	}
}
symbol * isNonLiteralString(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
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
				printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
			break;
		}

	}

}

symbol * isSeparator(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
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
				printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
			break;
			default:
				
			break;
		}

	}
}

symbol * isSucessionOfPoints(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
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
				printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);
				}else{
					returnCharacter(input);
					printf("Too much points!\n");
					return NULL;
				}
			break;
		}
}
}

symbol * isComment(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
	int nestedComments=0;
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			case 42: // *
			(*auxiliarBuffer)[0]='\0';
			for(;;){
				*workingCharacter=getNextCharacter(input);
				if(*workingCharacter==47 && (*auxiliarBuffer)[0]==42){
					return NULL;
				}
				// printf("Parella: %c%c\n",(*auxiliarBuffer)[0],*workingCharacter);
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
					return NULL;
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
						return NULL;
					}
				}
			break;
			default:

				(*auxiliarBuffer)[*actualCharacter+1]='\0';
				printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);
			break;
	}	
}
}

symbol * isBinaryNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
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
						return NULL;
					break;
					default:
						(*auxiliarBuffer)[*actualCharacter+1]='\0';
						printf("I've inserted: %s\n",*auxiliarBuffer);
						returnCharacter(input);
						return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
					break;
				}

			}
		}
		else{
			returnCharacter(input);
			return isIntegerNumber(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
		}

}

symbol * isIntegerNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
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
				return isFloatNumber(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;
			case 101: //e
				returnCharacter(input);
				return isFloatNumber(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;
			case 95: // _
			break;
			default:
				(*auxiliarBuffer)[*actualCharacter+1]='\0';
				printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
			break;
		}

	}

}

symbol * isFloatNumber(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
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
							printf("I've inserted: %s\n",*auxiliarBuffer);
							returnCharacter(input);
							return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
						break;
						}
				}
			break;
			default:
				(*auxiliarBuffer)[*actualCharacter+1]='\0';
				printf("I've inserted: %s\n",*auxiliarBuffer);
				returnCharacter(input);
				return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
			break;
		}

	}

}

symbol * isStringLiteral(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
		for(;;){
			*workingCharacter=getNextCharacter(input);
				if(*workingCharacter==34 && (*auxiliarBuffer)[*actualCharacter]!=92){ // " "\"
					(*actualCharacter)+=1;
					(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					printf("I've inserted: %s\n",*auxiliarBuffer);
					//returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
				}
				(*actualCharacter)+=1;
				(*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
			}
}

symbol *processLessThan(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			// case:
			// break;
			// case:
			// break;
			default:
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					printf("I've inserted: %s\n",*auxiliarBuffer);
					//returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
			break;

		}
	}
}

symbol *processPlus(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			 case 43: // +
			 case 61: // +
			 (*actualCharacter)+=1;
			 (*auxiliarBuffer)[*actualCharacter]=*workingCharacter;
			 (*auxiliarBuffer)[*actualCharacter+1]='\0';
			printf("I've inserted: %s\n",*auxiliarBuffer);
			//returnCharacter(input);
			return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);
			 break;
			default:
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
			break;

		}
	}

symbol *processAsterisk(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			// case:
			// break;
			// case:
			// break;
			default:
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
			break;

		}
	}
}

symbol *processDash(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
	for(;;){
		*workingCharacter=getNextCharacter(input);
		switch(*workingCharacter){
			// case:
			// break;
			// case:
			// break;
			default:
					(*auxiliarBuffer)[*actualCharacter+1]='\0';
					printf("I've inserted: %s\n",*auxiliarBuffer);
					returnCharacter(input);
					return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);	
			break;

		}
	}
}