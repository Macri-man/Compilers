dragon: y.tab.o lex.yy.o tree.o scope.o node.o list.o semantic.o gencode.o
	clang -g -o dragon tree.o scope.o node.o list.o semantic.o y.tab.o lex.yy.o  -ll -ly
gencode.o: gencode.c
	clang -g -c gencode.c
semantic.o: semantic.c
	clang -g -c semantic.c
tree.o: tree.c
	clang -g -c tree.c
scope.o: scope.c
	clang -g -c scope.c
node.o: node.c
	clang -g -c node.c
list.o: list.c
	clang -g -c list.c
y.tab.o: y.tab.c
	clang -g -c y.tab.c
y.tab.c: dragon.y
	yacc -dv dragon.y 
lex.yy.o: lex.yy.c
	clang -g -c lex.yy.c
lex.yy.c: dragon.l
	lex -l dragon.l
clean:
	rm -f y.tab.* lex.yy.* dragon *.o *.s *.txt *.out
