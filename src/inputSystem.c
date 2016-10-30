#include "inputSystem.h"

/*Struct input system with all the parameters necessary*/
struct inputSystem{
	FILE * fileToOpen;
	char * doubleBuffer;
	char * initialPointer;
	char * frontPointer;
	int readNumber;
}inputSystem;

/*Initializes all necessary structures for reading from the file*/
void inputInitialize(char const * path_to_file){

	// struct stat fi;
	// stat("/",&fi);

	inputSystem.doubleBuffer = (char *) malloc(2*N+2);
	inputSystem.initialPointer = inputSystem.doubleBuffer;
	inputSystem.frontPointer = (inputSystem.doubleBuffer-1);
	inputSystem.readNumber=1;

	/*If the file specified not exist it generates an error*/
	if((inputSystem.fileToOpen = fopen(path_to_file,"r"))==NULL)
		showInputError(FILE_NOT_FOUND,path_to_file);
	
	/*It reads N block of data, tipically, for an optimal performance N must be a block of the filesystem*/
	fread(inputSystem.doubleBuffer,N,1,inputSystem.fileToOpen);
	inputSystem.doubleBuffer[N] = '\0';
	}

/*Sends actual character to the lexical analyzer*/
char getNextCharacter(){
	/*The front pointer indicates the returned character*/
	inputSystem.frontPointer=(inputSystem.frontPointer+1);
	
	/*If the actual character is the EOF of any of the buffers*/
	if(*inputSystem.frontPointer=='\0'){
		/*If the actual character is the end of the second buffer*/
		if(&*(inputSystem.frontPointer)==&inputSystem.doubleBuffer[2*N+1]){
			/*The buffer is reseted*/
			memset(inputSystem.doubleBuffer,'\0',N);
			/*The pointer where the file is going to be read is moved N characters*/
			fseek(inputSystem.fileToOpen,N,N*inputSystem.readNumber);
			inputSystem.readNumber+=1;

			/*N characters are read from the file*/
			fread((inputSystem.doubleBuffer),N,1,inputSystem.fileToOpen);

			/*The front pointer is reseted to the initial position of the character buffer*/
			inputSystem.frontPointer=(inputSystem.doubleBuffer);

		}else
		/*If the actual character is the end of the firstbuffer*/ 
		if(&*(inputSystem.frontPointer)==&inputSystem.doubleBuffer[N]){
			/*The buffer is reseted*/
			memset((inputSystem.doubleBuffer+N+1),'\0',N);
			/*The pointer where the file is going to be read is moved N characters*/
			fseek(inputSystem.fileToOpen,N,N*inputSystem.readNumber);
			inputSystem.readNumber+=1;
			/*N characters are read from the file*/
			fread((inputSystem.doubleBuffer+N+1),N,1,inputSystem.fileToOpen);
			/*The front pointer is reseted to the second part of the character buffer*/
			inputSystem.frontPointer=(inputSystem.frontPointer+1);

		}
	}
	/*The character pointed by the frontPointer is returned*/
	return *inputSystem.frontPointer;
}
/*Allows the lexicalAnalyzer to return a character to the input system*/
void returnCharacter(){
		/*If the actual character is the begining of the first buffer, it's previous
		place is the last one of the second buffer*/ 
		if(&*(inputSystem.frontPointer)==&inputSystem.doubleBuffer[0]){
			inputSystem.frontPointer=(inputSystem.doubleBuffer+2*N);

		}else{
			/*The position of the front pointer is moved one step backwards*/
			inputSystem.frontPointer=(inputSystem.frontPointer-1);
		}

}
/*Finalizes all structures used on this program and frees memory and structures*/
short finalizeInputSystem(){
	fclose(inputSystem.fileToOpen);
	free(inputSystem.doubleBuffer);

	/*Both pointers are freed when freeing inputSystem.doubleBuffer*/

	//free(inputSystem.initialPointer);
	//free(inputSystem.frontPointer);

	return 0;
}
