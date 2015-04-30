%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include "node.h"
	#include "scope.h"
	#include "list.h"
	#include "tree.h"
	#include "semantic.h"
	#include "gencode.h"
	#include "y.tab.h"

	extern void yyerror(char* message);
	extern int yylex(void);
	extern int yyparse(void);

	extern scope_t *top_scope;
	extern node_t *temp;
	extern node_t *subprogram;
	extern tree_t *tree;
	extern int line_number;
	int nogen;
	int arglocaloffset;
	int depth;
	int assert;
	FILE * assemble;
	FILE * error;

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
%token FUNCTION PROCEDURE
%token <sval> READ WRITE
%token BBEGIN END
%token IF THEN ELSE
%token WHILE DO FOR TO

%token EMTPY CONDITIONAL TYPE NAME
%token LIST ARRAY_ACCESS ARRAY_RANGE STATEMENT
%token FUNCTION_CALL PROCEDURE_CALL
%token WHILE_DO DECL SUBDECL SUBDECLS SUBPROGDECL SUBPROGDECLHEAD SUBPROGDECLBODY
%token LOCAL PARAMETER IDLIST EXPR EXPRLIST PARALIST ARGLIST DECLIST STATLIST PROCSTAT COMPSTAT
%token FROM

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
	PROGRAM ID 
	{	
		if(nogen==0){
			genmainlabel();
		}
		top_scope = scope_push(top_scope,$2,PROGRAM);
		fprintf(stderr,"\nPUSH SCOPE %s: \n",top_scope->name);
	}
	'(' identifier_list ')' ';'
	{ arglocaloffset=-1; }
	declarations
	{ arglocaloffset=0; }
	subprogram_declarations
	{
		if(nogen==0){
			genstack($2);
			genallocstack(top_scope->localoffset);
		}
	}
		compound_statement
	'.'
	{
		if(nogen==0){
			gendeallocstack(top_scope->localoffset);
			genleave();
			genmain($2);
		}
		check_duplicate($9,top_scope);
		$$ = make_tree(PROGRAM,make_id(temp=scope_insert(top_scope,$2,arglocaloffset)),make_tree(LIST,make_treeFromList(IDLIST,$5),make_tree(LIST,make_treeFromList(DECLIST,$9),make_tree(SUBDECLS,$11,make_tree(COMPSTAT,$13,NULL)))));
		//print_scope(top_scope);
		//fprintf(stderr,"\n\n\n");
		fprintf(stderr,"\n\nPOP SCOPE %s: \n",top_scope->name);
		top_scope = scope_pop(top_scope);
		fprintf(stderr,"\n\n\n");
		fprintf(stderr,"Print TREE\n");
		print_tree($$,0);
	}
	;

