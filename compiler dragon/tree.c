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
		temp->mark=mark;
		temp->attribute.node->mark=mark;
	}
}

void assign_type(list_t *l,tree_t *ttype){
	int type;
	assert(l!=NULL);
	list_t *temp=NULL;
	if(ttype->type==ARRAY){
		type=ttype->right->type;
		assign_range(l,ttype->right->left->attribute.ival,ttype->right->right->attribute.ival);
	}else{
		type=ttype->left->type;
	}
	for(temp=l;temp!=NULL;temp=temp->next){
		temp->type=type;
		temp->attribute.node->type=type;
	}
}

void assign_range(list_t *l,int ivalfirst,int ivallast){
	assert(l!=NULL);
	list_t *temp=NULL;
	for(temp=l;temp!=NULL;temp=temp->next){
		temp->attribute.node->semantics.range[0]=ivalfirst;
		temp->attribute.node->semantics.range[1]=ivallast;
	}
}

void funcargs(list_t *head){

}

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

tree_t *make_program(int type,tree_t *id,tree_t *idlist,tree_t *decl,tree_t *subprogdecl,tree_t *compstm){
	
	tree_t *prog4=make_tree(SUBPROGDECL,subprogdecl,NULL);
	tree_t *prog3=make_tree(STATEMENT,compstm,prog4);
	tree_t *prog2=make_tree(DECL,decl,prog3);
	tree_t *prog1=make_tree(LIST,idlist,prog2);
	tree_t *prog=make_tree(type,id,prog1);
	return prog;
}
*//*
tree_t *make_decl(int type,list_t *decl,list_t *idlist){
	/*assign_mark(idlist,mark);
	if(ttype->type=ARRAY){
		assign_type(idlist,ttype->left->type);
		assign_range(idlist,ttype->left->left->ival,ttype->left->right->ival);
	}else{
		assign_type(idlist,ttype->type);
	}*/
	/*list_t *decllist=NULL;
	if(decl!=NULL){
		list_t *decllist=make_list(idlist,idlist->name,type);
		decllist->next=NULL;
		return decllist;
	}else{
		list_t *decllist=list_append(decl,idlist);
		return decllist;
	}/*
	tree_t *prog2=make_tree(TYPE,ttype,NULL);
	tree_t *prog1=make_tree(LIST,idlist,prog2);
	tree_t *prog=make_tree(type,decl,prog1);*/
//}
/*
tree_t *make_array(int type,tree_t *firstnum,tree_t *lastnum,tree_t *stdtype){
	firstnum->type=stdtype->type;
	lastnum->type=stdtype->type;
	//tree_t *prog3=make_tree(TYPE,stdtype,NULL);
	tree_t *prog2=make_tree(TYPE,NULL,stdtype);
	tree_t *prog1=make_tree(INUM,firstnum,lastnum);
	tree_t *prog=make_tree(type,prog1,prog2);
	return prog;
}

tree_t *make_subdecl(int type,tree_t *subproghead,tree_t *decl,tree_t *compstm){
	
	tree_t *prog2=make_tree(STATEMENT,compstm,NULL);
	tree_t *prog1=make_tree(DECL,decl,prog2);
	tree_t *prog=make_tree(type,subproghead,prog1);
	return prog;
}

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

tree_t *make_idlist(int type,list_t *idlist){
	tree_t *t=make_tree(type,NULL,NULL);
	t->attribute.lval=idlist;
	return t;
}

tree_t *make_statmnt(int type,tree_t *statement){
	tree_t *t=make_tree(type,NULL,NULL);
	t->attribute.lval=make_list_tree(statement,NULL,type);
	return t;
}

tree_t *list_append_statmnt(int type,tree_t *statementlist,tree_t *statement){
	statementlist->attribute.lval=list_append_tree(statementlist->lval,statement);
	return statementlist;
}

tree_t *make_exprlist(int type,tree_t *expr){
	tree_t *t=make_tree(type,NULL,NULL);
	t->attribute.lval=expr;
	return t;
}

tree_t *list_append_exprlist(int type,tree_t *exprlist,tree_t *expr){
	exprlist->attribute.lval=list_append_tree(exprlist->lval,expr);
	return exprlist;
}

tree_t *parlist_list(int type,tree_t *parlist,tree_t *idlist){
	parlist->attribute.lval=list_append_tree(parlist->attribute.lval,idlist);
	return parlist;
}

tree_t *make_parlist(int type,tree_t *idlist,tree_t *ttype,int mark){
	//tree_t *prog1=make_tree(TYPE,ttype,NULL);
	tree_t *prog=make_tree(type,NULL,NULL);
	prog->attribute.lval=make_list_tree(idlist,idlist->name,idlist->type);
	return prog;
}

tree_t *make_cond(int type,tree_t *expr,tree_t *stm1,tree_t *stm2){

	tree_t *prog1=make_tree(LIST,stm1,stm2);
	tree_t *prog=make_tree(type,expr,prog1);
	return prog;
}

tree_t *make_whdo(int type,tree_t *expr,tree_t *stm){

	tree_t *prog=make_tree(type,expr,stm);
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
			print_ADDOP(t->attribute.opval);
			break;
		case MULOP: 
			print_MULOP(t->attribute.opval);
			break;
		case RELOP: 
			print_RELOP(t->attribute.opval);
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
	switch(opval){
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


