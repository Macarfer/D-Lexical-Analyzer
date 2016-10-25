#include "inputSystem.h"

/*Initializes all necessary structures for reading from the file*/
void inputInitialize(inputSystem ** system,const char * pathToFile){
	// /*Necessary variables for managing the proccess*/
	/*First we obtain the FS size on the actual computer*/
	struct stat fi;
	stat("/",&fi);
	//printf("Tamano de bloque: %d\n", fi.st_blksize);
	(*system) = (inputSystem*) malloc(sizeof(inputSystem));
	(*system)->doubleBuffer = (char * ) malloc (2*N+2);
	(*system)->initialPointer = (*system)->doubleBuffer;
	(*system)->frontPointer = ((*system)->doubleBuffer-1);
	(*system)->readNumber=1;
	// Then we create a memory buffer, this buffer is going to be
	// the communication resource between the imput system and the lexical analyzer
	// char * buffer = (char * ) malloc(2*fi.st_blksize);
	// /*After that we open the file once per block read, this intends to optimize the access to disk
	// minimizing the time spent in this task*/
	(*system)->fileToOpen = fopen(pathToFile,"r");
	fread((*system)->doubleBuffer,N,1,(*system)->fileToOpen);
	//printf("contido: %s\n",(*system)->doubleBuffer);
	(*system)->doubleBuffer[N] = '\0';
	//fread(((*system)->doubleBuffer+N+1),N,1,(*system)->fileToOpen);
//(*system)->doubleBuffer[2*N+1]= '\0';
	//printf("contido: %s\n",((*system)->doubleBuffer+N+1));
	//fread(,N,1,(*system)->fileToOpen);
	//printf("contido: %s\n",(*system)->doubleGuardBuffer[N+1]);
	//fclose((*system)->fileToOpen);
	//fclose((*system)->fileToOpen);
	// printf("contido apuntado por initialPointer: %c\n",*((*system)->doubleGuardBuffer+(*system)->initialPointer));
	// printf("contido apuntado por frontPointer: %c\n",*((*system)->doubleGuardBuffer+(*system)->frontPointer));
	// // return buffer;
	// //printf("Caracter 1st: %c\n",fgetc(arquivo));
}

/*Sends actual character to the lexical analyzer*/
char getNextCharacter(inputSystem ** system){
	//(*system)->frontPointer+=1;
	(*system)->frontPointer=((*system)->frontPointer+1);
	//printf("%d\n",(*system)->doubleBuffer[2*N+1]);
	//getchar();
     //   printf("asdf: %p -> %d\n",&*((*system)->frontPointer),*((*system)->frontPointer));
       // printf("asdf1: %p -> %d\n",&(*system)->doubleBuffer[N],(*system)->doubleBuffer[N]);
        //printf("asdf2: %p -> %d\n",&(*system)->doubleBuffer[2*N+1],(*system)->doubleBuffer[2*N+1]);
	if(*(*system)->frontPointer=='\0'){
      if(&*((*system)->frontPointer)==&(*system)->doubleBuffer[2*N+1]){
      	memset((*system)->doubleBuffer,'\0',N);

        fseek((*system)->fileToOpen,N,N*(*system)->readNumber);
        (*system)->readNumber+=1;


        fread(((*system)->doubleBuffer),N,1,(*system)->fileToOpen);


       //printf("contido: %s\n",(*system)->doubleBuffer);

       (*system)->doubleBuffer[N] = '\0';

        (*system)->frontPointer=((*system)->doubleBuffer);

      }else if(&*((*system)->frontPointer)==&(*system)->doubleBuffer[N]){
        memset((*system)->doubleBuffer,'\0',N);

        fseek((*system)->fileToOpen,N,N*(*system)->readNumber);
        (*system)->readNumber+=1;


        fread(((*system)->doubleBuffer+N+1),N,1,(*system)->fileToOpen);

        //printf("contido 02: %s\n",((*system)->doubleBuffer+N+1));
        (*system)->doubleBuffer[2*N+1] = '\0';
       // getchar();
        (*system)->frontPointer=((*system)->frontPointer+1);
       // printf("lasdkfja;sldfjk: %c\n",*(*system)->frontPointer );

      }else{
        return '\0';
      }
	}
	return *(*system)->frontPointer;
}

void returnCharacter(inputSystem ** system){
	(*system)->frontPointer=((*system)->frontPointer-1);
}
/*Finalizes all structures used on this program and frees memory and structures*/
short finalize(){
	return 0;
}

char * getLexeme(){
	return "asdf";
}
