#define TYPE "type"
#define ARGS "args"
#define COMMANDS "commands"
#define EMPTY_STRING ""

// action types
#define CLICK_ACTION "click"
#define HOVER_ACTION "hover"
#define TYPE_ACTION "type"
#define OPEN_ACTION "open"
#define EXECJS_ACTION "execjs"
#define WAIT_ACTION "wait"
#define CLICK_IF_PRESENT_ACTION "click if present"
#define WAIT_UNTIL "wait until"

// Common args for all/most of the actions
#define SUBJECT "subject"
#define INDEX "index"
#define ATTRIBUTE "attribute"

// args for type action
#define USER_INPUT "input"

// For different action types, teh args will mean different things.

// indices for "click" action
#define CLICK_INDEX_INDEX 0
#define CLICK_SUBJECT_INDEX 1
#define CLICK_ATTRIBUTE_INDEX 2

// incdices for "type" action
#define TYPE_USER_INPUT_INDEX 0
#define TYPE_INDEX_INDEX 1
#define TYPE_SUBJECT_INDEX 2
#define TYPE_ATTRIBUTE_INDEX 3

// indices for "open" action
#define OPEN_SUBJECT_INDEX 0

// indices for "execjs" action
#define EXECJS_SUBJECT_INDEX 0

// indices for "wait" action
#define WAIT_SUBJECT_INDEX 0

#define MAX_ARGS 10
