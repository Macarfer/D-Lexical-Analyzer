#define N 10
/*Text array of the document to read*/
//const char * fileToOpen = "../regression.d";
/*Initializes all necessary structures for reading from the file*/
char * initialize();
/*Indicate the relative path to the file that is gonna be openned*/
short open(char * fileRoute);
/*Sends actual character to the lexical analyzer*/
char getNextCharacter();
/*Finalizes all structures used on this program and frees memory and structures*/
short finalize();