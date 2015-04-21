%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <assert.h>
	#include "node.h"
	#include "scope.h"
	#include "list.h"
	#include "tree.h"
	#include "semantic.h"
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
	list_t *lval;

	int type;
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
%token WHILE DO FOR TO

%token EMTPY CONDITIONAL TYPE
%token LIST ARRAY_ACCESS STATEMENT
%token FUNCTION_CALL PROCEDURE_CALL
%token WHILE_DO DECL SUBDECL SUBPROGDECL
%token LOCAL PARAMETER IDLIST EXPR EXPRLIST PARALIST ARGLIST DECLIST STATLIST PROCSTAT COMPSTAT

%type <tval> program
%type <tval> expression
%type <tval> expression_list
%type <tval> simple_expression
%type <tval> term
%type <tval> factor
%type <tval> type
%type <tval> procedure_statement
%type <tval> variable
%type <tval> ifelse
%type <tval> conditions
%type <tval> subprogram_head
%type <tval> subprogram_declarations
%type <tval> subprogram_declaration

%type <tval> statement
%type <tval> optional_statements
%type <tval> compound_statement
%type <tval> statement_list

%type <lval> arguments
%type <lval> declarations
%type <lval> parameter_list
%type <lval> identifier_list

%type <type> standard_type

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
		$$ = make_tree(PROGRAM,make_id(temp=scope_insert(top_scope,$3)),make_tree(LIST,make_treeFromList(IDLIST,$5),make_tree(LIST,make_treeFromList(DECLIST,$8),make_tree(SUBPROGDECL,$9,$10))));
		//print_tree(make_treeFromList(DECLIST,$8),0);
		top_scope = scope_pop(top_scope);
		print_tree($$,0);
	}
	;

identifier_list
	: ID
		{
			//insert ID into scope
			$$ = make_list_node(temp=scope_insert(top_scope,$1),$1,IDLIST);
			//$$ = make_id(scope_insert(top_scope,$1));
			//temp->type=ID;
		}
	| identifier_list ',' ID
		{
			//insert ID into scope
			$$ = list_append_node($1,temp=scope_insert(top_scope,$3));
			//$$ = make_tree(IDLIST,$1,scope_insert(top_scope,$1));
			//temp->type=ID;
		}
	;

declarations
	: declarations VAR identifier_list ':' type ';'
		{
			//set the types of the id list and set the mark to local
			//set_names($3,$5,LOCAL);
			//$$ = make_decl(DECLIST,make_idlist(IDLIST,$3),$5,LOCAL);
			assign_type($3,$5);
			assign_mark($3,LOCAL);
			//make list of identifier list and append id list to the declarations list
			$$ = list_append(DECLIST,$1,$3);
		}
	| /* empty */
		{ $$ = NULL; }//make_tree(EMTPY,NULL,NULL); }
	;

type 
	: standard_type
		{ $$ = make_tree($1,NULL,NULL); }
	| ARRAY '[' INUM DOTDOT INUM ']' OF standard_type
		{ 
			//make sure the ID knows the range of the array
			$$ = make_tree(ARRAY,make_tree($8,NULL,NULL),make_tree($8,make_inum(INUM),make_inum(INUM))); 
		}
	;

standard_type
	: INTEGER 	{ $$ = INTEGER; }
	| REAL		{ $$ = REAL; }
	| CHAR    	{ $$ = CHAR; }
	| STRING	{ $$ = STRING; }
	| BOOLEAN	{ $$ = BOOLEAN; }
	;

subprogram_declarations
	: subprogram_declarations subprogram_declaration ';'
		{ $$ = make_tree(SUBDECL,$1,$2); }
	| /* empty */
		{ $$ = NULL; }//make_tree(EMTPY,NULL,NULL); }
	;

subprogram_declaration
	: subprogram_head declarations subprogram_declarations compound_statement
		{	
			top_scope = scope_pop(top_scope); 
			$$ = make_tree(SUBPROGDECL,$1,make_tree(SUBPROGDECL,$2,$3));
		}
	;

