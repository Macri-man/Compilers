#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "semantic.h"
#include "list.h"
#include "y.tab.h"

int type(tree_t *expression){
	if(expression->type==ARRAY_ACCESS){
		if(expression->left->attribute.sval->type=RELOP) return BOOLEAN;
		return expression->left->attribute.sval->type;
	}else if(expression->type==RELOP){
		return BOOLEAN
	}else{
		return -1;
	}
	print_tree(expression,0);
	return -1;
}

int lengthArg(tree_t *args){
	return num_list(args->lval);
}

int equalArgs(node_t *args1,node_t *args2){
	node_t *n1=NULL;
	node_t *n2=NULL;
	for(n1=args1,n2=args2;n1!=NULL,n2!=NULL;n1->args1,n2->args2){
		if(args1->type!=args2->type) return -1;
	}
	return 0;
}

void check_array(tree_t *array,int type){
	
}

void check_procedure(tree_t *procedure,int type){

}

void check_function(tree_t *function,int type){
	node_t *functionArgs;
	node_t *functionTypes;
	tree_t *func;

	assert(function!=NULL);
	func=function->left;
	assert(func!=NULL&&func->type=FUNCTION);
	assert(func->attribute.sval!=NULL&&func->attribute.sval->type==type);
	functionArgs=func->attribute.sval->name;

	assert(func->right!=NULL);
	functionTypes=expression_list(func->right);

	if(lengthArg(functionArgs)!=lengthArg(functionTypes)){
		fprintf(stderr, "Wrong Number of Arguments\n");
	}

	if(equalArgs(functionArgs,functionTypes)==-1){
		fprintf(stderr, "Wrong Arguments Types\n");
	}
}