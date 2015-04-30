#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "scope.h"
#include "gencode.h"
#include "y.tab.h"

extern FILE *assemble;
extern scope_t *top_scope;
extern int depth;

char registers[][5] ={
	"%r8",
	"%r9",
	"%r10",
	"%r11",
	"%r12",
	"%r13",
	"%r14",
	"%r15",
};

typedef struct reg_s {
	int index;
	struct reg_s * nextreg;
}reg_t;

typedef struct{
	reg_t *topstack;
} regstack_t;

regstack_t regstack;
int jumpnum=0;

void init_register(){
	reg_t *nextreg;
	int i;
	regstack.topstack = NULL;
	for (i = 7; i >= 0; --i) {
		nextreg = regstack.topstack;
		regstack.topstack = malloc(sizeof(reg_t));
		regstack.topstack->index = i;
		regstack.topstack->nextreg = nextreg;
	}
}

void dealloc_register(){
	reg_t *nextreg, *temp;
	for (nextreg = regstack.topstack; nextreg != NULL;) {
		temp = nextreg;
		nextreg = nextreg->nextreg;
		free(temp);
	}
}

reg_t *pop_register(){
	reg_t * temp;
	temp = regstack.topstack;
	regstack.topstack = regstack.topstack->nextreg;
	return temp;
}

void push_register(reg_t *nextreg){
	reg_t *temp;
	temp = regstack.topstack;
	regstack.topstack = nextreg;
	nextreg->nextreg = temp;
}

void swap_registers(){
	reg_t *temp;
	temp = regstack.topstack->nextreg;
	regstack.topstack->nextreg = temp->nextreg;
	temp->nextreg = regstack.topstack;
	regstack.topstack = temp;
}

void rankify(tree_t *tree){
	assert(tree);
	if(!(tree->left || tree->right)) return ;

	if(tree->left && !tree->left->left && !tree->left->right){
		tree->left->rank = 1;
		printf("%d = %d\n", tree->left->type, tree->left->rank);
	}

	if(tree->right && !tree->right->left && !tree->right->right){
		tree->right->rank = 0;
		printf("%d = %d\n", tree->right->type, tree->right->rank);
	}

	rankify(tree->left);
	rankify(tree->right);

	if(tree->left->rank == tree->right->rank) {
		tree->rank = tree->left->rank + 1;
		printf("%d = %d\n", tree->type, tree->rank);
	}else{
		tree->rank = (tree->left->rank < tree->right->rank)? tree->right->rank : tree->left->rank;
		printf("%d = %d\n", tree->type, tree->rank);
	}

	return ;
}

void genmainlabel(){
	assemble(".LC0:\n");
	assemble("\t.string \"%%ld\\n\"\n");
	assemble(".LC1:\n");
	assemble("\t.string \"%%ld\"\n");
	assemble("\t.globl main\n");

	//return 0;
}

void genmain(char *name){
	assemble("main:\n");
	assemble("\tpushq\t%%rbp\n");
	assemble("\tmovq\t%%rsp, %%rbp\n");
	assemble("\tcall\t%s\n", name);
	genleave();

	//return 0;
}

void genstack(char *name){
	assemble("%s:\n", name);
	assemble("\tpushq\t%%rbp\n");
	assemble("\tmovq\t%%rsp, %%rbp\n");

	//return 0;
}

void genleave(){
	assemble("\tleave\n");
	assemble("\tret\n");

	//return 0;
}

void genallocstack(int offset){
	if(!offset) return ;
	assemble("\tsubq\t$%d, %%rsp\n", -offset);
	//return 0;
}

void gendeallocstack(int offset){
	if(!offset) return ;
	assemble("\taddq\t$%d, %%rsp\n", -offset);
	//return 0;
}

void jmp(char *jmp,int offset){
	char foo[10] = {0};

	sprintf(foo, ".LL%d", jumpnum+offset);
	assemble("\t%s\t%s\n",jmp,foo);

	//return 0;
}

void genlabel(){
	assemble(".LL%d:\n",jumpnum++);
	//return 0;
}

void genjmp(tree_t *tree,int offset){

	switch(tree->attribute.opval) {
		case EQ: jmp("je ", offset); break;
		case NEQ: jmp("jne", offset); break;
		case LT: jmp("jl ", offset); break;
		case LE: jmp("jle", offset); break;
		case GT: jmp("jg ", offset); break;
		case GE: jmp("jge", offset); break;
		default: fprintf(stderr, "Jump Name not found\n"); break;
	}
	//return 0;
}