subprogram_head
	: FUNCTION ID 
		{	
			//insert ID into scope
			assert((top_scope = scope_push(top_scope,"FUNCTION"))!=NULL);
			temp=scope_insert(top_scope,$2); 
			temp->mark=FUNCTION;

		}
			arguments ':' standard_type ';'
		{
			temp->type=$6;
			temp->list=$4;
			$$ = make_tree(FUNCTION,make_id(temp),make_treeFromList(ARGLIST,$4));
		}
	| PROCEDURE ID 
		{	
			//insert ID into scope
			assert((top_scope = scope_push(top_scope,"PROCEDURE"))!=NULL);
			temp=scope_insert(top_scope,$2); 
			temp->type=PROCEDURE;
			temp->mark=PROCEDURE;

		}
		arguments ';'
		{ 
			temp->list=$4;
			$$ = make_tree(PROCEDURE,make_id(temp),make_treeFromList(ARGLIST,$4)); 
		}
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
			//set the types of the id list and mark then as paramters
			//set_names($1,$3,PARAMETER);
			assign_type($1,$3);
			assign_mark($1,PARAMETER);
			//make list of parameters
			$$ = make_list(PARALIST,$1); 
		}
	| parameter_list ';' identifier_list ':' type
		{ 	
			//set the types of the id list and mark then as paramters
			//set_names($3,$5,PARAMETER);
			assign_type($3,$5);
			assign_mark($3,PARAMETER);
			//make list of identifier list and append id list to the parameter list
			$$ = list_append(PARALIST,$1,$3); 
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
		{ $$ = NULL; }//make_tree(EMTPY,NULL,NULL); }
	;

statement_list
	: statement
		//make list of statements
		{ $$ = $1; }//make_list_tree($1,"STATLIST",STATLIST); }
	| statement_list ';' statement
		//make list of statement then append the list of statements
		{ $$ = make_tree(STATLIST,$1,$3); }
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
			//check type of varibale == type of expression
			if(type($1)!=type($3)){ fprintf(stderr,"Type Mismatch: \n"); }
			$$ = make_tree(ASSIGNOP,$1,$3); 
		}
	| procedure_statement
		{ $$ = $1; }
	| compound_statement
		{ $$ = $1; }//make_treeFromList(COMPSTAT,$1); }
	| IF expression THEN statement ELSE statement
		{ 
			//check type of expression for boolean
			if(type($2)!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); } 
			$$ = make_tree(IF,$2,make_tree(THEN,$4,$6)); 
		}
	| WHILE expression DO statement
		{ 
			//check if expression is type boolean
			if(type($2)!=BOOLEAN) { fprintf(stderr,"Boolean Error: \n");  }
			$$ = make_tree(WHILE_DO,$2,$4); 
		}
	| FOR ID ASSIGNOP expression TO expression DO conditions
		{	
			//check if type of temp is type of expression before TO and type temp is type of expression after TO
			temp=scope_search(top_scope,$2);
			if(type(make_id(temp))!=type($4)){ fprintf(stderr,"Boolean Error: \n"); } 
			if(type(make_id(temp))!=type($6)){ fprintf(stderr,"Boolean Error: \n"); }
			$$ = make_tree(FOR,make_id(temp),make_tree(DO,make_tree(TO,$4,$6),$8));
		}
	;

ifelse
	: IF expression THEN statement
		{
			//check type of expresion is boolean
			if(type($2)!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); print_tree($2,0); }
			$$ = make_tree(IF,$2,$4);
		}
	| IF expression THEN conditions ELSE ifelse
		{
			//check type of expression is boolean
			if(type($2)!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); print_tree($2,0); } 
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
	 		//search ID and check if valid procedure call
	 		$$ = make_tree(PROCEDURE,make_id(scope_search(top_scope,$1)),NULL); 
	 		check_procedure($$,PROCEDURE);
	 	}
	| ID '(' expression_list ')'
		{
			//search ID and check if valid procedure call
			$$ = make_tree(PROCEDURE,make_id(scope_search(top_scope,$1)),$3); 
			check_procedure($$,PROCEDURE);
		}
	;

expression_list
	: expression
		{ $$ = $1; }
	| expression_list ',' expression
		{ $$ = make_tree(EXPRLIST,$1,$3); }
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
		{ $$ = make_op(ADDOP,$1,$2,NULL); }
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
			$$ = make_id(temp); 
		}
	| ID '(' expression_list ')' 
		{
			//check if valid function call
			if((temp=scope_search_all(top_scope,$1)) == NULL){
				fprintf(stderr,"Name %s used but not defined\n",$1);
				exit(1);
			}
			$$ = make_tree(FUNCTION_CALL,make_id(temp),$3);
			check_function($$,FUNCTION); 
		}
	| ID '[' expression_list ']' 
		{ 
			//check if valid array access
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

sign : '+' { $$ = '+'; }
     | '-' { $$ = '-'; }
     ;

%%


scope_t *top_scope;
node_t *temp;
int main(){
	top_scope=NULL;
	temp=NULL;
	yyparse();
}