identifier_list
	: ID
		{
			//insert ID into scope
			$$ = make_list_node(temp=scope_insert(top_scope,$1,arglocaloffset),$1,IDLIST);
			//$$ = make_id(scope_insert(top_scope,$1));
			//temp->type=ID;
		}
	| identifier_list ',' ID
		{
			//insert ID into scope
			$$ = list_append_node($1,temp=scope_insert(top_scope,$3,arglocaloffset));
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
	: INTEGER 	{ $$ = INUM; }
	| REAL		{ $$ = RNUM; }
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
	: subprogram_head 
	{ arglocaloffset=-1; }
	declarations 
	{ arglocaloffset=0; }
	subprogram_declarations 
	compound_statement
		{
			check_duplicate($3,top_scope);
			$$ = make_tree(SUBDECL,$1,make_tree(SUBPROGDECLBODY,make_treeFromList(DECLIST,$3),make_tree(SUBDECLS,$5,make_tree(COMPSTAT,$6,NULL))));
			fprintf(stderr,"\nPOP SCOPE %s: \n",top_scope->name);
			top_scope = scope_pop(top_scope); 
		}
	;

subprogram_head:
	FUNCTION ID 
		{	
			if(scope_search_all(top_scope, $2, &depth)!=NULL){
				if(assert!=0){
					fprintf(error,"Function name: %s redeclared in Scope %s on line: %d\n",$2,top_scope->name,line_number);
				}else{
					fprintf(stderr,"Function name: %s redeclared in Scope %s on line: %d\n",$2,top_scope->name,line_number);
					exit(1);
				}
			}
			if(nogen==0){
				genstack($2);
			}
			//assert(subprogram = scope_search_all(top_scope,$2)==NULL);
			assert(subprogram = scope_insert(top_scope,$2,arglocaloffset));
			fprintf(stderr,"\nPUSH SCOPE %s %s: \n",top_scope->name,subprogram->name);
			//fprintf(stderr,"\n[SCOPE %s] subprogram: %s\n",top_scope->name,subprogram->name);
			assert((top_scope = scope_push(top_scope,$2,FUNCTION))!=NULL);
			fprintf(stderr,"\nPUSH SCOPE %s: \n",top_scope->name);
			//fprintf(stderr,"\n[SCOPE %s]\n",top_scope->name);
		}
			arguments ':' standard_type ';'
		{
			//insert ID into scope
			//print_nodes($4);
			check_duplicate($4,top_scope);
			subprogram->type=$6;
			subprogram->mark=FUNCTION;
			subprogram->args=$4;
			if(nogen==0){
					genallocstack(top_scope->localoffset);
			}
			/*assert(temp = scope_insert(top_scope,$2));
			temp->type=FUNCTION;
			temp->mark=$6;
			temp->args=$4;*/
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
			if(scope_search_all(top_scope, $2,&depth)!=NULL){
				if(assert!=0){
					fprintf(error,"Procedure name: %s redeclared in Scope %s on line: %d\n",$2,top_scope->name,line_number);
				}else{
					fprintf(stderr,"Procedure name: %s redeclared in Scope %s on line: %d\n",$2,top_scope->name,line_number);
					exit(1);
				}
			}
			if(nogen==0){
				genstack($2);
			}
			//insert ID into scope
			//assert(subprogram = scope_search_all(top_scope,$2)==NULL);
			assert(subprogram = scope_insert(top_scope,$2,arglocaloffset));
			assert((top_scope = scope_push(top_scope,$2,PROCEDURE))!=NULL);
			fprintf(stderr,"\nPUSH SCOPE %s: \n",top_scope->name);
			//fprintf(stderr,"[SCOPE %s]",top_scope->name);

		}
		arguments ';'
		{
			//insert ID into scope
			check_duplicate($4,top_scope);
			subprogram->type=PROCEDURE;
			subprogram->mark=PROCEDURE;
			subprogram->args=$4;
			if(nogen==0){
			genallocstack(top_scope->localoffset);
			}
			/*assert(temp = scope_insert(top_scope,$2));
			temp->type=PROCEDURE;
			temp->mark=PROCEDURE;
			temp->args=$4;*/
			$$ = make_tree(PROCEDURE,tree=make_id(subprogram),make_treeFromList(ARGLIST,$4)); 
			tree->type=NAME;
			/*fprintf(stderr,"\n\n\n");
			print_tree($$,0);
			fprintf(stderr,"\n\n\n");*/
		}
	;

arguments:
	{ arglocaloffset=1; }
	'(' parameter_list ')'
		{
			arglocaloffset=0;
			$$ = $3; 
		}
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
		{
			if(top_scope->type==FUNCTION){
				if($2==NULL){
					temp=scope_search_all(top_scope,top_scope->name,&depth);
					if(assert!=0){
						fprintf(error,"Functions must have a return statement. Function %s does not have a return type on line: %d \n",temp->name,line_number);
					}else{
						fprintf(stderr,"Functions must have a return statement. Function %s does not have a return type on line: %d \n",temp->name,line_number);
						exit(1);
					}
				}
			}
			$$=$2;
		}
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
			//check type of variable == type of expression
			//fprintf(stderr,"\nCheck: %d \n",check_type($1));
			//fprintf(stderr,"\nCheck: %d \n",check_type($3));
			/*if(check_type($3)==PROCEDURE){
				fprintf(stderr,"Procedures cannot return values\n");
				exit(1);
			}*/
			if(check_type($1) && check_type($3)!=0){
				//fprintf(stderr,"ASIGN type%d\n",check_type($1));
					if(check_type($1)!=check_type($3)){
						char *name1=(char *)calloc(10,sizeof(char));
						switch(check_type($1)){
							case ID:
								//fprintf(stderr,"Mismatch Types in assignment: [Variable %s is type %s] [Expression is type %s]\n",$1->left->attribute.sval->name,$1->left->attribute.sval->name,"ID");
								name1=strdup("ID");
								break;
							case INUM:
								//fprintf(stderr,"Mismatch Types in assignment: [Variable %s is type %s] [Expression is type %s]\n",$1->left->attribute.sval->name,$1->left->attribute.sval->name,"INTEGER");
								name1=strdup("INTEGER");
								break;
							case RNUM:
								//fprintf(stderr,"Mismatch Types in assignment: [Variable %s is type %s] [Expression is type %s]\n",$1->left->attribute.sval->name,$1->left->attribute.sval->name,"REAL");
								name1=strdup("REAL");
								break;
							default:
								fprintf(error, "Wrong Type in Expression\n");
						}
						//(strcmp(name1,"INTEGER")!=0)? "REAL":"INTEGER"
						if($1->type==ARRAY_ACCESS){
							if(assert!=0){
							fprintf(error,"Mismatch Types in assignment: [Variable %s is type %s] [Expression is not type %s] on line: %d\n",$1->left->attribute.sval->name,name1,name1,line_number);
							}else{
							fprintf(stderr,"Mismatch Types in assignment: [Variable %s is type %s] [Expression is not type %s] on line: %d\n",$1->left->attribute.sval->name,name1,name1,line_number);
							exit(1);
							}
						}else{
						if(assert!=0){
							fprintf(error,"Mismatch Types in assignment: [Variable %s is type %s] [Expression is not type %s] on line: %d\n",$1->attribute.sval->name,name1,name1,line_number);
						}else{
							fprintf(stderr,"Mismatch Types in assignment: [Variable %s is type %s] [Expression is not type %s] on line: %d\n",$1->attribute.sval->name,name1,name1,line_number);
							exit(1);
						}
						//exit(1);
					}
				}

					if(top_scope->type==FUNCTION){
						if($1->type==ID){
							if($1->attribute.sval->mark==FUNCTION && $3==NULL){
								if(assert!=0){
									fprintf(error,"Functions must have a return statement. Function %s does not have a return type on line: %d \n",$1->attribute.sval->name,line_number);
								}else{
									fprintf(stderr,"Functions must have a return statement. Function %s does not have a return type on line: %d \n",$1->attribute.sval->name,line_number);
									exit(1);
								}
							}	
						}
					}
				}
			$$ = make_tree(ASSIGNOP,$1,$3); 
			if(nogen==0){
				genstatements($$);
			}		
		}
	| procedure_statement
		{ $$ = $1; }
	| compound_statement
		{ $$ = $1; }//make_treeFromList(COMPSTAT,$1); }
	| IF expression THEN conditions ELSE conditions
		{ 
			//check type of expression for boolean
			//if(type($2)!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); }
			if($2->type!=RELOP){
				if(assert!=0){
					fprintf(error,"IF statements expression Expression needs to be Boolean on line: %d\n",line_number);
				}else{
					fprintf(stderr,"IF statements expression Expression needs to be Boolean on line: %d\n",line_number);
					exit(1);
				}
			} 
			$$ = make_tree(IF,$2,make_tree(THEN,$4,make_tree(ELSE,$6,NULL))); 
			if(nogen==0){
				genIfThenElse($$);
			}
		}
	| WHILE expression DO conditions
		{ 
			if($2->type!=RELOP){
				if(assert!=0){
					fprintf(error,"Expression in While needs to be Boolean on line: %d\n",line_number);
				}else{
					fprintf(stderr,"Expression in While needs to be Boolean on line: %d\n",line_number);
					exit(1);
				}
			} 
			//check if expression is type boolean
			//if(type($2)!=BOOLEAN) { fprintf(stderr,"Boolean Error: \n");  }
			$$ = make_tree(WHILE,$2,$4);
			if(nogen==0){			
				genWhileDo($$);
			}
		}
	| FOR ID ASSIGNOP expression TO expression DO conditions
		{
			//check if type of temp is type of expression before TO and type temp is type of expression after TO
			temp=scope_search(top_scope,$2);
			if(check_type(make_id(temp))!=check_type($4)){
				char *name1=(char *)calloc(10,sizeof(char));
					switch(temp->type){
						case ID:
							//fprintf(stderr,"Mismatch Types in assignment: [Variable %s is type %s] [Expression is type %s]\n",$1->left->attribute.sval->name,$1->left->attribute.sval->name,"ID");
							name1=strdup("ID");
							break;
						case INUM:
							//fprintf(stderr,"Mismatch Types in assignment: [Variable %s is type %s] [Expression is type %s]\n",$1->left->attribute.sval->name,$1->left->attribute.sval->name,"INTEGER");
							name1=strdup("INTEGER");
							break;
						case RNUM:
							//fprintf(stderr,"Mismatch Types in assignment: [Variable %s is type %s] [Expression is type %s]\n",$1->left->attribute.sval->name,$1->left->attribute.sval->name,"REAL");
							name1=strdup("REAL");
							break;
						default:
							fprintf(error, "Wrong Type in Expression\n");
					}
				if(temp->type==ARRAY_ACCESS){
					if(assert!=0){
						fprintf(error,"Mismatch Types in FOR: [Variable %s is type %s] [Expression is not type %s] on line: %d\n",temp->name,name1,name1,line_number);
					}else{
						fprintf(stderr,"Mismatch Types in FOR: [Variable %s is type %s] [Expression is not type %s] on line: %d\n",temp->name,name1,name1,line_number);
						exit(1);
					}
				}else{
					if(assert!=0){
						fprintf(error,"Mismatch Types in FOR: [Variable %s is type %s] [Expression is not type %s] on line: %d\n",temp->name,name1,name1,line_number);
					}else{
						fprintf(stderr,"Mismatch Types in FOR: [Variable %s is type %s] [Expression is not type %s] on line: %d\n",temp->name,name1,name1,line_number);
						exit(1);
					}
				}
			}
			//if(type(make_id(temp))!=type($4)){ fprintf(stderr,"Boolean Error: \n"); } 
			//if(type(make_id(temp))!=type($6)){ fprintf(stderr,"Boolean Error: \n"); }
			$$ = make_tree(FOR,make_id(temp),make_tree(DO,$8,make_tree(FROM,$4,$6)));
		}
	;

