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
	extern node_t *subprogram;
	extern tree_t *tree;

	int depth;
	FILE * assemble;
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

	int ptype;
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
%token FUNCTION PROCEDURE READ WRITE
%token BBEGIN END
%token IF THEN ELSE
%token WHILE DO FOR TO

%token EMTPY CONDITIONAL TYPE NAME
%token LIST ARRAY_ACCESS ARRAY_RANGE STATEMENT
%token FUNCTION_CALL PROCEDURE_CALL
%token WHILE_DO DECL SUBDECL SUBDECLS SUBPROGDECL SUBPROGDECLHEAD SUBPROGDECLBODY
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


%type <ptype> standard_type


%type <lval> arguments
%type <lval> declarations
%type <lval> parameter_list
%type <lval> identifier_list

%%

program:
	{ 
		top_scope = scope_push(top_scope,"PROGRAM");
		temp=scope_insert(top_scope,"read");
		temp->type=FUNCTION;
		temp->mark=READ;
		temp=scope_insert(top_scope,"write");
		temp->type=FUNCTION;
		temp->mark=WRITE;

	}
	PROGRAM ID '(' identifier_list ')' ';'
	declarations
	subprogram_declarations
	compound_statement
	'.'
	{
		$$ = make_tree(PROGRAM,make_id(temp=scope_insert(top_scope,$3)),make_tree(LIST,make_treeFromList(IDLIST,$5),make_tree(LIST,make_treeFromList(DECLIST,$8),make_tree(SUBPROGDECL,$9,$10))));
		fprintf(stderr,"\n\n\n");
		//print_scope(top_scope);
		print_tree($$,0);
		//fprintf(stderr,"\n\n\n");
		top_scope = scope_pop(top_scope);
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
			$$ = list_append($1,$3);
			/*fprintf(stderr,"\n\n\n");
			print_tree(make_treeFromList(DECLIST,$$),0);
			fprintf(stderr,"\n\n\n");*/
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
			$$ = make_tree(ARRAY,make_tree($8,NULL,NULL),make_tree(ARRAY_RANGE,make_inum(INUM),make_inum(INUM))); 
			/*fprintf(stderr,"\n\n\n");
			print_tree($$,0);
			fprintf(stderr,"\n\n\n");*/
		}
	;

standard_type
	: INTEGER 	{ $$ = INTEGER; }
	| REAL		{ $$ = REAL; }
	;

subprogram_declarations
	: subprogram_declarations subprogram_declaration ';'
		{ 
			$$ = make_tree(SUBDECLS,$1,$2); 
			/*fprintf(stderr,"\n\n\n");
			print_tree($$,0);
			fprintf(stderr,"\n\n\n");*/
		}
	| /* empty */
		{ $$ = NULL; }//make_tree(EMTPY,NULL,NULL); }
	;

subprogram_declaration
	: subprogram_head declarations subprogram_declarations compound_statement
		{	
			$$ = make_tree(SUBDECL,$1,make_tree(SUBPROGDECLBODY,make_treeFromList(DECLIST,$2),make_tree(SUBDECLS,$3,make_tree(COMPSTAT,$4,NULL))));
			top_scope = scope_pop(top_scope); 
		}
	;

subprogram_head:
	FUNCTION ID 
		{	
			//assert(subprogram = scope_search_all(top_scope,$2)==NULL);
			assert(subprogram = scope_insert(top_scope,$2));
			//fprintf(stderr,"\n[SCOPE %s] subprogram: %s\n",top_scope->name,subprogram->name);
			assert((top_scope = scope_push(top_scope,$2))!=NULL);
			//fprintf(stderr,"\n[SCOPE %s]\n",top_scope->name);
		}
			arguments ':' standard_type ';'
		{
			//insert ID into scope
			subprogram->type=FUNCTION;
			subprogram->mark=$6;
			subprogram->args=$4;
			//fprintf(stderr,"\n[SCOPE %s] subprogram: %s %d\n",top_scope->name,subprogram->name,subprogram->type);
			//fprintf(stderr,"[SCOPE %s] subprogram: %s %d",top_scope->name,temp->name,temp->type);
			$$ = make_tree(FUNCTION,tree=make_id(subprogram),make_treeFromList(ARGLIST,$4));
			tree->type=NAME;
			/*fprintf(stderr,"\n\n\n");
			print_tree($$,0);
			fprintf(stderr,"\n\n\n");*/
		}
	| 	
		PROCEDURE ID
		{
			//insert ID into scope
			//assert(subprogram = scope_search_all(top_scope,$2)==NULL);
			assert(subprogram = scope_insert(top_scope,$2));
			assert((top_scope = scope_push(top_scope,$2))!=NULL);
			//fprintf(stderr,"[SCOPE %s]",top_scope->name);

		}
		arguments ';'
		{ 
			//insert ID into scope
			subprogram->type=PROCEDURE;
			subprogram->mark=PROCEDURE;
			subprogram->args=$4;
			$$ = make_tree(PROCEDURE,tree=make_id(subprogram),make_treeFromList(ARGLIST,$4)); 
			tree->type=NAME;
			/*fprintf(stderr,"\n\n\n");
			print_tree($$,0);
			fprintf(stderr,"\n\n\n");*/
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
			$$ = $1; 
		}
	| parameter_list ';' identifier_list ':' type
		{ 	
			//set the types of the id list and mark then as paramters
			//set_names($3,$5,PARAMETER);
			assign_type($3,$5);
			assign_mark($3,PARAMETER);
			//make list of identifier list and append id list to the parameter list
			$$ = list_append($1,$3); 
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
			//if(type($1)!=type($3)){ fprintf(stderr,"Type Mismatch: \n"); }
			$$ = make_tree(ASSIGNOP,$1,$3); 
		}
	| procedure_statement
		{ $$ = $1; }
	| compound_statement
		{ $$ = $1; }//make_treeFromList(COMPSTAT,$1); }
	| IF expression THEN conditions ELSE conditions
		{ 
			//check type of expression for boolean
			//if(type($2)!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); } 
			$$ = make_tree(IF,$2,make_tree(THEN,$4,$6)); 
		}
	| WHILE expression DO conditions
		{ 
			//check if expression is type boolean
			//if(type($2)!=BOOLEAN) { fprintf(stderr,"Boolean Error: \n");  }
			$$ = make_tree(WHILE,$2,$4); 
		}
	| FOR ID ASSIGNOP expression TO expression DO conditions
		{	
			//check if type of temp is type of expression before TO and type temp is type of expression after TO
			temp=scope_search(top_scope,$2);
			//if(type(make_id(temp))!=type($4)){ fprintf(stderr,"Boolean Error: \n"); } 
			//if(type(make_id(temp))!=type($6)){ fprintf(stderr,"Boolean Error: \n"); }
			$$ = make_tree(FOR,make_id(temp),make_tree(DO,make_tree(TO,$4,$6),$8));
		}
	;

