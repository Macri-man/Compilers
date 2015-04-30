#ifndef TREE_H
#define TREE_H 

#include "list.h"

typedef struct tree_s{
	int type; 		/* NUMBER, ADDOP, MULOP ... */
	union {
		int ival;  /* INUM */
		float rval;  /* RNUM */
		int opval;	/* ADDOP, MULOP  */
		struct node_s *sval;	/* ID */
		struct list_s *lval;
	} attribute;
	int rank;
	int scope_depth;
	struct tree_s *left;
	struct tree_s *right;
}tree_t;

/* contructor */
tree_t *make_tree(int type, tree_t *left, tree_t *right);
tree_t *make_op(int type, int attribute, tree_t *left, tree_t *right);
tree_t *make_id(struct node_s *node);
tree_t *make_inum(int val);
tree_t *make_rnum(float val);
/*
tree_t *make_program(int type,tree_t *id,tree_t *idlist,tree_t *decl,tree_t *subprogdecl,tree_t *compstm);
tree_t *make_decl(int type,tree_t *decl,tree_t *idlist,tree_t *ttype,int mark);
tree_t *make_array(int type,tree_t *arr,tree_t *firstnum,tree_t *lastnum,tree_t *stdtype);
tree_t *make_subdecl(int type,tree_t *subproghead,tree_t *decl,tree_t *compstm);
tree_t *make_function(int type,tree_t *id,tree_t *arguments,tree_t *stdtype);
tree_t *make_procedure(int type,tree_t *id,tree_t *arguments);
tree_t *make_cond(int type,tree_t *expr,tree_t *stm1,tree_t *stm2);
tree_t *make_whdo(int type,tree_t *expr,tree_t *stm);

tree_t *make_statmnt(int type,tree_t *statement);
tree_t *list_append_statmnt(int type,tree_t *statementlist,tree_t *statement);
tree_t *make_exprlist(int type,tree_t *expr);
tree_t *list_append_exprlist(int type,tree_t *exprlist,tree_t *expr);
tree_t *make_parlist(int type,tree_t *idlist,tree_t *ttype,int mark);
tree_t *parlist_list(int type,tree_t *parlist,tree_t *idlist,tree_t *ttype,int mark); 
*/

tree_t *make_treeFromList(int type,struct list_s *ls);
tree_t *make_idlist(int type,struct list_s *idlist);


void free_tree(tree_t *tree);

void list_print(struct list_s *l);
void id_list(struct list_s *head);
void print_type(int type);


void assign_mark(struct list_s *l,int mark);
void assign_type(struct list_s *l,tree_t *ttype);
void assign_range(struct list_s *l,int ivalfirst,int ivallast);

void print_mark(int mark);
void print_id(char *name);
void print_opval(int opval); 

void print_tree(tree_t *t, int spaces);
void print_ADDOP(int opval);
void print_MULOP(int opval);
void print_RELOP(int opval);

#endif