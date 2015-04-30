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


void free_tree(tree_t *tree){
	if (tree==NULL) return;
	if (tree->left==NULL && tree->right==NULL) {
		free(tree);
		return;
	}

	if(tree->left!=NULL)
		free_tree(tree->left);
	if(tree->right!=NULL)
		free_tree(tree->right);

	return;
}




/* preorder */
void print_tree(tree_t *t, int spaces){
	int i;

	if(t == NULL){
		return;
	}
	fprintf(stderr, "SPACES:%d",spaces);
	for(i=0;i<spaces;i++){
		fprintf(stderr, " ");
	}

	switch(t->type){
		case ID:
			fprintf(stderr, "[ID:%s ",(t->attribute.sval)->name);
			//fprintf(stderr, "\n");
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
			//fprintf(stderr, "\n");
			break;
		case INUM:
			fprintf(stderr, "[INUM:%d ",t->attribute.ival);
			//fprintf(stderr, "\n");
			break;
		case RNUM:
			fprintf(stderr, "[RNUM:%f ",t->attribute.rval);
			//fprintf(stderr, "\n");
			break;
		case ADDOP:
			print_opval(t->attribute.opval);
			//fprintf(stderr, "\n");
			break;
		case MULOP: 
			print_opval(t->attribute.opval);
			//fprintf(stderr, "\n");
			break;
		case RELOP: 
			print_opval(t->attribute.opval);
			//fprintf(stderr, "\n");
			break;
		case ASSIGNOP: 
			fprintf(stderr, "[ASSIGNOP: ");
			//fprintf(stderr, "\n");
			break;
		case WHILE: 
			fprintf(stderr, "[WHILE: ");
			//fprintf(stderr, "\n");
			break;
		case DO: 
			fprintf(stderr, "[DO: ");
			//fprintf(stderr, "\n");
			break;
		case FOR: 
			fprintf(stderr, "[FOR: ");
			//fprintf(stderr, "\n");
			break;
		case TO: 
			fprintf(stderr, "[TO: ");
			//fprintf(stderr, "\n");
			break;
		case FROM: 
			fprintf(stderr, "[FROM: ");
			//fprintf(stderr, "\n");
			break;
		case IF: 
			fprintf(stderr, "[IF: ");
			//fprintf(stderr, "\n");
			break;
		case THEN: 
			fprintf(stderr, "[THEN: ");
			//fprintf(stderr, "\n");
			break;
		case ELSE: 
			fprintf(stderr, "[ELSE: ");
			//fprintf(stderr, "\n");
			break;
		case NOT: 
			fprintf(stderr, "[NOT:");
			//fprintf(stderr, "\n");
			break;
		case INTEGER: 
			fprintf(stderr, "[INTEGER:");
			//fprintf(stderr, "\n");
			break;
		case REAL: 
			fprintf(stderr, "[REAL:");
			//fprintf(stderr, "\n");
			break;
		case ARRAY: 
			fprintf(stderr, "[ARRAY:");
			//fprintf(stderr, "\n");
			break;
		case ARRAY_ACCESS: 
			fprintf(stderr, "[ARRAY ACCESS: ");
			//fprintf(stderr, "\n");
			break;
		case ARRAY_RANGE: 
			fprintf(stderr, "[ARRAY RANGE: ");
			//fprintf(stderr, "\n");
			break;
		case FUNCTION: 
			fprintf(stderr, "[FUNCTION: ");
			//fprintf(stderr, "\n");
			break;
		case FUNCTION_CALL: 
			fprintf(stderr, "[FUNCTION CALL: ");
			//fprintf(stderr, "\n");
			break;
		case PROCEDURE: 
			fprintf(stderr, "[PROCEDURE: ");
			//fprintf(stderr, "\n");
			break;
		case EXPRLIST:
			fprintf(stderr, "[EXPRESSION LIST: ");
			//fprintf(stderr, "\n");
			break;
		case STATLIST:
			fprintf(stderr, "[STATEMENT LIST: ");
			//fprintf(stderr, "\n");
			break;
		case COMPSTAT:
			//if(t->left!=NULL){
				fprintf(stderr, "[COMPOUND STATEMENTS: ");
			//}
			//fprintf(stderr, "\n");
			break;
		case LIST: 
		//	fprintf(stderr, "[LIST:");
			break;
		case IDLIST:
			if(t->attribute.lval!=NULL){
				fprintf(stderr, "[IDLIST: ");
				id_list(t->attribute.lval);
			}

			//fprintf(stderr, "\n");
			break;
		case ARGLIST:
			if(t->attribute.lval!=NULL){
				fprintf(stderr, "[ARGLIST: ");
				list_print(t->attribute.lval);
			}
			//fprintf(stderr, "\n");
			break;
		case DECLIST:
			if(t->attribute.lval!=NULL){
				fprintf(stderr, "[DECLIST: ");
				list_print(t->attribute.lval);
			}
			//fprintf(stderr, "\n");
			break;
		case SUBDECLS:
			//if(t->left!=NULL){
				fprintf(stderr, "[SUBPROGRAM DECLARATIONS: ");
				//fprintf(stderr, "\n"); 
			//}
			break;
		case SUBDECL: 
			//if(t->left!=NULL){
				fprintf(stderr, "[SUBPROGRAM DECLARATION: ");
			//}
			break;
		case SUBPROGDECL: 
			//if(t->left!=NULL){
				fprintf(stderr, "[SUBPROGRAM DECLARATION: ");
			//}
			break;
		case SUBPROGDECLBODY: 
			//if(t->left!=NULL){
				fprintf(stderr, "[SUBPROGRAM BODY DECLARATION: ");
			//}
			//fprintf(stderr, "\n");
			break;
		case PROGRAM:
			fprintf(stderr, "[PROGRAM: ");
			//fprintf(stderr, "\n");
			break;
		default:
			fprintf(stderr, "[UNKOWN]");
	}
	if(t->type!=LIST){
		fprintf(stderr, "\n");
	}
	/* go left */
	print_tree(t->left,spaces+4);
	/*go right */
	print_tree(t->right,spaces+4);
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
			fprintf(stderr, " INTEGER ");
			break;
		case RNUM:
			fprintf(stderr, " REAL ");
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
			fprintf(stderr, " REAL]");
			break;
		case RNUM:
			fprintf(stderr, " INTEGER]");
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
			fprintf(stderr, " PROCEDURE]");
			break;
		default:
			fprintf(stderr, "[UNKOWN]");
	}
}

