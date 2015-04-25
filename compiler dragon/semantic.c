#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "list.h"
#include "semantic.h"
#include "y.tab.h"

int type(tree_t *expression){
	/*if(expression->type==ARRAY_ACCESS){
		if(expression->left->attribute.sval->type==RELOP) return BOOLEAN;
		return expression->left->attribute.sval->type;
	}else if(expression->type==RELOP){
		return BOOLEAN;
	}else{
		return -1;
	}
	return -1;*/
}

int check_type(tree_t *expression){
	if(expression==NULL) return -1;
	switch(expression->type){
		case ID:
			return expression->attribute.sval->type;
			break;
		case INUM:
			return expression->type;
			break;
		case RNUM:
			return expression->type;
			break;
		case ADDOP:
			return (check_type(expression->left)==check_type(expression->right))? check_type(expression->left): -1; 
			break;
		case MULOP:
			return (check_type(expression->left)==check_type(expression->right))? check_type(expression->left): -1;
			break;
		case DIV:
			return (check_type(expression->left)==check_type(expression->right))? check_type(expression->left): -1;
			break;
		default:
			fprintf(stderr, "Wrong Type in Expression: %d\n",expression->type);
	}
}

int lengthArg(list_t *args){
	return num_list(args);
}

int equalArgs(tree_t *functionArgs,tree_t *functionTypes){
	/*tree_t *n1=NULL;
	list_t *n2=NULL;
	for(n1=functionArgs,n2=functionTypes->lval;n1!=NULL,n2!=NULL;n2=n2->next){
		if(n1->type!=n2->type) return -1;
	}
	return 0;*/
}

void check_array(tree_t *array,int type){
	
}

void check_procedure(tree_t *procedure,int type){

}

void check_function(tree_t *function,int type){
	/*node_t *functionArgs;
	node_t *functionTypes;
	tree_t *func;

	assert(function!=NULL);
	func=function->left;
	assert(func!=NULL&&func->type==FUNCTION);
	assert(func->attribute.sval!=NULL&&func->attribute.sval->type==type);
	functionArgs=func->attribute.sval;

	assert(func->right!=NULL);
	functionTypes=func->right;
	assert(functionTypes->type==PARALIST);

	if(functionArgs->numargs!=lengthArg(functionTypes)){
		fprintf(stderr, "Wrong Number of Arguments\n");
	}

	if(equalArgs(functionArgs,functionTypes)==-1){
		fprintf(stderr, "Wrong Arguments Types\n");
	}*/
}