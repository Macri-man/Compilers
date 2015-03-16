#ifndef LISTS_H
#define LISTS_H

typedef struct list_s{
	char *name;
	int type;	
	tree_t *root;

	struct list_s *next;
}list_t;

list_t *make_list(,int type,tree_t *tree);
list_t *list_insert(list_t *head,tree_t *tree);
void list_print(list_t *head);

#endif