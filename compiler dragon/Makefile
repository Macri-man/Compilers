dragon: y.tab.o lex.yy.o tree.o scope.o node.o list.o semantic.o gencode.o
	gcc -g -o dragon tree.o scope.o node.o list.o semantic.o gencode.o y.tab.o lex.yy.o  
gencode.o: gencode.c 
	gcc -g -c gencode.c
semantic.o: semantic.c
	gcc -g -c semantic.c
tree.o: tree.c
	gcc -g -c tree.c
scope.o: scope.c
	gcc -g -c scope.c
node.o: node.c
	gcc -g -c node.c
list.o: list.c
	gcc -g -c list.c
y.tab.o: y.tab.c
	gcc -g -c y.tab.c
y.tab.c: dragon.y
	bison -y -dv dragon.y 
lex.yy.o: lex.yy.c
	gcc -g -c lex.yy.c
lex.yy.c: dragon.l
	lex -l dragon.l
clean:
	rm -f y.tab.* lex.yy.* dragon *.o *.s *.txt *.out
