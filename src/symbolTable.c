/*
*	This tray Table is gonna be implemented as a forest of trees
*	it'll be more efficient to use a hash table but,the additional memory usage
*	and development complexity of a hash table isn't worth it for this approach
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"

#define MIN_INT -2147483648
#define MAX_INT 2147483647

struct tray{
	struct symbol lexicalComponent;
	struct tray * left;
	struct tray * right;
} tray;


struct levelNode{
	short level;
	struct levelNode * nextNode;
	struct tray * firstSymbolOfLevel;
}levelNode;

struct symbolTable{
	struct levelNode * first;
}symbolTable;

symbol * insertSymbol(struct tray **,char * lexeme,int identifier,short line);
void inorder(struct tray *firstSymbolOfLevel);


struct levelNode * workingNode, * auxiliarNode;
struct tray * workingTray, * auxiliarTray;


void  initializeSymbolTable(){
	if(workingNode==NULL)
		workingNode= malloc(sizeof(levelNode));

}

symbol * insertOnSymbolTable(char * lexeme, int identifier, short line, short level){

	/*
	*
	*	If the table is empty, the first node is created
	*/
	if(symbolTable.first==NULL){
		symbolTable.first=malloc(sizeof(levelNode));
		symbolTable.first->level = 1;
		symbolTable.first->nextNode = NULL;
		symbolTable.first->firstSymbolOfLevel=NULL;
		//table->first->firstSymbolOfLevel=(tray *)malloc(sizeof(tray));
		return insertSymbol(&(symbolTable.first->firstSymbolOfLevel),lexeme, identifier ,line);
		//printf("First tray of level directon out: %p\n",table->first->firstSymbolOfLevel);

	/*
	*
	*	If the table isn't empty we must check the
	* 	linked list of table nodes
	*/
	}

	workingNode = symbolTable.first;
//	printf("Auxiliar node: %p\n",workingNode);
//	printf("Table first: %p\n",table->first);
	while(workingNode!=NULL){
//		printf("Axuiliar node level: %d\n",workingNode->level);
// 		// printf("Compared node level: %d\n",level);
// 		/*
// 		*	If the node we are loking for already exist, we must insert a new
// 		* 	tray in the already existing level node
// 		*/
		if(workingNode->level==level){
		//	printf("I'm gonna insert an item\n");

			//&workingNode=(*workingNode)->nextNode;
			//workingNode=workingNode->nextNode;
			return insertSymbol(&workingNode->firstSymbolOfLevel,lexeme, identifier ,line);
// 		/*
// 		*	If the node doesn't exist, we must create a new one
// 		*	this new node is linked from the last created one
// 		*/
		}

 			//printf("Close...\n");
			workingNode=workingNode->nextNode;
	}
// 	// printf("I've inserted shit: %s\n",workingNode->firstSymbolOfLevel->lexicalComponent);
// 	//return table;
	return NULL;
 }


symbol * searchSymbol(char * lexeme){
	int index=1;
	auxiliarNode=symbolTable.first;
	do{
		index=1;
		auxiliarTray=auxiliarNode->firstSymbolOfLevel;
		for(;index>0;){
			//printf("auxiliar: %s\n",auxiliarTray->lexicalComponent);
			switch(strcmp(auxiliarTray->lexicalComponent.lexeme,lexeme)){
				case MIN_INT ... -1:
					if(auxiliarTray->right!=NULL){
						auxiliarTray=auxiliarTray->right;
					}else{
						index=0;
					}
				break;
				case 1 ... MAX_INT :
					if(auxiliarTray->left!=NULL){
						auxiliarTray=auxiliarTray->left;
					}else{
						index=0;
					}
				break;
				default:
					//printf("Found %s!\n",auxiliarTray->lexicalComponent);
					return &auxiliarTray->lexicalComponent;
			}
		}
		if(auxiliarNode->nextNode==NULL)
			return NULL;
		else
			auxiliarNode=auxiliarNode->nextNode;
	}while(auxiliarNode->nextNode!=NULL);
	return NULL;
}

