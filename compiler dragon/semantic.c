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
		case ARRAY_ACCESS:
			return expression->left->attribute.sval->type;
		case FUNCTION_CALL:
			return expression->left->attribute.sval->type;
		case PROCEDURE:
			return expression->left->attribute.sval->type;
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
			fprintf(stderr, "Wrong Type in Expression: %d ",expression->type);
	}
}

void check_duplicate(list_t *list){
	//fprintf(stderr, "%s\n", "DUPLICATES");
	if(list == NULL) return ; // No list, no conflicts
	if(list->next == NULL) return ; // One variable, no conflicts!

	list_t *temp = list;
	list_t *comp = list->next;

	while(temp!=NULL){
		for(comp;comp!=NULL;comp=comp->next){
			if((temp->node->name != NULL) && (comp->node->name != NULL)){
				//fprintf(stderr, "FIRST: %s  SECOND: %s\n",temp->node->name,comp->node->name);
				if(!strcmp(temp->node->name, comp->node->name)){
					fprintf(stderr," Variable redeclaration not allowed\n");
					exit(1);
				}
			}
		}
		temp=temp->next;
		if(temp->next!=NULL){
			comp=temp->next;
		}else{
			return ;
		}
		//fprintf(stderr, "FIRST: %s  SECOND: %s\n",temp->node->name,comp->node->name);
	}
}

int lengthArg(tree_t *args){

	int num;
	for(num=1;args!=NULL;num++,args=args->left){
		//fprintf(stderr, "\nNUMBER:%d ARG TYPE:%d\n",num,args->type);
	}

	return num;
}

int equalArgs(list_t *functionArgs,tree_t *expressionTypes){
	tree_t *tree=NULL;
	list_t *list=NULL;
	node_t *temp=NULL;
	for(list=functionArgs->next;list->next!=NULL;list=list->next);
	temp=list->node;
	fprintf(stderr, "%s %s\n",temp->name,temp->next->name);
	for(temp,tree=expressionTypes;temp!=NULL && tree->type==EXPRLIST;temp=temp->next,tree=tree->left){
		//fprintf(stderr, "TREE:%d\n",tree->type);
		if(tree->left->type==EXPRLIST){
			//fprintf(stderr, "tree:%d %s list%d %s\n",tree->right->attribute.sval->type,tree->attribute.sval->name,temp->type,temp->name);
			if(check_type(tree)!=temp->type) return -1;
		}else{
			//fprintf(stderr, "tree:%d %s list%d %s\n",tree->attribute.sval->type,tree->attribute.sval->name,temp->type,temp->name);
			if(check_type(tree->right)!=temp->type) return -1;
		}
	}
	return 0;
}

void check_array(tree_t *expression){
	
}

void check_procedure(tree_t *procedure){
	list_t *functionArgs;
	tree_t *expressionTypes;
	node_t *funcID;

	assert(procedure!=NULL);
	funcID=procedure->left->attribute.sval;
	assert(funcID!=NULL&&funcID->mark==PROCEDURE);
	functionArgs=funcID->args;

	assert(procedure->right!=NULL);
	expressionTypes=procedure->right;
	assert(expressionTypes->type==EXPRLIST);
	if(num_list(functionArgs)!=lengthArg(expressionTypes)){
		fprintf(stderr, "Wrong Number of Arguments\n");
		exit(1);
	}

	if(equalArgs(functionArgs,expressionTypes)==-1){
		fprintf(stderr, "Wrong Arguments Types\n");
		exit(1);
	}
}

void check_function(tree_t *function){
	list_t *functionArgs;
	tree_t *expressionTypes;
	node_t *funcID;

	assert(function!=NULL);
	funcID=function->left->attribute.sval;
	assert(funcID!=NULL&&funcID->mark==FUNCTION);
	functionArgs=funcID->args;

	assert(function->right!=NULL);
	expressionTypes=function->right;
	assert(expressionTypes->type==EXPRLIST);
	if(num_list(functionArgs)!=lengthArg(expressionTypes)){
		fprintf(stderr, "Wrong Number of Arguments\n");
		exit(1);
	}

	if(equalArgs(functionArgs,expressionTypes)==-1){
		fprintf(stderr, "Wrong Arguments Types\n");
		exit(1);
	}
}