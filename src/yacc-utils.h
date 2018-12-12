#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

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
struct AFH_ACTION acceptAction(int n_args, ...) {
    va_list arguments;

    struct AFH_ACTION afh_action; // Where we will store all the good stuff.

    va_start(arguments, n_args);
    for (int i = 0; i < n_args; i++) {
        if (i == 0) {
            strcpy(afh_action.type, va_arg(arguments, char *));
            afh_action.n_args = 0;
        } else {
            strcpy(afh_action.args[i-1], va_arg(arguments, char *));
            afh_action.n_args++;
        }
    }
    va_end(arguments);

    print_afh_action(afh_action);

    get_afh_action_json(afh_action);

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

    /* parse through the input until there is no more */
    do {
        yyparse();
    } while (!feof(yyin));

    printf("[SUCCESS] Pasring of %s done!\n", argv[1]);

    return 0;
}

void yyerror(char *s) {
    printf("EEK, parse error!  Message: %s\n", s);

    /*
    * Halt as soon as we get a parse error.
    */
    exit(1);
}
