#ifndef LISTS_H
#define LISTS_H

typedef struct list_s{
	char *name;
	int type;
	int mark;
	union{	
		node_t *node;
		tree_t *tree;
	}attribute

	struct list_s *next;
}list_t;

list_t *make_list_node(node_t *node,char *name,int type);
list_t *make_list_tree(tree_t *tree,char *name,int type);
list_t *list_append_node(list_t *head,node_t *node);
list_t *list_append_tree(list_t *head,tree_t *tree);
void list_print(list_t *head);
int num_list(list_t *head);


#endif