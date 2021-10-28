%{
    #include "yacc-utils.h"
%}

%token OPEN CLICK TYPE WAIT HOVER EXECJS ON IN FOR IF PRESENT UNTIL ASSERT SHORTCUT
%token STRING_LITERAL INTEGER_CONSTANT WHITESPACE END_OF_FILE INTEGER_SPECIFIER
%start translation_unit

%union {
    char *stringValue;
    int integerValue;
    struct AFH_ACTION* afhAction;
    struct AFH_ACTION_LIST* actionList;
}

%type<stringValue> OPEN CLICK TYPE WAIT HOVER EXECJS ON IN FOR IF PRESENT UNTIL ASSERT SHORTCUT
%type<stringValue> STRING_LITERAL INTEGER_CONSTANT INTEGER_SPECIFIER
%type<afhAction> action click_action hover_action open_action type_action execjs wait_action click_if_present_action wait_until_action assert_action shortcut_action
%type<actionList> translation_unit

%%
action
    : click_action { $$ = $1; }
    | open_action { $$ = $1; }
    | type_action { $$ = $1; }
    | execjs { $$ = $1; }
    | wait_action { $$ = $1; }
    | hover_action { $$ = $1; }
    | click_if_present_action { $$ = $1; }
    | wait_until_action { $$ = $1; }
    | assert_action { $$ = $1; }
    | shortcut_action { $$ = $1; }
    ;
shortcut_action
    : SHORTCUT STRING_LITERAL IN STRING_LITERAL { $$ = acceptAction(5, $1, EMPTY_STRING, $2, $4, EMPTY_STRING); }
    ;
click_action
    : CLICK ON STRING_LITERAL { $$ = acceptAction(4, $1, EMPTY_STRING, $3, EMPTY_STRING); }
    | CLICK ON STRING_LITERAL STRING_LITERAL { $$ = acceptAction(4, $1, EMPTY_STRING, $3, $4); }
    | CLICK ON INTEGER_CONSTANT INTEGER_SPECIFIER STRING_LITERAL { $$ = acceptAction(4, $1, $3, $5, EMPTY_STRING); }
    | CLICK ON INTEGER_CONSTANT INTEGER_SPECIFIER STRING_LITERAL STRING_LITERAL { $$ = acceptAction(4, $1, $3, $5, $6); }
    ;
hover_action
    : HOVER ON STRING_LITERAL { $$ = acceptAction(4, $1, EMPTY_STRING, $3, EMPTY_STRING); }
    | HOVER ON STRING_LITERAL STRING_LITERAL { $$ = acceptAction(4, $1, EMPTY_STRING, $3, $4); }
    | HOVER ON INTEGER_CONSTANT INTEGER_SPECIFIER STRING_LITERAL { $$ = acceptAction(4, $1, $3, $5, EMPTY_STRING); }
    | HOVER ON INTEGER_CONSTANT INTEGER_SPECIFIER STRING_LITERAL STRING_LITERAL { $$ = acceptAction(4, $1, $3, $5, $6); }
    ;
open_action
    : OPEN STRING_LITERAL { $$ = acceptAction(2, $1, $2); }
    ;
type_action
    : TYPE STRING_LITERAL IN STRING_LITERAL { $$ = acceptAction(5, $1, $2, EMPTY_STRING, $4, EMPTY_STRING); }
    | TYPE STRING_LITERAL IN STRING_LITERAL STRING_LITERAL { $$ = acceptAction(5, $1, $2, EMPTY_STRING, $4, $5); }
    | TYPE STRING_LITERAL IN INTEGER_CONSTANT INTEGER_SPECIFIER STRING_LITERAL { $$ = acceptAction(5, $1, $2, $4, $6, EMPTY_STRING); }
    | TYPE STRING_LITERAL IN INTEGER_CONSTANT INTEGER_SPECIFIER STRING_LITERAL STRING_LITERAL { $$ = acceptAction(5, $1, $2, $3, $6, $7); }
    ;
execjs
    : EXECJS STRING_LITERAL { $$ = acceptAction(2, $1, $2); }
    ;
wait_action
    : WAIT FOR STRING_LITERAL { $$ = acceptAction(2, $1, $3); }
    ;
click_if_present_action
    : CLICK IF PRESENT ON STRING_LITERAL { $$ = acceptAction(4, CLICK_IF_PRESENT_ACTION, EMPTY_STRING, $5, EMPTY_STRING); }
    | CLICK IF PRESENT ON STRING_LITERAL STRING_LITERAL { $$ = acceptAction(4, CLICK_IF_PRESENT_ACTION, EMPTY_STRING, $5, $6); }
    | CLICK IF PRESENT ON INTEGER_CONSTANT INTEGER_SPECIFIER STRING_LITERAL { $$ = acceptAction(4, CLICK_IF_PRESENT_ACTION, $6, $7, EMPTY_STRING); }
    | CLICK IF PRESENT ON INTEGER_CONSTANT INTEGER_SPECIFIER STRING_LITERAL STRING_LITERAL { $$ = acceptAction(4, CLICK_IF_PRESENT_ACTION, $5, $7, $8); }
    ;
wait_until_action
    : WAIT UNTIL STRING_LITERAL { $$ = acceptAction(4, WAIT_UNTIL, EMPTY_STRING, $3, EMPTY_STRING); }
    | WAIT UNTIL STRING_LITERAL STRING_LITERAL { $$ = acceptAction(4, WAIT_UNTIL, EMPTY_STRING, $3, $4); }
    | WAIT UNTIL INTEGER_CONSTANT INTEGER_SPECIFIER STRING_LITERAL { $$ = acceptAction(4, WAIT_UNTIL, $3, $5, EMPTY_STRING); }
    | WAIT UNTIL INTEGER_CONSTANT INTEGER_SPECIFIER STRING_LITERAL STRING_LITERAL { $$ = acceptAction(4, WAIT_UNTIL, $3, $5, $6); }
    ;
assert_action
    : ASSERT STRING_LITERAL { $$ = acceptAction(3, $1, $2, EMPTY_STRING); }
    | ASSERT STRING_LITERAL IN STRING_LITERAL { $$ = acceptAction(3, $1, $2, $4); }
    ;
translation_unit
    : translation_unit action {$$ = add_to_action_list($1, $2); }
    | action { $$ = add_to_action_list(NULL, $1); }
    | translation_unit END_OF_FILE { convert_action_list_to_json($1); }
    ;
%%
