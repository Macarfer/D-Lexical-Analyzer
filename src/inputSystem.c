#include "inputSystem.h"

struct inputSystem{
	FILE * fileToOpen;
	char * doubleBuffer;
	char * initialPointer;
	char * frontPointer;
	int readNumber;
}inputSystem;

/*Initializes all necessary structures for reading from the file*/
void inputInitialize(){
	// /*Necessary variables for managing the proccess*/
	/*First we obtain the FS size on the actual computer*/
	struct stat fi;
	stat("/",&fi);
	//printf("Tamano de bloque: %d\n", fi.st_blksize);
	//(*system) = (inputSystem*) malloc(sizeof(inputSystem));
	//inputSystem.doubleBuffer = (char * ) malloc (2*N+2);
	inputSystem.doubleBuffer = (char *) malloc(2*N+2);
	inputSystem.initialPointer = inputSystem.doubleBuffer;
	inputSystem.frontPointer = (inputSystem.doubleBuffer-1);
	inputSystem.readNumber=1;
	// Then we create a memory buffer, this buffer is going to be
	// the communication resource between the imput system and the lexical analyzer
	// char * buffer = (char * ) malloc(2*fi.st_blksize);
	// /*After that we open the file once per block read, this intends to optimize the access to disk
	// minimizing the time spent in this task*/
	inputSystem.fileToOpen = fopen("../regression.d","r");
	fread(inputSystem.doubleBuffer,N,1,inputSystem.fileToOpen);
	printf("contido: %s\n",inputSystem.doubleBuffer);
	inputSystem.doubleBuffer[N] = '\0';
	//fread((inputSystem.doubleBuffer+N+1),N,1,inputSystem.fileToOpen);
//inputSystem.doubleBuffer[2*N+1]= '\0';
	//printf("contido: %s\n",(inputSystem.doubleBuffer+N+1));
	//fread(,N,1,inputSystem.fileToOpen);
	//printf("contido: %s\n",inputSystem.doubleGuardBuffer[N+1]);
	//fclose(inputSystem.fileToOpen);
	//fclose(inputSystem.fileToOpen);
	// printf("contido apuntado por initialPointer: %c\n",*(inputSystem.doubleGuardBuffer+inputSystem.initialPointer));
	// printf("contido apuntado por frontPointer: %c\n",*(inputSystem.doubleGuardBuffer+inputSystem.frontPointer));
	// // return buffer;
	// //printf("Caracter 1st: %c\n",fgetc(arquivo));
}

/*Sends actual character to the lexical analyzer*/
char getNextCharacter(){
	//inputSystem.frontPointer+=1;
	inputSystem.frontPointer=(inputSystem.frontPointer+1);
	//printf("%d\n",inputSystem.doubleBuffer[2*N+1]);
	//getchar();
     //   printf("asdf: %p -> %d\n",&*(inputSystem.frontPointer),*(inputSystem.frontPointer));
       // printf("asdf1: %p -> %d\n",&inputSystem.doubleBuffer[N],inputSystem.doubleBuffer[N]);
        //printf("asdf2: %p -> %d\n",&inputSystem.doubleBuffer[2*N+1],inputSystem.doubleBuffer[2*N+1]);
	if(*inputSystem.frontPointer=='\0'){
      if(&*(inputSystem.frontPointer)==&inputSystem.doubleBuffer[2*N+1]){
      	memset(inputSystem.doubleBuffer,'\0',N);

        fseek(inputSystem.fileToOpen,N,N*inputSystem.readNumber);
        inputSystem.readNumber+=1;


        fread((inputSystem.doubleBuffer),N,1,inputSystem.fileToOpen);


       printf("contido: %s\n",inputSystem.doubleBuffer);

       inputSystem.doubleBuffer[N] = '\0';

        inputSystem.frontPointer=(inputSystem.doubleBuffer);

      }else if(&*(inputSystem.frontPointer)==&inputSystem.doubleBuffer[N]){
        memset(inputSystem.doubleBuffer,'\0',N);

        fseek(inputSystem.fileToOpen,N,N*inputSystem.readNumber);
        inputSystem.readNumber+=1;


        fread((inputSystem.doubleBuffer+N+1),N,1,inputSystem.fileToOpen);

        //printf("contido 02: %s\n",(inputSystem.doubleBuffer+N+1));
        inputSystem.doubleBuffer[2*N+1] = '\0';
       // getchar();
        inputSystem.frontPointer=(inputSystem.frontPointer+1);
       // printf("lasdkfja;sldfjk: %c\n",*inputSystem.frontPointer );

      }else{
        return '\0';
      }
	}
	return *inputSystem.frontPointer;
}

void returnCharacter(){
	inputSystem.frontPointer=(inputSystem.frontPointer-1);
}
/*Finalizes all structures used on this program and frees memory and structures*/
short finalize(){
	return 0;
}

char * getLexeme(){
	return "asdf";
}
