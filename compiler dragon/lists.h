#ifndef LISTS_H
#define LISTS_H

typedef struct list_s{
	char *name;
	int type;
	int mark;	
	node_t *node;

	struct list_s *next;
}list_t;

list_t *make_list(node_t *node,char *name,int type);
list_t *list_append(list_t *head,node_t *list);
list_t *make_parlist(list_t *head,list_t *idlist,int mark);
list_t *parlist_append(list_t *head,$3,$5,int mark);
void list_print(list_t *head);


#endif