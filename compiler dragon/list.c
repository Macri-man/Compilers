#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list_t *make_list(tree_t *tree){
	list_t *p=(list_t*)malloc(sizeof(list_t));
	p->tree=tree;
	return p;
}
/*
list_t *node_search(list_t *head,tree_t *tree){
	list_t *p=NULL;
	for(p=head;p!=NULL;p=p->next){
		if(!strcmp(p->name,name))return p;
	}
	return NULL;
}*/

list_t *node_insert(list_t *head,tree_t *tree){
	list_t *p=make_list(tree_t *tree);
	p->next=head;
	return p;
}