ifelse
	: IF expression THEN statement
		{
			//check type of expresion is boolean
			//if(type($2)!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); print_tree($2,0); }
			$$ = make_tree(IF,$2,$4);
		}
	| IF expression THEN conditions ELSE ifelse
		{
			//check type of expression is boolean
			//if(type($2)!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); print_tree($2,0); } 
			$$ = make_tree(IF, $2, make_tree(THEN,$2,$6));
		}
	;


variable
	: ID
		{ 
			$$ = make_id(temp=scope_search(top_scope,$1));
			//assert(temp!=NULL);
		}
	| ID '[' expression ']'
		{ 
			$$ = make_tree(ARRAY_ACCESS,make_id(temp=scope_search(top_scope,$1)),$3);
			//assert(temp!=NULL);
			check_array($$,ARRAY_ACCESS); 
		}
	;

procedure_statement
	: ID
	 	{ 
	 		//search ID and check if valid procedure call
	 		$$ = make_tree(PROCEDURE,tree=make_id(scope_search(top_scope,$1)),NULL);
	 		tree->type=NAME;
	 		//check_procedure($$,PROCEDURE);
	 	}
	| ID '(' expression_list ')'
		{
			//search ID and check if valid procedure call
			$$ = make_tree(PROCEDURE,tree=make_id(scope_search(top_scope,$1)),$3);
			tree->type=NAME;
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
	| ADDOP term
		{ 
			//if(type(make_op(ADDOP,$2,NULL,NULL))==OR){ fprintf(stderr,"Unary Error: \n"); print_tree($$,0); }
			$$ = make_op(ADDOP,$1,$2,NULL); 
		}
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
			/*if((temp=scope_search_all(top_scope,$1)) == NULL){
				fprintf(stderr,"Name %s used but not defined\n",$1);
				exit(1);
			}*/
			temp=scope_search_all(top_scope,$1,&depth);
			$$ = tree = make_id(temp);
			tree->scope_depth=depth; 
		}
	| ID '(' expression_list ')' 
		{
			//check if valid function call
			/*if((temp=scope_search_all(top_scope,$1)) == NULL){
				fprintf(stderr,"Name %s used but not defined\n",$1);
				exit(1);
			}*/
			temp=scope_search(top_scope,$1);
			//fprintf(stderr,"[SCOPE %s EXPECTED %s ACTUAL %s %d",top_scope->name,$1,temp->name,temp->type);
			$$ = make_tree(FUNCTION_CALL,tree=make_id(temp),$3);
			tree->type=NAME;
			check_function($$,FUNCTION); 
		}
	| ID '[' expression_list ']' 
		{ 
			//check if valid array access
			/*if((temp=scope_search_all(top_scope,$1)) == NULL){
				fprintf(stderr,"Name %s used but not defined\n",$1);
				exit(1);
			}*/
			temp=scope_search_all(top_scope,$1,&depth);
			//fprintf(stderr,"[SCOPE %s EXPECTED %s ACTUAL %s",top_scope->name,$1,temp->name);
			$$ = make_tree(ARRAY_ACCESS,tree=make_id(temp),$3);
			tree->scope_depth=depth;
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
tree_t *tree;
node_t *subprogram;
int depth;
int main(){
	assemble = fopen("assemble.s", "w");
	top_scope=NULL;
	temp=NULL;
	tree=NULL;
	subprogram=NULL;
	depth=0;
	yyparse();
	fclose(assemble);
}


