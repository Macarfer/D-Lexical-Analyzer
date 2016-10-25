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

symbol * insertSymbol(symbol **,const char * lexicalComponent,int identifier,short line);
void inorder(symbol *firstSymbolOfLevel);


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

symbol * insertOnSymbolTable(symbolTable ** table,const char * lexicalComponent,int identifier, short line, short level){

	/*
	*
	*	If the table is empty, the first node is created
	*/
	if((*table)->first==NULL){
		(*table)->first=malloc(sizeof(levelNode));
		(*table)->first->level = 1;
		(*table)->first->nextNode = NULL;
		(*table)->first->firstSymbolOfLevel=NULL;
		//table->first->firstSymbolOfLevel=(symbol *)malloc(sizeof(symbol));
		return insertSymbol(&(*table)->first->firstSymbolOfLevel,lexicalComponent, identifier ,line);
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
			return insertSymbol(&workingNode->firstSymbolOfLevel,lexicalComponent, identifier ,line);
		/*
		*	If the node doesn't exist, we must create a new one
		*	this new node is linked from the last created one
		*/
		}else{
			printf("Close...\n");
			workingNode=workingNode->nextNode;
		}
	}
	// printf("I've inserted shit: %s\n",workingNode->firstSymbolOfLevel->lexicalComponent);
	// return 0;
}
	//return table;
}


symbol * searchSymbol(symbolTable * table,char * lexicalComponent){
	int index=1;
	auxiliarNode=table->first;
	do{
		index=1;
		auxiliarSymbol=auxiliarNode->firstSymbolOfLevel;
		while(index){
			//printf("auxiliar: %s\n",auxiliarSymbol->lexicalComponent);
			switch(strcmp(auxiliarSymbol->lexicalComponent,lexicalComponent)){
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
					//printf("Found %s!\n",auxiliarSymbol->lexicalComponent);
					return auxiliarSymbol;
			}
		}
		if(auxiliarNode->nextNode==NULL)
			return NULL;
		else
			auxiliarNode=auxiliarNode->nextNode;
	}while(auxiliarNode->nextNode!=NULL);

}

symbol * insertSymbol(symbol ** firstSymbolOfLevel,const char * lexicalComponent, int identifier,short line){
	if(*firstSymbolOfLevel==NULL){
		//printf("Entered!\n");
		*firstSymbolOfLevel= malloc(sizeof(symbol));
		(*firstSymbolOfLevel)->lexicalComponent = malloc(strlen(lexicalComponent));
		strcpy((*firstSymbolOfLevel)->lexicalComponent,lexicalComponent);
		(*firstSymbolOfLevel)->line = line;
		(*firstSymbolOfLevel)->left = NULL;
		(*firstSymbolOfLevel)->right = NULL;
		(*firstSymbolOfLevel)->identifier=identifier;
		// printf("First symbol of level directon: %p\n",*firstSymbolOfLevel);
	// 	// printf("Good job first attemp!\n");
		return *firstSymbolOfLevel;
	}else{
		workingSymbol=*firstSymbolOfLevel;
		// printf("working symbol: %p\n",workingSymbol);
		// printf("First symbol: %p\n",firstSymbolOfLevel);
	//	do{
		while(1){
			switch(strcmp(workingSymbol->lexicalComponent,lexicalComponent)){
				case MIN_INT ... -1:
				if(workingSymbol->right==NULL){
				//printf("I'm gonna go right\n");
					workingSymbol->right=malloc(sizeof(symbol));
					workingSymbol->right->line = line;
					workingSymbol->right->lexicalComponent = malloc(strlen(lexicalComponent));
					strcpy(workingSymbol->right->lexicalComponent,lexicalComponent);
					workingSymbol->right->identifier=identifier;
					workingSymbol->right->left=NULL;
					workingSymbol->right->right=NULL;
				// printf("I've inserted %s right to %s\n",workingSymbol->right->lexicalComponent,workingSymbol->lexicalComponent);
					return workingSymbol->right;
				}else{
					workingSymbol=workingSymbol->right;
				}
				break;
				case 1 ... MAX_INT :
				if(workingSymbol->left==NULL){
					workingSymbol->left=malloc(sizeof(symbol));
					workingSymbol->left->line = line;
					workingSymbol->left->lexicalComponent = malloc(strlen(lexicalComponent));
					strcpy(workingSymbol->left->lexicalComponent,lexicalComponent);
					workingSymbol->left->left=NULL;
					workingSymbol->left->right=NULL;
					workingSymbol->left->identifier=identifier;
					// printf("I've inserted %s left to %s\n",workingSymbol->left->lexicalComponent,workingSymbol->lexicalComponent);
					return workingSymbol->left;
					}else{
						workingSymbol=workingSymbol->left;
				}
				break;
				default:
					//getchar();
					//printf("Same ->lexicalComponent beach!\n");
					// printf("I've inserted: %s\n",workingSymbol->lexicalComponent);
					return workingSymbol;
			}
		}
		//}while(workingSymbol->right==NULL && workingSymbol->left==NULL);

	}
}

void printTable(symbolTable *table){
	workingNode = table->first;
	while(workingNode!=NULL){
		inorder(workingNode->firstSymbolOfLevel);
		workingNode=workingNode->nextNode;
	}

}

void inorder(symbol *firstSymbolOfLevel){

	if(firstSymbolOfLevel== NULL)
		return;
	inorder(firstSymbolOfLevel->left);
	printf("<%d> %s\n",firstSymbolOfLevel->identifier,firstSymbolOfLevel->lexicalComponent);
	inorder(firstSymbolOfLevel->right);
}

