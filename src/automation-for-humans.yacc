%{
    #include "yacc-utils.h"
%}

%token URL CLICK TYPE WAIT HOVER EXECJS ON IN FOR
%token STRING_LITERAL INTEGER_CONSTANT WHITESPACE
%start translation_unit

%union {
    char *stringValue;
    int integerValue;
}

%type<stringValue> URL CLICK TYPE WAIT HOVER EXECJS ON IN FOR STRING_LITERAL
%type<integerValue> INTEGER_CONSTANT

%%
action
    : click_action
    | url_open_action
    | type_action
    | execjs
    | wait_action
    | hover_action
    ;
click_action
    : CLICK ON STRING_LITERAL { acceptAction(2, $1, $3); }
    | CLICK ON STRING_LITERAL STRING_LITERAL { acceptAction(2, $1, $3, $4); }
    ;
hover_action
    : HOVER ON STRING_LITERAL { acceptAction(2, $1, $3); }
    | HOVER ON STRING_LITERAL STRING_LITERAL { acceptAction(2, $1, $3, $4); }
    ;
url_open_action
    : URL STRING_LITERAL { acceptAction(2, $1, $2); }
    ;
type_action
    : TYPE STRING_LITERAL IN STRING_LITERAL { acceptAction(3, $1, $2, $4); }
    | TYPE STRING_LITERAL IN STRING_LITERAL STRING_LITERAL { acceptAction(3, $1, $2, $4, $5); }
execjs
    : EXECJS STRING_LITERAL { acceptAction(2, $1, $2); }
    ;
wait_action
    : WAIT FOR STRING_LITERAL { acceptAction(2, $1, $3); }
translation_unit
    : translation_unit action
    | action
    ;
%%
