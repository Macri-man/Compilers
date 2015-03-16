#ifndef TREE_H
#define TREE_H 

typedef struct tree_s {
	int type; 		/* NUMBER, ADDOP, MULOP ... */
	union {
		int ival;  /* INUM */
		float rval;  /* RNUM */
		int opval;	/* ADDOP, MULOP  */
		node_t *sval;	/* ID */
		list_ *lval;
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

tree_t *make_program(int type,tree_t *id,tree_t *idlist,tree_t *decl,tree_t *subprogdecl,tree_t *compstm);
tree_t *make_decl(int type,tree_t *decl,tree_t *idlist,tree_t *type);
tree_t *make_array(int type,tree_t *arr,tree_t *firstnum,tree_t *lastnum,tree_t *stdtype);
tree_t *make_subdecl(int type,tree_t *subproghead,tree_t *decl,tree_t *compstm);
tree_t *make_function(int type,tree_t *id,tree_t *arguments,tree_t *stdtype);
tree_t *make_procedure(int type,tree_t *id,tree_t *arguments);
tree_t *make_parlist(int type,tree_t *parlist,tree_t *idlist,tree_t *type);
tree_t *make_cond(int type,tree_t *expr,tree_t *stm,tree_t *stm);
tree_t *make_whdo(int type,tree_t *expr,tree_t *stm);



void print_tree(tree_t *t, int spaces); 
void print_ADDOP(int opval);
void print_MULOP(int opval);
void print_RELOP(int opval);

#endif