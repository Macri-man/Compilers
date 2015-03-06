compiler: y.tab.o lex.yy.o
	clang -g -o compiler y.tab.o lex.yy.o -ll -ly
y.tab.o: y.tab.c 
	clang -g -c y.tab.c
y.tab.c: compiler.y
	yacc -dv compiler.y 
lex.yy.o: lex.yy.c 
	clang -g -c lex.yy.c
lex.yy.c: compiler.l
	lex -l compiler.l
clean:
	rm -f y.tab.* lex.yy.* compiler *.o