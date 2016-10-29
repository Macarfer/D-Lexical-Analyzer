#include "errorManager.h"
#include <stdio.h>


/*Meant for displaying and handling errors of the lexicalAnalyzer*/
void showLexicalError(int code,int line,char * string){
	/*Just switches the error code and prints a matching message on screen*/
	switch(code){
		case COMMENT_NOT_CLOSED_ERROR :
			printf("A comment has not been closed!\n %s\nLine: %d\n",string,line);
		break;

		case STRING_TOO_LONG:
			printf("Word size exceeded!\n %s\nLine: %d\n",string,line);
		break;
		default:
		break;

	}
}


/*Meant for displaying and handling errors of the inputSystem*/
void showInputError(int code,char const * string){
	/*Switches the error code and displays a matching error message.
	If a file that doesn't exist is openned the system will return a segmentation fault
	the exit(1) prevents that error and stops the execution*/
	switch (code){
	case FILE_NOT_FOUND:
		printf("File %s not found!\n",string);
		exit(1);
	break;

}

}