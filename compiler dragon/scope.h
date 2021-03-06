#ifndef SCOPE_H
#define SCOPE_H

#include "node.h"
#define HASH_SIZE 211
#define EOS 	'\0'

typedef struct scope_s{
	/* hash table: hashing with chaining */
	node_t *table[HASH_SIZE];
	char *name;
	int type;
	int argoffset;
	int localoffset;
	struct scope_s *next;
}scope_t;

scope_t *make_scope(char *name,int type);

/* basic search and insert */
node_t *scope_search(scope_t *head,char *name);
node_t *scope_insert(scope_t *head,char *name,int argorlocal);

node_t *scope_search_all(scope_t *head,char *name,int *depth);

void print_scope(scope_t *top);
void free_scope(scope_t *scope);
void free_scope_nodes(node_t *node);

/* symbol table = stack of hash tables; stack routins */
scope_t *scope_push(scope_t *top,char *name,int type);
scope_t *scope_pop(scope_t *top);

int hash_pjw(char *s);

#endif