#include "lexicalAnalyzer.h"
#include <string.h>

symbol * processCharacter(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol * isIdentifier(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer,char * workingCharacter);
symbol * isSeparator(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol * isSucessionOfPoints(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);
symbol * isComment(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter);


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
				return isIdentifier(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
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
				// printf("I've inserted: %s\n",*auxiliarBuffer);
				return insertOnSymbolTable(table,(*auxiliarBuffer),0,1);
				
			break;

			case 47:// /
				return isComment(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;
			default:
				 isIdentifier(input,actualCharacter,table,auxiliarBuffer,workingCharacter);
			break;


	}
}
symbol * isIdentifier(inputSystem **input,int *actualCharacter,symbolTable ** table,char **auxiliarBuffer, char * workingCharacter){
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