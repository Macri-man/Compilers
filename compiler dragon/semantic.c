#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "list.h"
#include "semantic.h"
#include "y.tab.h"

extern int line_number;

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
		case EXPRLIST:
			return (check_type(expression->left)==check_type(expression->right))? check_type(expression->left): -1;
			break;
		default:
			fprintf(error, "Wrong Type in Expression: %d ",expression->type);
	}
}

void check_duplicate(list_t *list,struct scope_s *scope){
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
					fprintf(error," Variable redeclaration not allowed: [Variable %s redeclared in Scoped of %s] on line: %d\n",temp->node->name,scope->name,line_number);
					//exit(1);
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
	if(args==NULL) return 0;
	return lengthArg(args->left)+1;

}

int equalArgs(list_t *functionArgs,tree_t *expressionTypes){
	tree_t *tree=NULL;
	list_t *list=NULL;
	node_t *temp=NULL;
	for(list=functionArgs;list->next!=NULL;list=list->next);
	temp=list->node;
	//fprintf(stderr, "%s\n",temp->name);
	for(temp,tree=expressionTypes;temp!=NULL && tree!=NULL;temp=temp->next,tree=tree->left){
		//fprintf(stderr, "TREE:%d\n",tree->type);
		/*if(tree->left->type!=EXPRLIST){
			//fprintf(stderr, "tree:%d %s list%d %s\n",tree->right->attribute.sval->type,tree->attribute.sval->name,temp->type,temp->name);
			if(check_type(tree)!=temp->type) return -1;
		}else{
			//fprintf(stderr, "tree:%d %s list%d %s\n",tree->attribute.sval->type,tree->attribute.sval->name,temp->type,temp->name);
			if(check_type(tree->right)!=temp->type) return -1;
		}*/
		if(check_type(tree->right)!=temp->type) return -1;
	}
	return 0;
}

void check_array(tree_t *expression){
	
}

void check_return(tree_t *expression){
	/*tree_t *temp=NULL;
	if(expression==NULL){
		fprintf(stderr, "Functions need a return statement\n");
		exit(1);
	}else{
		for(temp=expression;expression)
	}*/
}

void check_procedure(tree_t *procedure,char *name,char *scope){
	list_t *functionArgs;
	tree_t *expressionTypes;
	node_t *funcID;
	int length=0;
	assert(procedure!=NULL);
	funcID=procedure->left->attribute.sval;
	assert(funcID!=NULL&&funcID->mark==PROCEDURE);
	functionArgs=funcID->args;

	if(procedure->right==NULL){
		fprintf(error, "Procdures needs parameters\n");
	}else{
		//assert(procedure->right!=NULL);
		expressionTypes=procedure->right;
		//assert(expressionTypes!=NULL);
		length=lengthArg(expressionTypes);
		//fprintf(stderr, "Number of Arguments: %d %d\n",num_list(functionArgs),length);
		if(num_list(functionArgs)!=length){
			fprintf(error, "In Procdure %s Wrong Number of Arguments %d in Scope %s on line: %d\n",name,length,scope,line_number);
			//exit(1);
		}

		if(equalArgs(functionArgs,expressionTypes)==-1){
			fprintf(error, "In Procdure %s Wrong Arguments Types in Scope %s on line: %d\n",name,scope,line_number);
			//exit(1);
		}
	}
}

void check_function(tree_t *function,char *name,char *scope){
	list_t *functionArgs;
	tree_t *expressionTypes;
	node_t *funcID;
	int length=0;
	assert(function!=NULL);
	funcID=function->left->attribute.sval;
	assert(funcID!=NULL&&funcID->mark==FUNCTION);
	functionArgs=funcID->args;

	//assert(function->right!=NULL);
	if(function->right==NULL){
		fprintf(error, "Functions needs parameters\n");
	}else{
		expressionTypes=function->right;
		//assert(expressionTypes!=NULL);
		length=lengthArg(expressionTypes);
		//fprintf(stderr, "Number of Arguments: %d %d\n",num_list(functionArgs),length);
		if(num_list(functionArgs)!=length){
			fprintf(error, "In Function Call %s Wrong Number of Arguments %d in Scope %s on line: %d\n",name,length,scope,line_number);
			//exit(1);
		}

		if(equalArgs(functionArgs,expressionTypes)==-1){
			fprintf(error, "In Function Call %s Wrong Arguments Types in Scope %s on line: %d\n",name,scope,line_number);
			//exit(1);
		}
	}
}