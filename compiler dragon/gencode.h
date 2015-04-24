#include "tree.h"

#define assemble(...) fprintf(gen_code, __VA_ARGS__)

int gencode(tree_t * t);
int gen_preamble(void);
int gen_postamble(char * name);
int gen_intro(char * name);
int gen_outro(void);
int gen_stalloc(int off);
int gen_dealloc(int off);
int gen_write(char * name, tree_t * t);
int gen_read(char * name, tree_t * t);