all:
	mkdir -p bin/
	bison --defines=src/y.tab.h -o src/y.tab.cpp src/automation-for-humans.yacc
	flex -o src/lex.yy.cpp src/automation-for-humans.lex
	g++ -w -std=c++11 -Iinclude/ -ll src/y.tab.cpp src/lex.yy.cpp -o bin/afh-parser
alpine:
	mkdir -p bin/
	bison --defines=src/y.tab.h -o src/y.tab.cpp src/automation-for-humans.yacc
	flex -o src/lex.yy.cpp src/automation-for-humans.lex
	g++ -w -std=c++11 -Iinclude/ /usr/bin/flex src/y.tab.cpp src/lex.yy.cpp -o bin/afh-parser
validate:
	bin/afh-parser "$(src).txt" "$(src).json"
clean:
	rm -rf src/lex.yy.c*
	rm -rf src/y.tab.c*
	rm -rf src/y.tab.h
	rm -rf bin/
