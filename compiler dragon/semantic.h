#ifndef TREE_H
#define TREE_H 

void check_function(tree_t *function,int type);
void check_procedure(tree_t *procedure,int type);
void check_array(tree_t *array,int type);

int lengthArg(list_t *args);
int equalArgs(node_t *args1,node_t *args2);

int type(tree_t *expression);

#endif