void genid(char *format, tree_t *tree, char *op){
	int i;
	char foo[16] = {0};

	if (tree->type == INUM) {
		sprintf(foo, "$%d", tree->attribute.ival);
		assemble(format, foo, op);
		return;
	}

	scope_search_all(top_scope, tree->attribute.sval->name,&depth);
	if (tree->attribute.sval->depth != 0) {
		assemble("\tmovq\t(%%rbp), %%rcx\n");
		for (i = tree->attribute.sval->depth - 1; i != 0; i--) {
			assemble("\tmovq\t(%%rcx), %%rcx\n");
		}
		sprintf(foo,"%d(%%rcx)", tree->attribute.sval->offset);
		assemble(format, foo, op);
	}
	else {
		sprintf(foo,"%d(%%rbp)", tree->attribute.sval->offset);
		assemble(format, foo, op);
	}
}

void genwrite(char *name, tree_t *tree){
	if(tree==NULL || strcmp("write", name)!=0) return ;

	if(tree->type != EXPRLIST) {
		assemble("\tmovq\t$0, %%rax\n");
		if(tree->type == INUM){
			assemble("\tmovq\t$%d, %%rsi\n", tree->attribute.ival);
		}else{
			assemble("\tmovq\t%d(%%rbp), %%rsi\n", tree->attribute.sval->offset);
		}
		assemble("\tmovq\t$.LC0, %%rdi\n");
		assemble("\tcall\tprintf\n");
		return ;
	}

	assemble("\tmovq\t$0, %%rax\n");
	if (tree->right->type == INUM){
		assemble("\tmovq\t$%d, %%rsi\n", tree->right->attribute.ival);
	}else {
		genid("\tmovq\t%s, %%rsi\n", tree->right, NULL);
	}
	assemble("\tmovq\t$.LC0, %%rdi\n");
	assemble("\tcall\tprintf\n");
	genwrite("write", tree->left);

	return ;
}

void genread(char *name, tree_t *tree){
	if(tree==NULL || strcmp("read", name)) return ;

	genid("\tleaq\t%s, %%rsi\n", tree->right, NULL);
	assemble("\tmovq\t$.LC1, %%rdi\n");
	assemble("\tmovq\t$0, %%rax\n");
	assemble("\tcall\tscanf\n");

	// TODO

	return ;
}

void genaddop(tree_t *tree, reg_t *left, reg_t *right){
	if (left == NULL){
		if(tree->attribute.opval == PLUS){
			genid("\taddq\t%s,%s\n",tree->right, registers[right->index]);
			return ;
			if(tree->right->type == INUM){
				assemble("\taddq\t$%d, %s\n", tree->right->attribute.ival, registers[right->index]);
			}else{
				genid("\taddq\t%s, %s\n", tree->right, registers[right->index]);
			}
		}
		else if(tree->attribute.opval == MINUS){
			if(tree->right->type == INUM){
				assemble("\tsubq\t$%d, %s\n", tree->right->attribute.ival, registers[right->index]);
			}else{
				genid("\tsubq\t$%d, %s\n", tree->right, registers[right->index]);
			}
		}
		return ;
	}
	assert(right);
	assemble("\taddq\t%s, %s\n", registers[left->index], registers[right->index]);

}

void genmulop(tree_t * tree, reg_t *left, reg_t *right){
	if(left == NULL) {
		assemble("\timulq\t$%d, %s\n", tree->right->attribute.ival, registers[right->index]);
	}else{
		assert(right);
		assemble("\timulq\t%s, %s\n", registers[left->index], registers[right->index]);
	}	
}

void genop(tree_t *tree, reg_t *left, reg_t *right){
	switch(tree->type){
		case ADDOP: genaddop(tree,left,right); break;
		case MULOP: genmulop(tree,left,right); break;
		default: fprintf(stderr, "NO OP FOUND\n"); break;
	}
}


void genrelop(tree_t *tree, char *reg){
	if (tree->type == ID) {
		genid("\tmovq\t%s, %s\n", tree, reg);
	}
	else if (tree->type == INUM) {
		assemble("\tmovq\t$%d, %s\n", tree->attribute.ival, reg);
	}
	else {
		init_register();
		rankify(tree);
		gencode(tree);
		if (strcmp(reg, "%r10"))
			assemble("\tmovq\t%%r10, %s\n", reg);
		dealloc_register();
	}
}

