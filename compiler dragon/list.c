#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *make_list(node_t *node,char *name,int type){
	list_t *p=(list_t*)malloc(sizeof(list_t));
	p->head=node;
	p->name=name;
	p->type=type;
	p->next=NULL;
	return p;
}

void list_print(list_t *head){
	list_t *p=NULL;
	for(p=head;p!=NULL;p=p->next){
		print_tree(p,0);
		fprintf(stderr, "\n\n\n");
	}
}

list_t *list_append(list_t *head,node_t *node){
	list_t *p=make_list(node,node->name,node->type);
	p->next=head;
	return p;
}