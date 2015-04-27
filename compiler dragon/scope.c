#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scope.h"

/*constructor */
scope_t *make_scope(char *name,int type){
	int i;
	scope_t *scope=(scope_t *)malloc(sizeof(scope_t));
	for(i=0;i<HASH_SIZE;i++){
		scope->table[i]=NULL;
	}
	scope->name=strdup(name);
	scope->type=type,
	scope->argoffset=8;
	scope->next=NULL;
	return scope;
}

/* local search */
node_t *scope_search(scope_t *scope,char *name){
	
	int index;
	node_t *head;

	if(scope!=NULL){
		index=hash_pjw(name);
		head=scope->table[index];
		return node_search(head,name);
	}else return NULL;
}

/* local insert */
node_t *scope_insert(scope_t *scope,char *name,int argorlocal){
	
	int index;
	node_t *head;
	int offset;

	if(scope!=NULL){
		index=hash_pjw(name);
		head=scope->table[index];
		switch(argorlocal) {
			case -1: 
				offset = scope->localoffset -= 8; 	
				break;
			case 0 : 
				offset = 0;                 		
				break;
			case 1 : 
				offset = scope->argoffset += 8;		
				break;
		}
		return scope->table[index]=node_insert(head,name,offset);
	}else return NULL;
}

/* gloabl search */
node_t *scope_search_all(scope_t *scope,char *name,int *depth){

	node_t *node;
	for(scope;scope!=NULL;scope=scope->next){
		node=scope_search(scope,name);
		//(*depth)++;
		if(node!=NULL){
			node->depth=(*depth);
			(*depth)=0;
			return node;
		}
		(*depth)++;
	}
	(*depth)=0;
	return NULL;
}

/* push new one */
scope_t *scope_push(scope_t *top, char *name,int type){
	scope_t *new_scope=make_scope(name,type);
	assert(new_scope!=NULL);
	new_scope->next=top;
	return new_scope;
}

/* pop top scope */
scope_t *scope_pop(scope_t *top){
	scope_t *tmp=top;
	if(top!=NULL){
		tmp=top;
		top=top->next;

		//free_scope(tmp);

		return top;
	}else return NULL;
}

void print_scope(scope_t *top){
	scope_t *temp=NULL;
	int num=0;
	for(temp=top;temp!=NULL;temp=temp->next){
		fprintf(stderr, "%s\n",temp->name);
	}
	for(temp=top;temp!=NULL;temp=temp->next){
		num++;
	}
	fprintf(stderr, "Number of Scopes: %d\n",num);
}

/* hash function (Weinberger's hash)*/
/* page 430 Dragon 1 */
int hash_pjw(char *s){
	char *p;
	unsigned h=0,g;

	for(p=s;*p!=EOS;p++){
		h=(h<<4)+(*p);
		if(g=(h&0xf0000000)){
			h=h^(g>>24);
			h=h^g;
		}
	}
	return h%HASH_SIZE;
}