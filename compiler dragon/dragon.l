%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"
#include "scope.h"
#include "tree.h"
#include "y.tab.h"


void echo(char *message);

int line_number = 1;

%}

ident     	[a-zA-Z][a-zA-Z0-9]*
num      	[0-9]+
whitespace 	[ \t]+
comment     \(\*.*\*\)


%%

"program"		{ echo("PROGRAM "); return PROGRAM; }
"array"			{ echo("ARRAY "); return ARRAY; }
"of"			{ echo("OF "); return OF; }
"integer"		{ echo("INTEGER "); return INTEGER; }
"real"			{ echo("REAL "); return REAL; }
"string"   		{ echo("STRING "); return STRING; }
"char"      	{ echo("CHAR "); return CHAR; }
"boolean"      	{ echo("BOOLEAN "); return BOOLEAN; }
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
"for"			{ echo("FOR "); return FOR; }
"to"			{ echo("TO "); return TO; }
"read"			{ echo("READ "); yylval.sval = strdup(yytext); return READ; }
"write"			{ echo("WRITE "); yylval.sval = strdup(yytext); return WRITE; }

".."	{ echo("DOTDOT "); return DOTDOT; }
":="	{ echo("ASSIGNOP "); return ASSIGNOP; }
"="		{ fprintf(stderr, "RELOP[%s] ", yytext); yylval.opval=EQ; return RELOP; 	}
"<>"	{ fprintf(stderr, "RELOP[%s] ", yytext); yylval.opval=NEQ; return RELOP; 	}
"<"		{ fprintf(stderr, "RELOP[%s] ", yytext); yylval.opval=LT; return RELOP; 	}
"<="	{ fprintf(stderr, "RELOP[%s] ", yytext); yylval.opval=LE; return RELOP; 	}
">"		{ fprintf(stderr, "RELOP[%s] ", yytext); yylval.opval=GT; return RELOP; 	}
">="	{ fprintf(stderr, "RELOP[%s] ", yytext); yylval.opval=GE; return RELOP; 	}

"-"		{ fprintf(stderr, "ADDOP[%s] ", yytext); yylval.opval=MINUS; return ADDOP; 	}
"+"		{ fprintf(stderr, "ADDOP[%s] ", yytext); yylval.opval=PLUS; return ADDOP; 	}
"or"	{ fprintf(stderr, "ADDOP[%s] ", yytext); yylval.opval=OR; return ADDOP; 	}

"*"		{ fprintf(stderr, "MULOP[%s] ", yytext); yylval.opval=STAR; return MULOP; 	}
"/"		{ fprintf(stderr, "MULOP[%s] ", yytext); yylval.opval=SLASH; return MULOP; 	}
"div"	{ fprintf(stderr, "MULOP[%s] ", yytext); yylval.opval=DIV; return MULOP; 	}
"mod"	{ fprintf(stderr, "MULOP[%s] ", yytext); yylval.opval=MOD; return MULOP; 	}
"and"	{ fprintf(stderr, "MULOP[%s] ", yytext); yylval.opval=AND; return MULOP; 	}

{num}				{ fprintf(stderr, "INUM[%d] ", yylval.ival = atoi(yytext)); return INUM; }
{num}"."{num}		{ fprintf(stderr, "RNUM[%f] ", yylval.rval = atof(yytext)); return RNUM; }
{ident}				{ fprintf(stderr, "ID[%s] ", yylval.sval = strdup(yytext)); return ID; 	}

{comment}    { ; }
{whitespace} { ; }
\n 			{ fprintf(stderr, "%s ", yytext); line_number++; }
.			{ fprintf(stderr, "<%c> ", yytext[0]); return yytext[0]; }

%%

void echo(char *message){
	fprintf(stderr, "%s ", message);
}

int yywrap(){
	return 1;
}

int yyerror(const char *s) {
    printf("parse error at Line Number:%d %s\n",line_number,s);
    return 0;
}