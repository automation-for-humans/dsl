#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

#include "afh-utils.h"

/*
* Things that lex requires
*/
extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(char* s);

/*
* Utilities used in the yacc.
*/

/*
* This is used to accept an action that has been specified
*/
struct AFH_ACTION* acceptAction(int n_args, ...) {
    va_list arguments;

    struct AFH_ACTION* afh_action = new struct AFH_ACTION; // Where we will store all the good stuff.

    va_start(arguments, n_args);
    for (int i = 0; i < n_args; i++) {
        if (i == 0) {
            afh_action->type.assign(va_arg(arguments, char *));
            afh_action->n_args = 0;
        } else {
            afh_action->args[i-1].assign(va_arg(arguments, char *));
            afh_action->n_args++;
        }
    }
    va_end(arguments);

    return afh_action;
}

/*
* The main function called in the yacc file.
*/
int main(int argc, char** argv) {
    FILE *myfile = fopen(argv[1], "r");

    if (!myfile) {
        printf("Couldn't open file : %s\n", argv[1]);
        return -1;
    }
    /* Ask lex to read from this file than STDIN */
    yyin = myfile;

    /* Redirecting stdout to FILE */
    freopen(argv[2], "w", stdout);

    /* parse through the input until there is no more */
    do {
        yyparse();
    } while (!feof(yyin));

    return 0;
}

void yyerror(char *s) {
    printf("EEK, parse error!  Message: %s\n", s);

    /*
    * Halt as soon as we get a parse error.
    */
    exit(1);
}