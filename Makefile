all:
	mkdir -p bin/
	yacc --defines=src/y.tab.h -o src/y.tab.cpp src/automation-for-humans.yacc
	lex -o src/lex.yy.cpp src/automation-for-humans.lex
	g++ -w -std=c++11 -Iinclude/ src/y.tab.cpp src/lex.yy.cpp -ll -o bin/afh-parser
validate:
	bin/afh-parser "$(src).txt" "$(src).json"
clean:
	rm -rf src/lex.yy.c*
	rm -rf src/y.tab.c*
	rm -rf src/y.tab.h
	rm -rf bin/