void genIfThenElse(tree_t *tree){
	gencode(tree->left);
	genjmp(tree->left, 0);
	jmp("jmp", 1);
	genlabel();
	jmp("jmp",1); 
	genlabel();
	genlabel();
}

void genWhileDo(tree_t *tree){
	jmp("jmp",1);
	genlabel();
	genlabel();
	gencode(tree->left); 
	genjmp(tree->left, -2);
}

void genIfThen(tree_t *tree){
	gencode(tree->right->left);
	genjmp(tree->right->left, 0);
}


void gencode(tree_t *tree){
	reg_t *right;

	if(tree->left==NULL && tree->rank == 0) {
		fprintf(stderr, "INVALID RANK\n");
		return ;
	}

	if (tree->type == INUM) {
		assemble("\tmovq\t$%d,%s\n",tree->attribute.ival,registers[regstack.topstack->index]);
		return ;
	}

	/*if (t->type == RNUM) {
		assemble("\tmovq\t$%d,%s\n",t->attribute.rval,registers[st.top->index]);
		return 0;
	}*/
	if(!tree->left && !tree->right && (tree->rank == 1)){
		// MOV to top
		printf("case 0\n");
		printf("MOV %d, %s\n", tree->attribute.ival, registers[regstack.topstack->index]);
		genid("\tmovq\t%s, %s\n", tree, registers[regstack.topstack->index]);
	}else if(tree->right && (tree->right->rank == 0)){
		printf("case 1\n");
		gencode(tree->left);
		genop(tree, NULL, regstack.topstack);
		printf("OP %d, %s\n", tree->right->attribute.ival, registers[regstack.topstack->index]);
	}else if(tree->left && tree->right && (tree->left->rank < tree->right->rank) && (tree->left->rank >= 1)){
		printf("case 2\n");
		swap_registers();
		gencode(tree->right);
		right = pop_register();
		gencode(tree->left);
		printf("OP %s, %s\n", registers[right->index], registers[regstack.topstack->index]);
		genop(tree, right, regstack.topstack);
		push_register(right);
		swap_registers();
	}else if(tree->left && tree->right && (tree->left->rank >= tree->right->rank) && (tree->right->rank >= 1)){
		printf("case 3\n");
		gencode(tree->left);
		right = pop_register();
		gencode(tree->right);
		printf("OP %s, %s\n", registers[regstack.topstack->index], registers[right->index]);
		genop(tree, regstack.topstack, right);
		push_register(right);
	}else{
		fprintf(stderr, "NO Case 4\n"); 
		assert(0);
	}
}


void genstatements(tree_t *tree){
	if(tree==NULL) return ;
	//tree_print(t);

	printf("\nCreation of Assembly\n");

	if (tree->type == ASSIGNOP) {
		if (tree->right->type == INUM) {
			assemble("\tmovq\t$%d, %d(%%rbp)\n", tree->right->attribute.ival, tree->left->attribute.sval->offset);
			return ;
		}else if(tree->right->type == ID){
			assemble("\tmovq\t%d(%%rbp), %%rdx\n", tree->right->attribute.sval->offset);
			assemble("\tmovq\t%%rdx, %d(%%rbp)\n", tree->left->attribute.sval->offset);
			return ;
		}
		rankify(tree->right);
		fprintf(stderr, "ASNOP to a %d\n", tree->right->attribute.opval);
		init_register();
		rankify(tree->right);
		gencode(tree->right);
		assemble("\tmovq\t%s, %d(%%rbp)\n", registers[regstack.topstack->index], tree->left->attribute.sval->offset);
		dealloc_register();
	}else if(tree->type == PROCEDURE){
		genstatements(tree->right);
		assemble("\tcall\t%s\n", tree->left->attribute.sval->name);
		assemble("\taddq\t$%d, %%rsp\n", num_list(tree->left->attribute.sval->args)*8);

	}else if(tree->type == EXPRLIST) {
		genrelop(tree->right, "%r10");
		assemble("\tpushq\t%%r10\n");
		genstatements(tree->left);
	}else if(tree->type == RELOP) {
		genrelop(tree->left, "%rdx");
		genrelop(tree->right, "%rbx");
		assemble("\tcmpq\t%%rbx, %%rdx\n");

	}else{
		assert(0);
	}
}

