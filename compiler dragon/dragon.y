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
	extern node_t *tmp;
%}

%union{
	/* scanner */
	int ival;
	float rval;
	char *sval;
	int opval;

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

%token EMTPY CONDITIONAL
%token LIST ARRAY_ACCESS
%token FUNCTION_CALL PROCEDURE_CALL
%token WHILE_DO

%type <tval> expression
%type <tval> expression_list
%type <tval> simple_expression
%type <tval> term
%type <tval> factor



%%

program:
	{ top_scope = scope_push(top_scope); }
	PROGRAM ID '(' identifier_list ')' ';'
	declarations
	subprogram_declarations
	compound_statement
	'.'
	{ 
		top_scope = scope_pop(top_scope);
		$$ = make_program(PROGRAM,make_prog(PROGRAM),make_id(ID),$3,$7,$8,$9,$10);
	}
	;

identifier_list
	: ID
		{ 
			scope_insert(top_scope,$1); 
			$$ = make_list(make_id($1));
		}
	| identifier_list ',' ID
		{ 
			scope_insert(top_scope,$3);
			$$ = $1; list_insert($$,make_id($3)); 
		}
	;

declarations
	: declarations VAR identifier_list ':' type ';'
		{ $$ = make_decl($1,make_var(VAR),$3,$5); }
	| /* empty */
		{ $$ = EMTPY; }
	;

type 
	: standard_type
		{ $$ = $1; }
	| ARRAY '[' INUM DOTDOT INUM ']' OF standard_type
		{ $$ = make_array(make_arr(ARRAY),make_inum(INUM),make_inum(INUM),$8); }
	;

standard_type
	: INTEGER
	| REAL
	| CHAR
	| STRING
	| BOOLEAN
	;

subprogram_declarations
	: subprogram_declarations subprogram_declaration ';'
		{ $$ = sub_decl($1,$2); }
	| /* empty */
		{ $$ = EMTPY; }
	;

subprogram_declaration
	: subprogram_head declarations compound_statement
		{	top_scope = scope_pop(top_scope); }
	;

subprogram_head
	: FUNCTION ID 
		{	top_scope = scope_push(top_scope); }
			arguments ':' standard_type ';'
		{	$$ make_function(make_func(FUNCTION),make_id(ID),$3,$5);}
	| PROCEDURE ID 
		{	top_scope = scope_push(top_scope); }
		arguments ';'
		{ $$ = make_procedure(make_proc(PROCEDURE),make_id(ID),$3); }
	;

arguments
	: '(' parameter_list ')'
		{ $$ = $2; }
	| /* empty */
	;

parameter_list
	: identifier_list ':' type
		{ $$ = make_idlist($1,$2); }
	| parameter_list ';' identifier_list ':' type
		{ $$ = make_parlist($1,$3,$5); }
	;

compound_statement
	: BBEGIN optional_statements END
		{ $$ = make_optstat($1,$2,$3); }
	;

optional_statements
	: statement_list
		{ $$ = $1; }
	| /* empty */	
		{ $$ = EMTPY; }
	;

statement_list
	: statement
		{ $$ = make_stm(STM_LIST,$1,$2); }
	| statement_list ';' statement
		{ $$ = make_stm(STM_LIST,$1,$2); }
	;

statement
	: variable ASSIGNOP expression
		{ $$ = make_op(ASSIGNOP,$2,$1,$3); }
	| procedure_statement
		{ $$ = $1; }
	| compound_statement
		{ $$ = $1; }
	| IF expression THEN statement ELSE statement
		{ $$ = make_cond(CONDITIONAL,$2,$4,$6); }
	| WHILE expression DO statement
		{ $$ = make_tree(WHILE_DO,$1,$2); }
	;

variable
	: ID
		{ $$ = make_id($1); }
	| ID '[' expression ']'
		{ $$ = make_tree(ARRAY_ACCESS,make_id($1),$3); }
	;

procedure_statement
	: ID
	 	{ $$ = make_id($1); }
	| ID '(' expression_list ')'
		{ $$ = make_tree(PROCEDURE_CALL,make_id($1),$3); }
	;

expression_list
	: expression
		{ $$ = $1; }
	| expression_list ',' expression
		{ $$=make_tree(LIST,$1,$3); }
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
	| sign term
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
			if((tmp=scope_search_all(top_scope,$1)) == NULL){
				fprintf(stderr,"Name %s used but not defined\n",$1);
					exit(1);
				}
					$$ = make_id(tmp); 
				}
	| ID '(' expression_list ')' 
		{ 
			if((tmp=scope_search_all(top_scope,$1)) == NULL){
						fprintf(stderr,"Name %s used but not defined\n",$1);
						exit(1);
					}
			$$ = make_tree(FUNCTION_CALL,make_id(tmp),$3); 
		}
	| ID '[' expression_list ']' 
		{ 
			if((tmp=scope_search_all(top_scope,$1)) == NULL){
						fprintf(stderr,"Name %s used but not defined\n",$1);
						exit(1);
					}
			$$ = make_tree(ARRAY_ACCESS,make_id(tmp),$3); 
		}
	| INUM
		{ $$ = make_inum($1); }
	| RNUM
		{ $$ = make_rnum($1); }	
	| '(' expression ')'
		{$$ = $2; }
	| NOT factor
		{ $$ = make_tree(NOT,NULL,NULL); }
	;

sign : '+' { $$ = '+'; }
     | '-' { $$ = '-'; }
     ;


%%


scope_t *top_scope;
node_t *tmp;
main(){
	top_scope=NULL;
	tmp=NULL;
	yyparse();
}


