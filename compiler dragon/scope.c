#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "scope.h"

/*constructor */
scope_t *make_scope(char *name){
	int i;
	scope_t *p=(scope_t *)malloc(sizeof(scope_t));
	for(i=0;i<HASH_SIZE;i++){
		p->table[i]=NULL;
	}
	p->name=strdup(name);
	p->next=NULL;
	return p;
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
node_t *scope_insert(scope_t *scope,char *name){
	
	int index;
	node_t *head;

	if(scope!=NULL){
		hash_pjw(name);
		head=scope->table[index];
		return scope->table[index]=node_insert(head,name);
	}else return NULL;
}

/* gloabl search */
node_t *scope_search_all(scope_t *curr_scope,char *name){

	node_t *p;
	for(curr_scope;curr_scope!=NULL;curr_scope=curr_scope->next){
		p=scope_search(curr_scope,name);
		if(p!=NULL) return p;
	}
	return NULL;
}

/* push new one */
scope_t *scope_push(scope_t *top, char *name){
	scope_t *new_scope=make_scope(name);
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