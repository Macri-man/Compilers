#ifndef SEMANTIC_H
#define SEMANTIC_H 

void check_function(tree_t *function,int type);
void check_procedure(tree_t *procedure,int type);
void check_array(tree_t *array);

int lengthArg(list_t *args);
int equalArgs(tree_t *args1,tree_t *args2);

int type(tree_t *expression);

int check_type(tree_t *expression);
int findtype(tree_t *expression,int type);

#endif