#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

list_t *make_list_node(node_t *node,char *name,int type){
	assert(node!=NULL);
	list_t *p=(list_t*)malloc(sizeof(list_t));
	p->node=node;
	//p->name=strdup(name);
	//p->type=type;
	p->next=NULL;
	return p;
}

list_t *make_list(list_t *list){
	assert(list!=NULL);
	list_t *p=(list_t*)malloc(sizeof(list_t));
	p=list;
	return p;
}

list_t *list_append(list_t *head,list_t *list){
	assert(list!=NULL);
	list_t *temp=NULL;
	if(head==NULL){
		head=list;
	}else{
		assert(head!=NULL && list!=NULL);
		for(temp=head;temp->next!=NULL;temp=temp->next);
		temp->next=list;
		list->node->next=temp->node;
	}
	assert(head !=NULL);
	return head;
}

list_t *list_append_node(list_t *list,node_t *node){
	assert(list!=NULL && node!=NULL);
	list_t *ls=make_list_node(node,node->name,node->type);
	list_t *temp=NULL;
	for(temp=list;temp->next!=NULL;temp=temp->next);
	temp->next=ls;
	return list;
}

void offset(list_t *head,int sign){
	int num=0;
	list_t *temp;
	for(temp=head;temp->next!=NULL;temp=temp->next){
		if(sign==0){
			num+=8;
		}else{
			num-=8;
		}
	}
}

void print_list(list_t *list){
	list_t *temp;
	if(list==NULL) return;
	if(list->node==NULL) return;
	for(temp=list;temp!=NULL;temp=temp->next){
		fprintf(stderr, "%s",temp->node->name);
	}
}

int num_list(list_t *head){
	assert(head!=NULL);
	int num=0;
	list_t *temp=NULL;
	for(temp=head;temp!=NULL;temp=temp->next){
		num++;
	}
	return num;
}