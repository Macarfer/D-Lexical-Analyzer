
/*Text array of the document to read*/
char * fileToOpen = "../regression.d";
/*Initializes all necessary structures for reading from the file*/
short initialize();
/*Indicate the relative path to the file that is gonna be openned*/
short open(char * fileRoute);
/*Sends actual character to the lexical analyzer*/
char getNextCharacter();
/*Finalizes all structures used on this program and frees memory and structures*/
short finalize();