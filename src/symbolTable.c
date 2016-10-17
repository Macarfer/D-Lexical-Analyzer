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

short insertSymbolOnNode(levelNode *,const char * identifier,short line);

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
symbolTable * insertOnSymbolTable(symbolTable * table,const char * identifier, short line, short level){

	/*
	*
	*	If the table is empty, the first node is created
	*/
	if(table->first==NULL){
		table->first=(levelNode *) malloc(sizeof(levelNode));
		table->first->level = 1;
		table->first->nextNode = NULL;
		//table->first->firstSymbolOfLevel=(symbol *)malloc(sizeof(symbol));
		insertSymbolOnNode(table->first,identifier,line);
		return table;
		//return 0;

	/*
	*
	*	If the table isn't empty we must check the 
	* 	linked list of table nodes
	*/
	}else{
	workingNode = table->first;
	printf("Auxiliar node: %p\n",workingNode);
	printf("Table first: %p\n",table->first);
	while(workingNode!=NULL){
		// printf("Axuiliar node level: %d\n",workingNode->level);
		// printf("Compared node level: %d\n",level);
		/*
		*	If the node we are loking for already exist, we must insert a new 
		* 	symbol in the already existing level node
		*/
		if(workingNode->level==level){
			printf("I'm gonna insert an item\n");
			insertSymbolOnNode(workingNode,identifier,line);

			workingNode=workingNode->nextNode;
			//return 0;
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
	return table;
}


short insertSymbolOnNode(levelNode * node,const char * identifier,short line){

	if(node->firstSymbolOfLevel==NULL){
		printf("Entered!\n");
		node->firstSymbolOfLevel= (symbol *) malloc(sizeof(symbol));
		node->firstSymbolOfLevel->identifier = (char *) malloc(sizeof(identifier));
		strcpy(node->firstSymbolOfLevel->identifier,identifier);
		node->firstSymbolOfLevel->line = line;
		node->firstSymbolOfLevel->left = NULL;
		node->firstSymbolOfLevel->right = NULL;
		printf("First symbol of level directon: %p\n",&node->firstSymbolOfLevel);
		printf("Good job first attemp!\n");
		return 0;
	}else{
		printf("Pls I'm half working!\n");
		workingSymbol=node->firstSymbolOfLevel;
		do{
			switch(strcmp(workingSymbol->identifier,identifier)){
				case MIN_INT ... -1:
				printf("I'm gonna go right\n");
				break;
				case 1 ... MAX_INT :
				printf("I'm gonna go left\n");
				break;
				default:
				printf("Same identifier beach!\n");
				break;
			}
		}while(workingSymbol->left!=NULL && workingSymbol->right!=NULL);

	}
	return 0;
}