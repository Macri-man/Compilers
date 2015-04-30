#ifndef SEMANTIC_H
#define SEMANTIC_H 

#include "scope.h"
extern FILE * error;

void check_function(tree_t *function,char *name,char *scope);
void check_procedure(tree_t *procedure,char *name,char *scope);
void check_array(tree_t *array);

int lengthArg(tree_t *args);
int equalArgs(list_t *args1,tree_t *args2);

int type(tree_t *expression);

int check_type(tree_t *expression);
int findtype(tree_t *expression,int type);
void check_duplicate(list_t *list,struct scope_s *scope);

void check_array(tree_t *expression);
void check_return(tree_t *expression);

#endif