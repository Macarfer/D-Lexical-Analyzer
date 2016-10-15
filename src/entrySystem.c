#include "entrySystem.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

/*Initializes all necessary structures for reading from the file*/
char* initialize(){
	/*Necessary variables for managing the proccess*/
	/*First we obtain the FS size on the actual computer*/
	struct stat fi;
	stat("/",&fi);
	//printf("Tamano de bloque: %d\n", fi.st_blksize);
	/*Then we create a memory buffer, this buffer is going to be 
	the communication resource between the imput system and the lexical analyzer*/
	char * buffer = (char * ) malloc(2*fi.st_blksize);
	/*After that we open the file once per block read, this intends to optimize the access to disk
	minimizing the time spent in this task*/
	FILE * arquivo;
	arquivo = fopen("../regression.d","r");
	fread(buffer,sizeof(char),fi.st_blksize,arquivo);
	return buffer;
	//printf("Caracter 1st: %c\n",fgetc(arquivo));
};
/*Indicate the relative path to the file that is gonna be openned*/
short open(char * fileRoute);
/*Sends actual character to the lexical analyzer*/
char getNextCharacter(){

};
/*Finalizes all structures used on this program and frees memory and structures*/
short finalize();