/*
*	This symbol Table is gonna be implemented as a forest of trees
*	it'll be more efficient to use a hash table but,the additional memory usage
*	and development complexity of a hash table isn't worth it for this approach
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"

#define MIN_INT -2147483648
#define MAX_INT 2147483647

symbol * insertSymbol(symbol **,const char * identifier,short line);

levelNode * workingNode, * auxiliarNode;
symbol * workingSymbol, * auxiliarSymbol;

symbolTable * initializeTable(symbolTable * table){
	if(table==NULL){
		table = (symbolTable *) malloc (sizeof(symbolTable));
		workingNode=(levelNode *) malloc(sizeof(levelNode));
		return table;
	}else{
		/*This must be managed by the erro management module*/
		printf("The table is already initializated!\n");
		return table;
	}
}

symbol * insertOnSymbolTable(symbolTable ** table,const char * identifier, short line, short level){

	/*
	*
	*	If the table is empty, the first node is created
	*/
	if((*table)->first==NULL){
		(*table)->first=(levelNode *) malloc(sizeof(levelNode));
		(*table)->first->level = 1;
		(*table)->first->nextNode = NULL;
		//table->first->firstSymbolOfLevel=(symbol *)malloc(sizeof(symbol));
		return insertSymbol(&(*table)->first->firstSymbolOfLevel,identifier,line);
		//printf("First symbol of level directon out: %p\n",table->first->firstSymbolOfLevel);
		
		//return 0;

	/*
	*
	*	If the table isn't empty we must check the 
	* 	linked list of table nodes
	*/
	}else{
	workingNode = (*table)->first;
	// printf("Auxiliar node: %p\n",workingNode);
	// printf("Table first: %p\n",table->first);
	while(workingNode!=NULL){
		// printf("Axuiliar node level: %d\n",workingNode->level);
		// printf("Compared node level: %d\n",level);
		/*
		*	If the node we are loking for already exist, we must insert a new 
		* 	symbol in the already existing level node
		*/
		if(workingNode->level==level){
			//printf("I'm gonna insert an item\n");
			
			//&workingNode=(*workingNode)->nextNode;
			//workingNode=workingNode->nextNode;
			return insertSymbol(&workingNode->firstSymbolOfLevel,identifier,line);
		/*
		*	If the node doesn't exist, we must create a new one
		*	this new node is linked from the last created one
		*/
		}else{
			printf("Close...\n");
			workingNode=workingNode->nextNode;
		}
	}
	// printf("I've inserted shit: %s\n",workingNode->firstSymbolOfLevel->identifier);
	// return 0;
}
	//return table;
}


symbol * searchSymbol(symbolTable * table,const char * identifier){
	int index=1;
	auxiliarNode=table->first;
	do{
		index=1;
		auxiliarSymbol=auxiliarNode->firstSymbolOfLevel;
		while(index){
			printf("auxiliar: %s\n",auxiliarSymbol->identifier);
			switch(strcmp(auxiliarSymbol->identifier,identifier)){
				case MIN_INT ... -1:
				if(auxiliarSymbol->right!=NULL){
					auxiliarSymbol=auxiliarSymbol->right;
				}else{
					index=0;
				}
				break;
				case 1 ... MAX_INT :
				if(auxiliarSymbol->left!=NULL){
					auxiliarSymbol=auxiliarSymbol->left;
				}else{
					index=0;
				}
				break;
				default:
					printf("Found %s!\n",auxiliarSymbol->identifier);
					return auxiliarSymbol;
				break;
			}
		}
		if(auxiliarNode->nextNode==NULL)
			return NULL;
		else
			auxiliarNode=auxiliarNode->nextNode;
	}while(auxiliarNode->nextNode!=NULL);

}

symbol * insertSymbol(symbol ** firstSymbolOfLevel,const char * identifier,short line){
	if(*firstSymbolOfLevel==NULL){
		//printf("Entered!\n");
		*firstSymbolOfLevel= (symbol *) malloc(sizeof(symbol));
		(*firstSymbolOfLevel)->identifier = (char *) malloc(sizeof(identifier));
		strcpy((*firstSymbolOfLevel)->identifier,identifier);
		(*firstSymbolOfLevel)->line = line;
		(*firstSymbolOfLevel)->left = NULL;
		(*firstSymbolOfLevel)->right = NULL;
		// printf("First symbol of level directon: %p\n",*firstSymbolOfLevel);
	// 	// printf("Good job first attemp!\n");
		return *firstSymbolOfLevel;
	}else{
		workingSymbol=*firstSymbolOfLevel;
		// printf("working symbol: %p\n",workingSymbol);
		// printf("First symbol: %p\n",firstSymbolOfLevel);
	//	do{
		while(1){
			switch(strcmp(workingSymbol->identifier,identifier)){
				case MIN_INT ... -1:
				if(workingSymbol->right==NULL){
				//printf("I'm gonna go right\n");
				//printf("I've inserted %s right to %s\n",identifier,workingSymbol->identifier);
					workingSymbol->right=(symbol *) malloc(sizeof(symbol));
					workingSymbol->right->line = line;
					workingSymbol->right->identifier = (char *) malloc(sizeof(identifier));
					strcpy(workingSymbol->right->identifier,identifier);
					workingSymbol->right->left=NULL;
					workingSymbol->right->right=NULL;
					return workingSymbol;
				}else{
					workingSymbol=workingSymbol->right;
				}
				break;
				case 1 ... MAX_INT :
				if(workingSymbol->left==NULL){
				//printf("I've inserted %s left to %s\n",identifier,workingSymbol->identifier);
					workingSymbol->left=(symbol *) malloc(sizeof(symbol));
					workingSymbol->left->line = line;
					workingSymbol->left->identifier = (char *) malloc(sizeof(identifier));
					strcpy(workingSymbol->left->identifier,identifier);
					workingSymbol->left->left=NULL;
					workingSymbol->left->right=NULL;
					return workingSymbol;
					}else{
						workingSymbol=workingSymbol->left;
				}
				break;
				default:
					//getchar();
					//printf("Same identifier beach!\n");
					return workingSymbol;
				break;
			}
		}
		//}while(workingSymbol->right==NULL && workingSymbol->left==NULL);

	}
	return 0;
}