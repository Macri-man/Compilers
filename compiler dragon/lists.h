#ifndef LISTS_H
#define LISTS_H

typedef struct list_s{
	char *name;
	int type;	
	tree_t *statement;

	struct list_s *next;
}list_t;

list_t *make_list(tree_t *tree,char *name,int type);

//node_t *list_search(node_t *,tree_t *tree);
list_t *list_insert(list_t *,tree_t *tree);


#endif