ifelse
	: IF expression THEN statement
		{
			if($2->type!=RELOP){
				 if(assert!=0){
				fprintf(error,"IF statements expression Expression needs to be Boolean on line: %d\n",line_number);
				}else{
				fprintf(stderr,"IF statements expression Expression needs to be Boolean on line: %d\n",line_number);
				exit(1);
				}
			} 
			//check type of expresion is boolean
			//if(type($2)!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); print_tree($2,0); }
			$$ = make_tree(IF,$2,make_tree(THEN,$4,NULL));
			if(nogen==0){			
				genIfThen($$);
			}
		}
	| IF expression THEN conditions ELSE ifelse
		{
			if($2->type!=RELOP){
				if(assert!=0){
				fprintf(error,"IF statements expression Expression needs to be Boolean on line: %d\n",line_number);
				}else{
				fprintf(stderr,"IF statements expression Expression needs to be Boolean on line: %d\n",line_number);
				exit(1);
				}
			} 
			//check type of expression is boolean
			//if(type($2)!=BOOLEAN){ fprintf(stderr,"Boolean Error: \n"); print_tree($2,0); } 
			$$ = make_tree(IF,$2,make_tree(THEN,$4,make_tree(ELSE,$6,NULL)));
			if(nogen==0){			
				genIfThenElse($$);
			}
		}
	;


