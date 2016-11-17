%{				
#include <stdio.h>				
#include "lexical.h"	
#include "errorManager.h"		
#define MAX_STRING_SIZE 200				

/*Auxiliar elements for counting lines and nested comments*/			
int lines=1;						
short nestedComments=0;						
%}				
/*Identifiers of functions for different types of comments detection*/
%x comment				
%x comment2				
%x comment3				
%x comment4				
				
%%		
"/"	 return	SLASH	; /*Just checks if the exact string is matched and, if it is returns it's identifier*/		
"/="	 return	SLASH_EQUAL	;
"."	 return	POINT	;
".."	 return	DOUBLE_POINT	;
"..."	 return	TRIPLE_POINT	;
"&"	 return	AMPERSAND	;
"&="	 return	AMPERSAND_EQUAL	;
"&&"	 return	DOUBLE_AMPERSAND	;
"|"	 return	VERTICAL_BAR	;
"|="	 return	VERTICAL_BAR_EQUAL	;
"||"	 return	DOUBLE_VERTICAL_BAR	;
"-"	 return	HORIZONTAL_BAR	;
"-="	 return	HORIZONTAL_BAR_EQUAL	;
"--"	 return	DOUBLE_HORIZONTAL_BAR	;
"+"	 return	PLUS	;
"+="	 return	PLUS_EQUAL	;
"++"	 return	DOUBLE_PLUS	;
"<"	 return	LESS_THAN	;
"<="	 return	LESS_THAN_EQUAL	;
"<<"	 return	DOUBLE_LESS_THAN	;
"<<="	 return	DOUBLE_LESS_THAN_EQUAL	;
"<>"	 return	LESS_THAN_MORE_THAN	;
"<>="	 return	LESS_THAN_MORE_THAN_EQUAL	;
">"	 return	MORE_THAN	;
">="	 return	MORE_THAN_EQUAL	;
">>="	 return	DOUBLE_MORE_THAN_EQUAL	;
">>>="	 return	TRIPLE_MORE_THAN_EQUAL	;
">>"	 return	DOUBLE_MORE_THAN	;
">>>"	 return	TRIPLE_MORE_THAN	;
"!"	 return	EXCLAMATION	;
"!="	 return	EXCLAMATION_EQUAL	;
"!<>"	 return	EXCLAMATION_LESS_THAN_MORE_THAN	;
"!<>="	 return	EXCLAMATION_LESS_THAN_MORE_THAN_EQUAL	;
"!<"	 return	EXCLAMATION_LESS_THAN	;
"!<="	 return	EXCLAMATION_LESS_THAN_EQUAL	;
"!>"	 return	EXCLAMATION_MORE_THAN	;
"!>="	 return	EXCLAMATION_MORE_THAN_EQUAL	;
"("	 return	PARENTHESES_OPEN	;
")"	 return	PARENTHESES_CLOSE	;
"["	 return	SQUARE_BRACKET_OPEN	;
"]"	 return	SQUARE_BRACKET_CLOSE	;
"{"	 return	CURLY_BRACKET_OPEN	;
"}"	 return	CURLY_BRACKET_CLOSE	;
"?"	 return	QUESTION_MARK	;
","	 return	COMMA	;
";"	 return	SEMICOLON	;
":"	 return	COLON	;
"$"	 return	DOLLAR	;
"="	 return	EQUAL	;
"=="return	DOUBLE_EQUAL	;	
"*"	 return	ASTERISK	;
"*="	 return	ASTERISK_EQUAL	;
"%"	 return	PERCENTAGE	;
"%="	 return	PERCENTAGE_EQUAL	;
"^"	 return	CARET	;
"^="	 return	CARET_EQUAL	;
"^^"	 return	DOUBLE_CARET	;
"^^="	 return	DOUBLE_CARET_EQUAL	;
"~"	 return	TILDE	;
"~="	 return	TILDE_EQUAL	;
"@"	 return	AT	;
"=>"  return	EQUAL_MORE_THAN	;
"#"   return	HASHTAG	;	
" " 		   		/*Checks if there's a space and ignores it*/
"abstract"	| /*Chescks if any of the keywords is in the texts, if it is it returns the identifier keyword*/
"alias"	|
"align"	|
"asm"	|
"assert"	|
"auto"	|
"body"	|
"bool"	|
"break"	|
"byte"	|
"case"	|
"cast"	|
"catch"	|
"cdouble"	|
"cent"	|
"cfloat"	|
"char"	|
"class"	|
"const"	|
"continue"	|
"creal"	|
"dchar"	|
"debug"	|
"default"	|
"delegate"	|
"delete"	|
"deprecated"	|
"do"	|
"double"	|
"else"	|
"enum"	|
"export"	|
"extern"	|
"false"	|
"final"	|
"finally"	|
"float"	|
"for"	|
"foreach"	|
"foreach_reverse"	|
"function"	|
"goto"	|
"idouble"	|
"if"	|
"ifloat"	|
"immutable"	|
"import"	|
"in"	|
"inout"	|
"int"	|
"interface"	|
"invariant"	|
"ireal"	|
"is"	|
"lazy"	|
"long"	|
"macro"	|
"mixin"	|
"module"	|
"new"	|
"nothrow"	|
"package"	|
"pragma"	|
"protected"	|
"public"	|
"pure"	|
"ref"	|
"return"	|
"scope"	|
"shared"	|
"short"	|
"static"	|
"struct"	|
"super"	|
"switch"	|
"synchronized"	|
"template"	|
"this"	|
"throw"	|
"true"	|
"try"	|
"typedef"	|
"typeid"	|
"typeof"	|
"ubyte"	|
"ucent"	|
"uint"	|
"ulong"	|
"union"	|
"unittest"	|
"ushort"	|
"version"	|
"void"	|
"volatile"	|
"wchar"	|
"while"	|
"with"	|
"__FILE__"	|
"__FILE_FULL_PATH__"	|
"__MODULE__"	|
"__LINE__"	|
"__FUNCTION__"	|
"__PRETTY_FUNCTION__"	|
"__gshared"	|
"__traits"	|
"__vector"	|
"__parameters"  return KEYWORD;	
[_a-zA-Z]{1}[_[:alnum:][:alpha:]]*  return IDENTIFIER; /*Checks if a string is an identifier*/	
0[bB][01]*  return 				INTEGER_LITERAL;/*Checks if we've got a binary number*/	
[-+]?[0-9_]+ return INTEGER_LITERAL;/*Checks if we've got an integer (with or whitout symbol)*/				
[-+]?[0-9]+\.?([eE][-+]?[0-9]+)? return FLOAT_LITERAL;/*Checks if we've got a float in scientific notation (with or whitout symbol)*/		
[-+]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)? return FLOAT_LITERAL;	/*The same as the previous one but, this one can not have something before the point*/		
<<EOF>> return DOLLAR;		/*If we've reached the end of file we return the end of file character*/	

