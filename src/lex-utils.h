#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

/*
* Utilities used in the lex.
*/

/*
* NOTE: The fields used for "yylval" like :
*   yylval.stringValue
*   yylval.integerValue
* etc. are defined in the YACC file along with the grammar.
* TODO: Can we externalise it from the YACC file.
*/

/*
* Saves a String token so that it can be used by the parser.
*/
void saveStringToken() {
    char *result = new char[strlen(yytext)+1];
    strcpy(result, yytext);

    yylval.stringValue = result;
}

/*
* Saves a Integer token so that it can be used by the parser.
*/
void saveIntegerToken() {
    yylval.integerValue = atoi(yytext);
}
