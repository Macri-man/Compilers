#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

node_t *make_node(char *name){
	node_t *node=(node_t*)calloc(1,sizeof(node_t));
	node->name=strdup(name);
	return node;
}

node_t *node_search(node_t *head,char *name){
	node_t *node=NULL;
	for(node=head;node!=NULL;node=node->next){
		if(!strcmp(node->name,name))return node;
	}
	return NULL;
}

node_t *node_insert(node_t *head,char *name,int offset){
	node_t *node=make_node(name);
	node->offset=offset;
	node->next=head;
	return node;
}

void print_nodes(list_t *head){
	list_t *temp=NULL;
	node_t *node=NULL;
	for(temp=head;temp->next!=NULL;temp=temp->next);
	for(node=temp->node;node!=NULL;node=node->next){
		fprintf(stderr, "\nNODES:%s",node->name);
	}
}
