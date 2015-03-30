#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "node.h"
#include "tree.h"
#include "y.tab.h"

/* contructor */
tree_t *make_tree(int type, tree_t *left, tree_t *right){

	tree_t *p=(tree_t *)malloc(sizeof(tree_t));
	assert(p != NULL);

	p->type=type;
	p->left=left;
	p->right=right;

	return p;
}

tree_t *make_op(int type, int attribute, tree_t *left, tree_t *right){

	tree_t *p=make_tree(type,left,right);
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

tree_t *make_program(int type,tree_t *id,tree_t *idlist,tree_t *decl,tree_t *subprogdecl,tree_t *compstm){
	
	tree_t *prog4=make_tree(SUBPROGDECL,subprogdecl,NULL);
	tree_t *prog3=make_tree(STATEMENT,compstm,prog4);
	tree_t *prog2=make_tree(DECL,decl,prog3);
	tree_t *prog1=make_tree(LIST,idlist,prog2);
	tree_t *prog=make_tree(type,id,prog1);
	return prog;
}

void assign_mark(tree_t *t,int mark){
	tree_t *temp;
	for(temp=t;temp!=NULL;temp=temp->left){
		t->attribute.sval->mark=mark;
	}
	for(temp=t;temp!=NULL;temp=temp->right){
		t->attribute.sval->mark=mark;
	}
}

void assign_type(tree_t *t,int type){
	tree_t *temp;
	for(temp=t;temp!=NULL;temp=temp->left){
		t->attribute.sval->type=type;
	}
	for(temp=t;temp!=NULL;temp=temp->right){
		t->attribute.sval->type=type;
	}
}

tree_t *make_decl(int type,tree_t *decl,tree_t *idlist,tree_t *ttype,int mark){
	assign_mark(idlist,mark);
	if(ttype->ARRAY){
		assign_type(id,ttype->left->type);
	}else{
		assign_type(id,ttype->type);
	}
	tree_t *prog2=make_tree(TYPE,ttype,NULL);
	tree_t *prog1=make_tree(LIST,idlist,prog2);
	tree_t *prog=make_tree(type,decl,prog1);
	return prog;
}

tree_t *make_array(int type,tree_t *firstnum,tree_t *lastnum,tree_t *stdtype){
	
	tree_t *prog3=make_tree(TYPE,stdtype,NULL);
	tree_t *prog2=make_tree(INUM,NULL,lastnum);
	tree_t *prog1=make_tree(INUM,firstnum,prog2);
	tree_t *prog=make_tree(type,prog3,prog1);
	return prog;
}

tree_t *make_subdecl(int type,tree_t *subproghead,tree_t *decl,tree_t *compstm){
	
	tree_t *prog2=make_tree(STATEMENT,compstm,NULL);
	tree_t *prog1=make_tree(DECL,decl,prog2);
	tree_t *prog=make_tree(type,subproghead,prog1);
	return prog;
}

tree_t *make_function(int type,tree_t *id,tree_t *arguments,tree_t *stdtype){
	assign_type(id,stdtype->type);
	tree_t *prog2=make_tree(TYPE,stdtype,NULL);
	tree_t *prog1=make_tree(LIST,arguments,prog2);
	tree_t *prog=make_tree(type,id,prog1);
	return prog;
}
tree_t *make_procedure(int type,tree_t *id,tree_t *arguments){

	tree_t *prog1=make_tree(LIST,arguments,NULL);
	tree_t *prog=make_tree(type,id,prog1);
	return prog;
}
tree_t *make_parlist(int type,tree_t *parlist,tree_t *idlist,tree_t *ttype,int mark){
	assign_mark(idlist,mark);
	if(ttype->ARRAY){
		assign_type(id,ttype->left->type);
	}else{
		assign_type(id,ttype->type);
	}
	tree_t *prog2=make_tree(TYPE,ttype,NULL);
	tree_t *prog1=make_tree(LIST,idlist,prog2);
	tree_t *prog=make_tree(type,parlist,prog1);
	return prog;
}

tree_t *make_cond(int type,tree_t *expr,tree_t *stm,tree_t *stm){

	tree_t *prog1=make_tree(LIST,stm,stm);
	tree_t *prog=make_tree(type,expr,prog1);
	return prog;
}

tree_t *make_whdo(int type,tree_t *expr,tree_t *stm){

	tree_t *prog=make_tree(type,expr,stm);
	return prog;
}



/* preorder */
void print_tree(tree_t *t, int spaces){

	int i;

	if(t == NULL){
		return;
	}

	for(i=0;i<spaces;i++){
		fprintf(stderr, " ");
	}

	/* process root */
	switch(t->type){
		case ID:
			fprintf(stderr, "[ID:%s\n",(t->attribute.sval)->name);
			break;
		case INUM:
			fprintf(stderr, "[INUM:%d\n",t->attribute.ival);
			break;
		case RNUM:
			fprintf(stderr, "[RNUM:%f\n",t->attribute.rval);
			break;
		case ADDOP:
			print_ADDOP(t->type);
			break;
		case MULOP: 
			print_MULOP(t->type);
			break;
		case RELOP: 
			print_RELOP(t->type);
			break;
		default:
			fprintf(stderr, "[UNKOWN]");
	}
	//fprintf(stderr, "\n");
	/* go left */
	print_tree(t->left,spaces+4);
	/*go right */
	print_tree(t->right,spaces+4);

}

void print_ADDOP(int opval){
	swtich(opval){
		case OR:
			fprintf(stderr, "[ADDOP: or\n");
			break;
		case PLUS:
			fprintf(stderr, "[ADDOP: +\n");
			break;
		case MINUS:
			fprintf(stderr, "[ADDOP: -\n");
			break;
		default:
			fprintf(stderr, "[UNKOWN]");
	}
}

void print_MULOP(int opval){
	switch(opval){
		case AND:
			fprintf(stderr, "[MULLOP: and\n");
			break;
		case STAR:
			fprintf(stderr, "[MULLOP: *\n");
			break;
		case SLASH:
			fprintf(stderr, "[MULLOP: /\n");
			break;
		case DIV:
			fprintf(stderr, "[MULLOP: div\n");
			break;
		case MOD:
			fprintf(stderr, "[MULLOP: mod\n");
			break;
		default:
			fprintf(stderr, "[UNKOWN]");
	}
}

void print_RELOP(int opval){
	switch(opval){
		case LT:
			fprintf(stderr, "[RELOP: <\n");
			break;
		case LE:
			fprintf(stderr, "[RELOP: <=\n");
			break;
		case GT:
			fprintf(stderr, "[RELOP: >\n");
			break;
		case GE:
			fprintf(stderr, "[RELOP: =>\n");
			break;
		case EQ:
			fprintf(stderr, "[RELOP: =\n");
			break;
		case NEQ:
			fprintf(stderr, "[RELOP: <>\n");
			break;
		default:
			fprintf(stderr, "[UNKOWN]");
	}
}