variable
	: ID
		{ 	
			if((temp=scope_search_all(top_scope,$1,&depth))==NULL){
				if(assert!=0){
					fprintf(error,"Variables must be declared: [Variable %s] is not defined in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
				}else{
					fprintf(stderr,"Variables must be declared: [Variable %s] is not defined in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
					exit(1);
				}
				temp=make_node($1);
				temp->type=0;
				temp->mark=0;
				$$ = make_id(temp);
			}else if(temp->depth>0 && top_scope->type==FUNCTION && temp->mark!=FUNCTION){
				if(assert!=0){
					fprintf(error,"Variable must be local to be assigned: [Variable %s] is not local variable in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
				}else{
					fprintf(stderr,"Variable must be local to be assigned: [Variable %s] is not local variable in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
					exit(1);
				}
				$$ = make_id(temp);
			}else{ 
				$$ = make_id(temp);
			}
		}
	| ID '[' expression ']'
		{
			if((temp=scope_search_all(top_scope,$1,&depth))==NULL){
				if(assert!=0){
				fprintf(error,"Arrays must be declared: Array %s is not defined in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
				}else{
				fprintf(stderr,"Arrays must be declared: Array %s is not defined in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
				exit(1);
				}
				temp=make_node($1);
				temp->type=0;
				temp->mark=0;
				$$ = make_tree(ARRAY_ACCESS,make_id(temp),$3);
			}else if(check_type($3)!=INUM){
				if(assert!=0){
				fprintf(error,"Array Access %s needs to be INTEGER on line: %d\n",temp->name,line_number);
				}else{
				fprintf(stderr,"Array Access %s needs to be INTEGER on line: %d\n",temp->name,line_number);
				exit(1);
				}
				$$ = make_tree(ARRAY_ACCESS,make_id(temp),$3);
			}else{
				$$ = make_tree(ARRAY_ACCESS,make_id(temp),$3);
				check_array($$); 
			}
		}
	;

procedure_statement
	: ID
	 	{ 
	 		//search ID and check if valid procedure call
	 		$$ = make_tree(PROCEDURE,tree=make_id(temp=scope_search_all(top_scope,$1,&depth)),NULL);
	 		tree->type=NAME;
	 	}
	| ID '(' expression_list ')'
		{
			//search ID and check if valid procedure call
			$$ = make_tree(PROCEDURE,tree=make_id(temp=scope_search_all(top_scope,$1,&depth)),$3);
			tree->type=NAME;
			check_procedure($$,temp->name,top_scope->name);
			if(nogen==0){
				genstatements($$);
			}
		}
	| WRITE '(' expression_list ')'
		{
			temp=make_node($1);
			temp->type=FUNCTION;
			temp->mark=WRITE;
			/*if(check_type($3)!=INUM && check_type($3)!=RNUM){
				fprintf(error,"Write need to be called with INTEGER or REALS");
			}*/
			$$ = make_tree(PROCEDURE,tree=make_id(temp),$3);
			tree->type=NAME;
			if(nogen==0){
				genwrite($1,$3);
			}
		}

	| READ '(' expression_list ')'
		{
			temp=make_node($1);
			temp->type=FUNCTION;
			temp->mark=READ;
			/*if(check_type($3)!=INUM && check_type($3)!=RNUM){
				fprintf(error,"Read need to be called with INTEGER or REALS");
			}*/
			$$ = make_tree(PROCEDURE,tree=make_id(temp),$3);
			tree->type=NAME;
			if(nogen==0){
				genread($1,$3);
			}	
		}
	;

expression_list
	: expression
		{ $$ = make_tree(EXPRLIST,NULL,$1); }
	| expression_list ',' expression
		{ 
			$$ = make_tree(EXPRLIST,$1,$3); 
		}
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
			if(ADDOP==OR){ 
				if(assert!=0){
					fprintf(error,"Unary Error cannot have or of a number on line: %d\n",line_number); 
				}else{
					fprintf(stderr,"Unary Error cannot have or of a number on line: %d\n",line_number);
					exit(1);
				}
			}
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
			if((temp=scope_search_all(top_scope,$1,&depth)) == NULL){
				if(assert!=0){
				fprintf(error,"ID %s used but not defined in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
				}else{
				fprintf(stderr,"ID %s used but not defined in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
				exit(1);
				}
				temp=make_node($1);
				temp->type=0;
				temp->mark=0;
				$$ = tree = make_id(temp);
				tree->scope_depth=depth;
			}else if(temp->mark==PROCEDURE){
			if(assert!=0){
				fprintf(error,"Procedures cannot return values on line: %d\n",line_number);
				}else{
				fprintf(stderr,"Procedures cannot return values on line: %d\n",line_number);
				exit(1);
				}
				$$ = tree = make_id(temp);
				tree->scope_depth=depth;
			}else{
				$$ = tree = make_id(temp);
				tree->scope_depth=depth;
			} 
		}
	| ID '(' expression_list ')' 
		{
			//fprintf(stderr,"id %s\n",$1);
			//check if valid function call
			if((temp=scope_search(top_scope,$1)) == NULL){
				if(assert!=0){
					fprintf(error,"ID %s used but not defined in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
				}else{
				 	fprintf(stderr,"ID %s used but not defined in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
					exit(1);
				}
				temp=make_node($1);
				temp->type=0;
				temp->mark=0;
				$$ = make_tree(FUNCTION_CALL,tree=make_id(temp),$3);
				tree->type=NAME;
			}else if(temp->mark==PROCEDURE){
				if(assert!=0){
					fprintf(error,"Procedures cannot return values\n");
				}else{
					fprintf(stderr,"Procedures cannot return values\n");
					exit(1);
				}
				$$ = make_tree(FUNCTION_CALL,tree=make_id(temp),$3);
				tree->type=NAME;
			}else{
			//fprintf(stderr,"[SCOPE %s EXPECTED %s ACTUAL %s %d",top_scope->name,$1,temp->name,temp->type);
				$$ = make_tree(FUNCTION_CALL,tree=make_id(temp),$3);
				tree->type=NAME;
				check_function($$,temp->name,top_scope->name); 
			}
		}
	| ID '[' expression_list ']' 
		{ 
			//check if valid array access
			if((temp=scope_search_all(top_scope,$1,&depth)) == NULL){
				if(assert!=0){
					fprintf(error,"ID %s used but not defined in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
				}else{
					fprintf(stderr,"ID %s used but not defined in Scope of %s on line: %d\n",$1,top_scope->name,line_number);
					exit(1);
				}
				temp=make_node($1);
				temp->type=0;
				temp->mark=0;
				$$ = make_tree(ARRAY_ACCESS,tree=make_id(temp),$3);
			}else if(check_type($3)!=INUM){
				if(assert!=0){
					fprintf(error,"Array Access needs to be INTEGER on line: %d\n",line_number);
				}else{
					fprintf(stderr,"Array Access needs to be INTEGER on line: %d\n",line_number);
					exit(1);
				}
				$$ = make_tree(ARRAY_ACCESS,tree=make_id(temp),$3);
				tree->scope_depth=depth;
			}else{
			//temp=scope_search_all(top_scope,$1,&depth);
			//fprintf(stderr,"[SCOPE %s EXPECTED %s ACTUAL %s",top_scope->name,$1,temp->name);
			$$ = make_tree(ARRAY_ACCESS,tree=make_id(temp),$3);
				tree->scope_depth=depth;
				check_array($$);
			}
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
int arglocaloffset;
int main(int argc, char ** argv){
//	fprintf(stderr,"codegen %d",nogen);
	if(argv[1]==NULL){
		fprintf(stderr,"Need codegen args -n for no code gen -c for code gen\n");
		exit(1);
	}
	if(argv[2]==NULL){
		fprintf(stderr,"Need assert arg -s for assertion -e for error file\n");
		exit(1);
	}
	nogen=!strcmp(argv[1],"-n");
	assert=strcmp(argv[2],"-s");
	fprintf(stderr,"%d %d",nogen,assert);
	assemble = fopen("assemble.s", "w");
	error = fopen("error.txt","w");
	top_scope=NULL;
	temp=NULL;
	tree=NULL;
	line_number=1;
	depth=0;
	arglocaloffset=0;
	subprogram=NULL;
	yyparse();
	fclose(assemble);
	fclose(error);
}


