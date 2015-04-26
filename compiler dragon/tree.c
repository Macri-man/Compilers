#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "node.h"
#include "tree.h"
#include "y.tab.h"

void assign_mark(list_t *l,int mark){
	assert(l!=NULL);
	list_t *temp=NULL;
	for(temp=l;temp!=NULL;temp=temp->next){
		//temp->mark=mark;
		temp->node->mark=mark;
	}
}

void assign_type(list_t *l,tree_t *ttype){
	int type;
	assert(l!=NULL);
	list_t *temp=NULL;
	if(ttype->type==ARRAY){
		type=ttype->left->type;
		assign_range(l,ttype->right->left->attribute.ival,ttype->right->right->attribute.ival);
	}else{
		type=ttype->type;
	}
	for(temp=l;temp!=NULL;temp=temp->next){
		//temp->type=type;
		temp->node->type=type;
	}
}

void assign_range(list_t *l,int ivalfirst,int ivallast){
	assert(l!=NULL);
	list_t *temp=NULL;
	for(temp=l;temp!=NULL;temp=temp->next){
		temp->node->semantics.range[0]=ivalfirst;
		temp->node->semantics.range[1]=ivallast;
	}
}

void funcargs(list_t *head){

}

tree_t *make_tree(int type, tree_t *left, tree_t *right){

	tree_t *p=(tree_t *)malloc(sizeof(tree_t));
	assert(p != NULL);
	p->rank=0;;
	p->scope_depth=0;
	p->type=type;
	p->left=left;
	p->right=right;

	return p;
}

tree_t *make_op(int type, int attribute, tree_t *left, tree_t *right){

	tree_t *p=make_tree(type,left,right);
	assert(p != NULL);
	p->attribute.opval=attribute;
	return p;
}

tree_t *make_inum(int val){

	tree_t *p=make_tree(INUM,NULL,NULL);
	p->attribute.ival=val;
	return p;
}

tree_t *make_rnum(float val){

	tree_t *p=make_tree(RNUM,NULL,NULL);
	p->attribute.rval=val;
	return p;
}

tree_t *make_id(node_t *node){

	tree_t *p=make_tree(ID,NULL,NULL);
	p->attribute.sval=node;
	return p;
}

tree_t *make_treeFromList(int type,list_t *ls){
	tree_t *t=make_tree(type,NULL,NULL);
	t->attribute.lval=ls;
	return t;

}
/*
tree_t *make_function(int type,tree_t *id,tree_t *arguments,tree_t *stdtype){
	assign_type_node(id->attribute.sval,stdtype->type);
	id->attribute.sval->funcargs=num_list(arguments->attribute.lval);
	//tree_t *prog2=make_tree(TYPE,stdtype,NULL);
	//tree_t *prog1=make_tree(ARGLIST,NULL,NULL);
	//assign_type(id->lval,stdtype->type);
	tree_t *prog=make_tree(type,id,arguments);
	return prog;
}
tree_t *make_procedure(int type,tree_t *id,tree_t *arguments){

	tree_t *prog1=make_tree(LIST,arguments,NULL);
	tree_t *prog=make_tree(type,id,prog1);
	return prog;
}
*/




/* preorder */
void print_tree(tree_t *t, int spaces){

	int i;

	if(t == NULL){
		return;
	}

	for(i=0;i<spaces;i++){
		fprintf(stderr, " ");
	}

	switch(t->type){
		case ID:
			fprintf(stderr, "[ID:%s\n",(t->attribute.sval)->name);
			break;
		case NAME:
			//fprintf(stderr, "[NAME:" );
			print_id(t->attribute.sval->name);
			if(t->attribute.sval->type==PROCEDURE){
				print_type(t->attribute.sval->type);
			}else{
				print_mark(t->attribute.sval->type);
				print_type(t->attribute.sval->mark);
			}
			fprintf(stderr, "\n");
			break;
		case INUM:
			fprintf(stderr, "[INUM:%d\n",t->attribute.ival);
			break;
		case RNUM:
			fprintf(stderr, "[RNUM:%f\n",t->attribute.rval);
			break;
		case ADDOP:
			print_opval(t->attribute.opval);
			break;
		case MULOP: 
			print_opval(t->attribute.opval);
			break;
		case RELOP: 
			print_opval(t->attribute.opval);
			break;
		case ASSIGNOP: 
			fprintf(stderr, "[ASSIGNOP: \n");
			break;
		case WHILE: 
			fprintf(stderr, "[WHILE: \n");
			break;
		case DO: 
			fprintf(stderr, "[DO: \n");
			break;
		case FOR: 
			fprintf(stderr, "[FOR: \n");
			break;
		case TO: 
			fprintf(stderr, "[TO: \n");
			break;
		case FROM: 
			fprintf(stderr, "[FROM: \n");
			break;
		case IF: 
			fprintf(stderr, "[IF: \n");
			break;
		case THEN: 
			fprintf(stderr, "[THEN: \n");
			break;
		case ELSE: 
			fprintf(stderr, "[ELSE: \n");
			break;
		case NOT: 
			fprintf(stderr, "[NOT:");
			break;
		case INTEGER: 
			fprintf(stderr, "[INTEGER:");
			break;
		case REAL: 
			fprintf(stderr, "[REAL:");
			break;
		case ARRAY: 
			fprintf(stderr, "[ARRAY:");
			break;
		case ARRAY_ACCESS: 
			fprintf(stderr, "[ARRAY ACCESS:\n");
			break;
		case ARRAY_RANGE: 
			fprintf(stderr, "[ARRAY RANGE:\n");
			break;
		case FUNCTION: 
			fprintf(stderr, "[FUNCTION: \n");
			break;
		case FUNCTION_CALL: 
			fprintf(stderr, "[FUNCTION CALL: \n");
			break;
		case PROCEDURE: 
			fprintf(stderr, "[PROCEDURE: \n");
			break;
		case EXPRLIST: 
			fprintf(stderr, "[EXPRESSION LIST: \n");
			break;
		case STATLIST: 
			fprintf(stderr, "[STATEMENT LIST: \n");
			break;
		case COMPSTAT: 
			fprintf(stderr, "[COMPOUND STATEMENTS: \n");
			break;
		case LIST: 
			//fprintf(stderr, "LIST:");
			break;
		case IDLIST:
			if(t->attribute.lval!=NULL){
				fprintf(stderr, "[IDLIST:");
				id_list(t->attribute.lval);
				fprintf(stderr, "\n");
			}
			break;
		case ARGLIST:
			if(t->attribute.lval!=NULL){
				fprintf(stderr, "[ARGLIST:");
				list_print(t->attribute.lval);
				fprintf(stderr, "\n");
			}
			break;
		case DECLIST:
			if(t->attribute.lval!=NULL){
				fprintf(stderr, "[DECLIST:");
				list_print(t->attribute.lval);
				fprintf(stderr, "\n");
			}
			break;
		case SUBDECLS: 
			fprintf(stderr, "[SUBPROGRAM DECLARATIONS: \n");
			break;
		case SUBDECL: 
			fprintf(stderr, "[SUBPROGRAM DECLARATION: \n");
			break;
		case SUBPROGDECL: 
			fprintf(stderr, "[SUBPROGRAM DECLARATION: \n");
			break;
		case SUBPROGDECLBODY: 
			fprintf(stderr, "[SUBPROGRAM DECLARATION BODY: \n");
			break;
		case PROGRAM:
			fprintf(stderr, "[PROGRAM:");
			break;
		default:
			fprintf(stderr, "[UNKOWN]");
	}
	//fprintf(stderr, "\n");
	/* go left */
	print_tree(t->left,spaces+2);
	/*go right */
	print_tree(t->right,spaces+2);
}


