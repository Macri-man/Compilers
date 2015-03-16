#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *make_list(tree_t *tree,char *name,int type){
	list_t *p=(list_t*)malloc(sizeof(list_t));
	p->tree=tree;
	p->name=name;
	p->type=type;
	return p;
}

void list_print(list_t *head){
	list_t *p=NULL;
	for(p=head;p!=NULL;p=p->next){
		print_tree(p,0);
		fprintf(stderr, "\n\n\n");
	}
}

list_t *list_insert(list_t *head,tree_t *tree){
	list_t *p=make_list(tree_t *tree);
	p->next=head;
	return p;
}