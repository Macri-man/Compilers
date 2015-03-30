%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <assert.h>
	#include "node.h"
	#include "scope.h"
	#include "tree.h"
	#include "y.tab.h"

	extern void yyerror(char* message);
	extern int yylex(void);
	extern int yyparse(void);

	extern scope_t *top_scope;
	extern node_t *temp;
%}

%union{
	/* scanner */
	int ival;
	float rval;
	char *sval;
	int opval;
	char cval;

	/* semantic + code gen */
	tree_t *tval;
}

%token NUMBER 
%token <ival> INUM 
%token <rval> RNUM
%token <sval> ID
%token NOT

%token ASSIGNOP
%token <opval> RELOP
%token LT LE GT GE EQ NEQ
%token <opval> ADDOP
%token OR PLUS MINUS
%token <opval> MULOP
%token AND STAR SLASH DIV MOD

%token PROGRAM
%token VAR
%token ARRAY OF DOTDOT
%token INTEGER REAL CHAR STRING BOOLEAN
%token FUNCTION PROCEDURE
%token BBEGIN END
%token IF THEN ELSE
%token WHILE DO

%token EMTPY CONDITIONAL TYPE
%token LIST ARRAY_ACCESS STATEMENT
%token FUNCTION_CALL PROCEDURE_CALL
%token WHILE_DO DECL SUBDECL SUBPROGDECL
%token LOCAL PARAMETER

%type <tval> program
%type <tval> expression
%type <tval> simple_expression
%type <tval> term
%type <tval> factor
%type <tval> type
%type <tval> subprogram_declaration
%type <tval> expression_list
%type <tval> identifier_list
%type <tval> declarations
%type <tval> subprogram_declarations
%type <tval> subprogram_declaration

%type <cval> sign


%%