"/+" BEGIN(comment2);/*checks for nested comments*/
<comment2>[^/+\n]* /*processes everything except + */
<comment2>\n ++lines; /*If we reach the end of file we increment the line count*/
<comment2>"*"+"/"			
<comment2>"/"+"*"		
<comment2>"/"		/*This and the previous ones just processes some strange symbols like * and / */
<comment2>"/"+"+"  ++nestedComments; 				/*If we reach an init of a nested comment then we increment nestedComments variable*/
<comment2>"+"+"/" if(!nestedComments) BEGIN(INITIAL); else nestedComments--;		/*If we reached the end of a comment and there are no comments opened then we've finished if not, we just start again decreasing the value of the nestedComments variable*/

<comment2,comment3,comment,comment4><EOF> showLexicalError(COMMENT_NOT_CLOSED_ERROR,lines,yytext); /*If we reach the end of file before ending the comment we throw an error*/

"//" BEGIN(comment3);
<comment3>[^(\n)]* /* just processes everything */
<comment3>\n ++lines; BEGIN(INITIAL); /*When we reach the end of line we increment the line count and continue the proccess*/

"/**"	yymore();BEGIN(comment4);		
<comment4>[^*\n]* yymore();	/*Process everything except * and adds the processed content to yytext()*/	
<comment4>\n		lines++;yymore();	/*Increments the line count and adds the processed content to yytext()*/	
<comment4>"*"+"/"   BEGIN(INITIAL);return STRING_LITERAL;/*Returns the recognized string and it's identifier*/

"/*" BEGIN(comment);
<comment>[^*\n]* /* processes everything except * */
<comment>"*"+[^*/\n]* /* processes every * not followed by an / */
<comment>\n ++lines; /*Increments the line count*/
<comment>"*"+"/" BEGIN(INITIAL); 

"/**/"							/*Recognizes the exact string*/
\n			lines+=1;			/*Increments the lines if we reach the end of line*/
\"(\\.|[^\\"])*\" return STRING_LITERAL;				/*Recognices string literals with scaped elements*/
%%				
