all:
	mkdir -p bin/
	yacc --defines=src/y.tab.h -o src/y.tab.c src/automation-for-humans.yacc
	lex -o src/lex.yy.c src/automation-for-humans.lex
	gcc -Iinclude/ src/y.tab.c src/lex.yy.c -ll -o bin/afh-parser
validate:
	bin/afh-parser $(src)
clean:
	rm -rf src/lex.yy.c
	rm -rf src/y.tab.c
	rm -rf src/y.tab.h
	rm -rf bin/
