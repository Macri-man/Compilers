%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "y.tab.h"

void echo(char *message);

%}

ident     	[a-zA-Z][a-zA-Z0-9]*
number    	[0-9]
whitespace 	[ \t]+

%%

"program"		{ echo("PROGRAM "); return PROGRAM; }
"array"			{ echo("ARRAY "); return ARRAY; }
"of"			{ echo("OF "); return OF; }
"integer"		{ echo("INTEGER "); return INTEGER; }
"real"			{ echo("REAL "); return REAL; }
"function"		{ echo("FUNCTION "); return FUNCTION; }
"procedure"		{ echo("PROCEDURE "); return PROCEDURE; }
"begin"			{ echo("BEGIN "); return BBEGIN; }
"end"			{ echo("END "); return END; }
"if"			{ echo("IF "); return IF; }
"else"			{ echo("ELSE "); return ELSE; }
"while"			{ echo("WHILE "); return WHILE; }
"do"			{ echo("DO "); return DO; }
"not"			{ echo("NOT "); return NOT; }
"var"			{ echo("VAR "); return VAR; }
"then"			{ echo("THEN "); return THEN; }

".."		{ echo("DOTDOT "); return DOTDOT;}
":="		{ echo("ASSIGNOP "); return ASSIGNOP; }
"="			{ fprintf(stderr, "RELOP[%s] ", yytext); return RELOP; }
"<>"		{ fprintf(stderr, "RELOP[%s] ", yytext); return RELOP; }
"<"			{ fprintf(stderr, "RELOP[%s] ", yytext); return RELOP; }
"<="		{ fprintf(stderr, "RELOP[%s] ", yytext); return RELOP; }
">"			{ fprintf(stderr, "RELOP[%s] ", yytext); return RELOP; }
"=>"		{ fprintf(stderr, "RELOP[%s] ", yytext); return RELOP; }

"or"		{ fprintf(stderr, "ADDOP[%s] ", yytext); return ADDOP; }
"+"			{ fprintf(stderr, "ADDOP[%s] ", yytext); return ADDOP; }
"-"			{ fprintf(stderr, "ADDOP[%s] ", yytext); return ADDOP; }

"div"		{ fprintf(stderr, "MULOP[%s] ", yytext); return MULOP; }
"mod"		{ fprintf(stderr, "MULOP[%s] ", yytext); return MULOP; }
"and"		{ fprintf(stderr, "MULOP[%s] ", yytext); return MULOP; }
"*"			{ fprintf(stderr, "MULOP[%s] ", yytext); return MULOP; }
"/"			{ fprintf(stderr, "MULOP[%s] ", yytext); return MULOP; }

{number}	{ fprintf(stderr, "NUMBER[%d] ", atoi(yytext)); return NUMBER; }
{ident}		{ fprintf(stderr, "ID[%s] ", yytext); return ID; }


{whitespace} { ; }
\n 			{ fprintf(stderr, "%s ", yytext); }
.			{ fprintf(stderr, "<%c> ", yytext[0]); return yytext[0]; }

%%

void echo(char *message){
	fprintf(stderr, "%s ", message);
}

int yywrap(){
	return 1;
}

void yyerror(char* message){
	fprintf(stderr,"[ERROR:%s]\n",message);
	exit(1);
}