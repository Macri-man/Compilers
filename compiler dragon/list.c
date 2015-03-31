#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *make_list_node(node_t *node,char *name,int type){
	list_t *p=(list_t*)malloc(sizeof(list_t));
	p->attribute.node=node;
	p->name=name;
	p->type=type;
	p->next=NULL;
	return p;
}

list_t *make_list_tree(tree_t *tree,char *name,int type){
	list_t *p=(list_t*)malloc(sizeof(list_t));
	p->attribute.tree=tree;
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

list_t *list_append_node(list_t *head,node_t *node){
	list_t *p=make_list_node(node,node->name,node->type);
	p->next=head;
	return p;
}

list_t *list_append_tree(list_t *head,tree_t *tree){
	list_t *p=make_list_tree(tree,tree->name,tree->type);
	p->next=head;
	return p;
}

int num_list(list_t *head){
	int num=0;
	list_t *temp=NULL;
	for(temp=head;temp!=NULL;temp=temp->next){
		num++;
	}
	return num;
}