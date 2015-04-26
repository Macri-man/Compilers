#ifndef SEMANTIC_H
#define SEMANTIC_H 

void check_function(tree_t *function);
void check_procedure(tree_t *procedure);
void check_array(tree_t *array);

int lengthArg(tree_t *args);
int equalArgs(list_t *args1,tree_t *args2);

int type(tree_t *expression);

int check_type(tree_t *expression);
int findtype(tree_t *expression,int type);
void check_duplicate(list_t *list);

void check_array(tree_t *expression);

list_t *exprlist(tree_t *t);

#endif