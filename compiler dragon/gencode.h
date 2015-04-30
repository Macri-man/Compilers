#include "tree.h"

#define assemble(...) fprintf(assemble, __VA_ARGS__)

void genmainlabel();
void genmain(char *name);
void genstack(char *name);
void genleave();
void genallocstack(int offset);
void gendeallocstack(int offset);
void jmp(char *jmp,int offset);
void genlabel();
void genjmp(tree_t *tree,int offset);
void genrelop(tree_t *tree, char *reg);
void genwrite(char *name, tree_t *tree);
void genread(char *name, tree_t *tree);
void gencode(tree_t *tree);
void genstatements(tree_t *tree);
void genWhileDo(tree_t *tree);
void genIfThen(tree_t *tree);
void genIfThenElse(tree_t *tree);