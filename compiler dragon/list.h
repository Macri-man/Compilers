#ifndef LIST_H
#define LIST_H

#include "tree.h"
#include "node.h"

typedef struct list_s{
	char *name;
	int type;
	int mark;
	struct node_s *node;

	struct list_s *next;
}list_t;

list_t *make_list_node(struct node_s *node,char *name,int type);
list_t *make_list_tree(struct tree_s *tree,char *name,int type);
list_t *make_list(list_t *list);
list_t *list_append(list_t *head,list_t *list);
list_t *list_append_node(list_t *head,struct node_s *node);
list_t *list_append_tree(list_t *head,struct tree_s *tree);
void list_print(list_t *head);
int num_list(list_t *head);

#endif