program:
	{ top_scope = scope_push(top_scope,"PROGRAM"); }
	PROGRAM ID '(' identifier_list ')' ';'
	declarations
	subprogram_declarations
	compound_statement
	'.'
	{
		$$ = make_program(PROGRAM,make_id(scope_insert(top_scope,$2),$3,$7,$8,$9);
		top_scope = scope_pop(top_scope);
	}
	;

identifier_list
	: ID
		{
			$$ = make_id(temp=scope_insert(top_scope,$1));
			//temp->type=ID;
		}
	| identifier_list ',' ID
		{ 
			$$ = make_tree(LIST,$1,make_id(scope_insert(top_scope,$3)));
			//temp->type=ID; 
		}
	;

declarations
	: declarations VAR identifier_list ':' type ';'
		{
			//set_names($3,$5,LOCAL);
			$$ = make_decl(VAR,$1,$3,$5,LOCAL); 
		}
	| /* empty */
		{ $$ = NULL; }//make_tree(EMTPY,NULL,NULL); }
	;

type 
	: standard_type
		{ $$ = $1; }
	| ARRAY '[' INUM DOTDOT INUM ']' OF standard_type
		{ 
			$$ = make_array(ARRAY,make_inum(INUM),make_inum(INUM),$8); 
		}
	;

standard_type
	: INTEGER 	{ $$ = make_tree(INTEGER,NULL,NULL); }
	| REAL		{ $$ = make_tree(REAL,NULL,NULL); }
	| CHAR    	{ $$ = make_tree(CHAR,NULL,NULL); }
	| STRING	{ $$ = make_tree(STRING,NULL,NULL); }
	| BOOLEAN	{ $$ = make_tree(BOOLEAN,NULL,NULL); }
	;

subprogram_declarations
	: subprogram_declarations subprogram_declaration ';'
		{ $$ = make_tree(SUBDECL,$1,$2); }
	| /* empty */
		{ $$ = NULL; }//make_tree(EMTPY,NULL,NULL); }
	;

subprogram_declaration
	: subprogram_head declarations compound_statement
		{	
			top_scope = scope_pop(top_scope); 
			$$ = make_subdecl(SUBPROGDECL,$1,$2,$3);
		}
	;

subprogram_head
	: FUNCTION ID 
		{	top_scope = scope_push(top_scope,"FUNCTION"); }
			arguments ':' standard_type ';'
		{	$$ = make_function(FUNCTION,make_id(scope_insert(top_scope,ID)),$3,$5);}
	| PROCEDURE ID 
		{	top_scope = scope_push(top_scope,"PROCEDURE"); }
		arguments ';'
		{ $$ = make_procedure(PROCEDURE,make_id(scope_insert(top_scope,ID)),$3); }
	;

arguments
	: '(' parameter_list ')'
		{ $$ = $2; }
	| /* empty */
		{ $$ = NULL; }//make_tree(EMTPY,NULL,NULL); }
	;

parameter_list
	: identifier_list ':' type
		{ 
			//set_names($1,$3,PARAMETER);
			$$ = make_parlist(LIST,NULL,$1,$2,PARAMETER); 
		}
	| parameter_list ';' identifier_list ':' type
		{ 	
			//set_names($3,$5,PARAMETER);
			$$ = make_parlist(LIST,$1,$3,$5,PARAMETER); 
		}
	;

compound_statement
	: BBEGIN optional_statements END
		{ $$ = $2; }
	;

optional_statements
	: statement_list
		{ $$ = $1; }
	| /* empty */	
		{ $$ = make_tree(EMTPY,NULL,NULL); }
	;

statement_list
	: statement
		{ $$ = $1; }
	| statement_list ';' statement
		{ $$ = make_tree(LIST,$1,$3); }
	;

statement
	: conditions
		{ $$ = $1; }
	| ifelse
		{ $$ = $1; }
	;

conditions
	: variable ASSIGNOP expression
		{ 
			if(type($1)!=type($3)) fprintf(stderr,"Line: %d: Type Mismatch: \n",line_number);
			$$ = make_op(ASSIGNOP,$2,$1,$3); 
		}
	| procedure_statement
		{ $$ = $1; }
	| compound_statement
		{ $$ = $1; }
	| IF expression THEN statement ELSE statement
		{ 
			if(type($2)!=BOOLEAN) fprintf(stderr,"Line: %d: Boolean Error: \n",line_number);  
			$$ = make_cond(CONDITIONAL,$2,$4,$6); 
		}
	| WHILE expression DO statement
		{ 
			if(type($2)!=BOOLEAN) { fprintf(stderr,"Line: %d: Boolean Error: \n",line_number);  }
			$$ = make_tree(WHILE_DO,$1,$2); 
		}
	| FOR ID ASSIGNOP expression TO expression DO conditions
		{	
			temp=scope_search(top_scope,$2);
			if(type(make_id(temp))!=type($4)) fprintf(stderr,"Line: %d: Boolean Error: \n",line_number);  
			if(type(make_id(temp))!=type($6)) fprintf(stderr,"Line: %d: Boolean Error: \n",line_number);  
			$$ = make_tree(FOR,make_id(temp),make_tree(DO,make_tree(TO,$4,$6),$8));
		}
	;

ifelse
	: IF expression THEN statement
		{
			if(type($2)!=BOOLEAN) fprintf(stderr,"Line: %d: TBoolean Error: \n",line_number); print_tree($2,0); 
			$$ = make_tree(IF,$2,$4);
		}
	| IF expression THEN conditions ELSE ifelse
		{
			if(type($2)!=BOOLEAN) fprintf(stderr,"Line: %d: Boolean Error: \n",line_number); print_tree($2,0); 
			$$ = make_tree(IF, $2, make_tree(THEN,$2,$6));
		}
	;


variable
	: ID
		{ $$ = make_id(scope_search(top_scope,$1)); }
	| ID '[' expression ']'
		{ 
			$$ = make_tree(ARRAY_ACCESS,make_id(scope_search(top_scope,$1)),$3);
			check_array($$,ARRAY_ACCESS); 
		}
	;

procedure_statement
	: ID
	 	{ 
	 		$$ = make_tree(PROCEDURE,make_id(scope_search(top_scope,$1)),NULL); 
	 		check_procedure($$,PROCEDURE);
	 	}
	| ID '(' expression_list ')'
		{ 
			$$ = make_tree(PROCEDURE,make_id(scope_search(top_scope,$1)),$3); 
			check_procedure($$,PROCEDURE);
		}
	;

expression_list
	: expression
		{ $$ = $1; }
	| expression_list ',' expression
		{ $$ = make_tree(LIST,$1,$3); }
	;

expression
	: simple_expression
		{ $$ = $1; }
	| simple_expression RELOP simple_expression
		{ $$=make_op(RELOP,$2,$1,$3); }
	;

simple_expression
	: term
		{ $$ = $1; }
	| ADDOP term
		{ $$ = make_tree(ADDOP,$1,$2); }
	| simple_expression ADDOP term
		{ $$ = make_op(ADDOP,$2,$1,$3); }
	;

term
	: factor
		{ $$ = $1; }
	| term MULOP factor
		{ $$ = make_op(MULOP,$2,$1,$3); }
	;

factor
	: ID { 	
			if((temp=scope_search_all(top_scope,$1)) == NULL){
				fprintf(stderr,"Name %s used but not defined\n",$1);
					exit(1);
				}
					$$ = make_id(tmp); 
				}
	| ID '(' expression_list ')' 
		{
			if((temp=scope_search_all(top_scope,$1)) == NULL){
						fprintf(stderr,"Name %s used but not defined\n",$1);
						exit(1);
					}
			$$ = make_tree(FUNCTION_CALL,make_id(temp),$3);
			check_function($$,FUNCTION); 
		}
	| ID '[' expression_list ']' 
		{ 
			if((temp=scope_search_all(top_scope,$1)) == NULL){
						fprintf(stderr,"Name %s used but not defined\n",$1);
						exit(1);
					}
			$$ = make_tree(ARRAY_ACCESS,make_id(temp),$3); 
			check_array($$,ARRAY_ACCESS);
		}
	| INUM
		{ $$ = make_inum($1); }
	| RNUM
		{ $$ = make_rnum($1); }	
	| '(' expression ')'
		{$$ = $2; }
	| NOT factor
		{ $$ = make_tree(NOT,$2,NULL); }
	;



%%


scope_t *top_scope;
node_t *temp;
main(){
	top_scope=NULL;
	tmp=NULL;
	yyparse();
}