void print_opval(int opval){
	switch(opval){
		case OR:
			fprintf(stderr, "[ADDOP: or] ");
			break;
		case PLUS:
			fprintf(stderr, "[ADDOP: +] ");
			break;
		case MINUS:
			fprintf(stderr, "[ADDOP: -] ");
			break;
		case AND:
			fprintf(stderr, "[MULLOP: and] ");
			break;
		case STAR:
			fprintf(stderr, "[MULLOP: *] ");
			break;
		case SLASH:
			fprintf(stderr, "[MULLOP: /] ");
			break;
		case DIV:
			fprintf(stderr, "[MULLOP: div] ");
			break;
		case MOD:
			fprintf(stderr, "[MULLOP: mod] ");
			break;
		case LT:
			fprintf(stderr, "[RELOP: <] ");
			break;
		case LE:
			fprintf(stderr, "[RELOP: <=] ");
			break;
		case GT:
			fprintf(stderr, "[RELOP: >] ");
			break;
		case GE:
			fprintf(stderr, "[RELOP: =>] ");
			break;
		case EQ:
			fprintf(stderr, "[RELOP: =] ");
			break;
		case NEQ:
			fprintf(stderr, "[RELOP: <>] ");
			break;
		default:
			fprintf(stderr, "[UNKOWN]");
	}
	//fprintf(stderr, "\n");
}
