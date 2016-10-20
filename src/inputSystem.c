#include "inputSystem.h"

/*Initializes all necessary structures for reading from the file*/
void inputInitialize(inputSystem ** system,const char * pathToFile){
	// /*Necessary variables for managing the proccess*/
	/*First we obtain the FS size on the actual computer*/
	struct stat fi;
	stat("/",&fi);
	//printf("Tamano de bloque: %d\n", fi.st_blksize);
	(*system) = (inputSystem*) malloc(sizeof(inputSystem));
	(*system)->doubleGuardBuffer = (char * ) malloc (2*N+2);
	(*system)->initialPointer = 0;
	(*system)->frontPointer = 0;
	// Then we create a memory buffer, this buffer is going to be 
	// the communication resource between the imput system and the lexical analyzer
	// char * buffer = (char * ) malloc(2*fi.st_blksize);
	// /*After that we open the file once per block read, this intends to optimize the access to disk
	// minimizing the time spent in this task*/
	(*system)->fileToOpen = fopen(pathToFile,"r");
	fread((*system)->doubleGuardBuffer,sizeof(char),2*N,(*system)->fileToOpen);
	printf("contido: %s\n",(*system)->doubleGuardBuffer);
	// printf("contido apuntado por initialPointer: %c\n",*((*system)->doubleGuardBuffer+(*system)->initialPointer));
	// printf("contido apuntado por frontPointer: %c\n",*((*system)->doubleGuardBuffer+(*system)->frontPointer));
	// // return buffer;
	// //printf("Caracter 1st: %c\n",fgetc(arquivo));
};

/*Sends actual character to the lexical analyzer*/
char getNextCharacter(inputSystem ** system){
	(*system)->frontPointer+=1;
	return *((*system)->doubleGuardBuffer+(*system)->frontPointer-1);
};

void returnCharacter(inputSystem ** system){
	(*system)->frontPointer-=1;
};
/*Finalizes all structures used on this program and frees memory and structures*/
short finalize();