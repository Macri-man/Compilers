#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <semantic.h>
#include "y.tab.h"

void check_function(tree_t *function,int type);
void check_procedure(tree_t *procedure,int type);
void check_array(tree_t *array,int type);

int lengthArg(node_t *args);
int equalArgs(node_t *args1,node_t *args2);

int type(tree_t *expression){
	if(expression->type==ARRAY_ACCESS){
		return expression->left->attribute.sval->type;
	}
	print_tree(expression,0);
	return -1;
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