symbol * insertSymbol(struct tray ** firstSymbolOfLevel,char * lexeme,int identifier,short line){
	if(*firstSymbolOfLevel==NULL){
		//printf("Entered!\n");
		*firstSymbolOfLevel= malloc(sizeof(tray));
		//(*firstSymbolOfLevel)->lexicalComponent = malloc(sizeof(symbol));
		(*firstSymbolOfLevel)->lexicalComponent.lexeme = malloc(strlen(lexeme));
		strcpy((*firstSymbolOfLevel)->lexicalComponent.lexeme,lexeme);
		(*firstSymbolOfLevel)->lexicalComponent.line = line;
		(*firstSymbolOfLevel)->left = NULL;
		(*firstSymbolOfLevel)->right = NULL;
		(*firstSymbolOfLevel)->lexicalComponent.identifier=identifier;
	//	 printf("First tray of level directon: %p\n",*firstSymbolOfLevel);
	// 	// printf("Good job first attemp!\n");
		return &(*firstSymbolOfLevel)->lexicalComponent;
	}
	else{
		workingTray=*firstSymbolOfLevel;
		 // printf("working tray: %p\n",workingTray);
		 // printf("First tray: %p\n",firstSymbolOfLevel);
	//	do{
		for(;;){
			switch(strcmp(workingTray->lexicalComponent.lexeme,lexeme)){
				case MIN_INT ... -1:
				if(workingTray->right==NULL){
				//printf("I'm gonna go right\n");
					workingTray->right=malloc(sizeof(tray));
					workingTray->right->lexicalComponent.line = line;
					workingTray->right->lexicalComponent.lexeme = malloc(strlen(lexeme));
					strcpy(workingTray->right->lexicalComponent.lexeme,lexeme);
					workingTray->right->lexicalComponent.identifier=identifier;
					workingTray->right->left=NULL;
					workingTray->right->right=NULL;
				//printf("I've inserted %s right to %s\n",workingTray->right->lexicalComponent.lexeme,workingTray->lexicalComponent.lexeme);
					return &workingTray->right->lexicalComponent;
				}else{
					workingTray=workingTray->right;
				}
				break;
				case 1 ... MAX_INT :
				if(workingTray->left==NULL){
					workingTray->left=malloc(sizeof(tray));
					workingTray->left->lexicalComponent.line = line;
					workingTray->left->lexicalComponent.lexeme = malloc(strlen(lexeme));
					strcpy(workingTray->left->lexicalComponent.lexeme,lexeme);
					workingTray->left->lexicalComponent.identifier=identifier;
					workingTray->left->left=NULL;
					workingTray->left->right=NULL;
					//printf("I've inserted %s left to %s\n",workingTray->left->lexicalComponent.lexeme,workingTray->lexicalComponent.lexeme);
					return &workingTray->left->lexicalComponent;
					}else{
						workingTray=workingTray->left;
				}
				break;
				default:
					//printf("Same ->lexicalComponent beach!\n");
					//printf("I've inserted: %s\n",workingTray->lexicalComponent.lexeme);
					return &workingTray->lexicalComponent;
			}
		}
		//}while(workingTray->right==NULL && workingTray->left==NULL);

	}
}

void printSymbolTable(){
	workingNode = symbolTable.first;
	while(workingNode!=NULL){
		inorder(workingNode->firstSymbolOfLevel);
		workingNode=workingNode->nextNode;
	}

}

void inorder(struct tray *firstSymbolOfLevel){

	if(firstSymbolOfLevel== NULL)
		return;
	inorder(firstSymbolOfLevel->left);
	printf("<%d> %s\n",firstSymbolOfLevel->lexicalComponent.identifier,firstSymbolOfLevel->lexicalComponent.lexeme);
	inorder(firstSymbolOfLevel->right);
 }

