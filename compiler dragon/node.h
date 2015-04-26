#ifndef NODE_H
#define NODE_H

#include "list.h"

typedef struct node_s{
	char *name;
	int type;
	int mark;

	union{
		int numargs;
		int range[2];
	}semantics;

	int offset;
	struct list_s *args;
	struct node_s *next;
}node_t;

node_t *make_node(char *name);

node_t *node_search(node_t *,char *);
node_t *node_insert(node_t *,char *);

void print_nodes(struct list_s *head);

#endif