void list_print(list_t *head){
	//assert(head!=NULL);
	list_t *ls=NULL;
	for(ls=head;ls!=NULL;ls=ls->next){
		print_id(ls->node->name);
		print_mark(ls->node->mark);
		print_type(ls->node->type);
	}
}

void id_list(list_t *head){
	assert(head!=NULL);
	list_t *ls=NULL;
	for(ls=head;ls!=NULL;ls=ls->next){
		print_id(ls->node->name);
	}
}

void print_id(char *name){
	fprintf(stderr, "[ID:%s ",name);
}

void print_mark(int mark){
	switch(mark){
		case LOCAL:
			fprintf(stderr, " LOCAL ");
			break;
		case PARAMETER:
			fprintf(stderr, " PARAMETER ");
			break;
		case FUNCTION:
			fprintf(stderr, " FUNCTION ");
			break;
		case PROCEDURE:
			fprintf(stderr, " PROCEDURE ");
			break;
		case READ:
			fprintf(stderr, " READ ");
			break;
		case WRITE:
			fprintf(stderr, " WRITE ");
			break;
		case INUM:
			fprintf(stderr, " INUM]");
			break;
		case RNUM:
			fprintf(stderr, " RNUM]");
		default:
			fprintf(stderr, "[UNKOWN]");
	}
}

void print_type(int type){
	switch(type){
		case INTEGER:
			fprintf(stderr, " INTEGER]");
			break;
		case REAL:
			fprintf(stderr, " REAL]");
			break;
		case INUM:
			fprintf(stderr, " INUM]");
			break;
		case RNUM:
			fprintf(stderr, " RNUM]");
			break;
		case FUNCTION:
			fprintf(stderr, " FUNCTION]");
			break;
		case READ:
			fprintf(stderr, " READ]");
			break;
		case WRITE:
			fprintf(stderr, " WRITE]");
			break;
		case PROCEDURE:
			fprintf(stderr, " PROCEDURE] ");
			break;
		default:
			fprintf(stderr, "[UNKOWN]");
	}
}

void print_opval(int opval){
	switch(opval){
		case OR:
			fprintf(stderr, "[ADDOP: or]\n");
			break;
		case PLUS:
			fprintf(stderr, "[ADDOP: +]\n");
			break;
		case MINUS:
			fprintf(stderr, "[ADDOP: -]\n");
			break;
		case AND:
			fprintf(stderr, "[MULLOP: and]\n");
			break;
		case STAR:
			fprintf(stderr, "[MULLOP: *]\n");
			break;
		case SLASH:
			fprintf(stderr, "[MULLOP: /]\n");
			break;
		case DIV:
			fprintf(stderr, "[MULLOP: div]\n");
			break;
		case MOD:
			fprintf(stderr, "[MULLOP: mod]\n");
			break;
		case LT:
			fprintf(stderr, "[RELOP: <]\n");
			break;
		case LE:
			fprintf(stderr, "[RELOP: <=]\n");
			break;
		case GT:
			fprintf(stderr, "[RELOP: >]\n");
			break;
		case GE:
			fprintf(stderr, "[RELOP: =>]\n");
			break;
		case EQ:
			fprintf(stderr, "[RELOP: =]\n");
			break;
		case NEQ:
			fprintf(stderr, "[RELOP: <>]\n");
			break;
		default:
			fprintf(stderr, "[UNKOWN]");
	}
}