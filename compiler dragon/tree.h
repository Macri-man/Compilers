#ifndef TREE_H
#define TREE_H 

typedef struct tree_s {
	int type; 		/* NUMBER, ADDOP, MULOP ... */
	union {
		int ival;  /* INUM */
		float rval;  /* RNUM */
		int opval;	/* ADDOP, MULOP  */
		node_t *sval;	/* ID */
	} attribute;
	struct tree_s *left;
	struct tree_s *right;
} tree_t;


/* contructor */
tree_t *make_tree(int type, tree_t *left, tree_t *right);
tree_t *make_op(int type, int attribute, tree_t *left, tree_t *right);
tree_t *make_id(node_t *node);
tree_t *make_inum(int val);
tree_t *make_rnum(float val);


void print_tree(tree_t *t, int spaces); 
void print_ADDOP(int opval);
void print_RELOP(int opval);
void print_MULOP(int opval);

#endif