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
struct AFH_JSON acceptAction(int n_args, ...) {
    va_list arguments;

    struct AFH_JSON afh_json; // Where we will store all the good stuff.

    va_start(arguments, n_args);
    for (int i = 0; i < n_args; i++) {
        if (i == 0) {
            strcpy(afh_json.type, va_arg(arguments, char *));
            afh_json.n_args = 0;
        } else {
            strcpy(afh_json.args[i-1], va_arg(arguments, char *));
            afh_json.n_args++;
        }
    }
    va_end(arguments);

    print_AFH_JSON(afh_json);

    return afh_json;
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
