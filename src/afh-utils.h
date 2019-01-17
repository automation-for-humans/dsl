#include <json.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <regex>

#include "afh-constants.h"

using namespace std;
using json = nlohmann::json;

struct AFH_ACTION {
    string type;

    string args[MAX_ARGS];
    int n_args;
};

struct AFH_ACTION_LIST {
    vector<struct AFH_ACTION*> action_list;
};

/*
* Utility function to print the AFH_ACTION struct
*/
void print_afh_action(struct AFH_ACTION* s) {
    cout<<"[TYPE] : "<<s->type<<endl;
    for (int i = 0; i < s->n_args; i++) {
        cout<<"[ARGUMENT] "<<i<<" : "<<s->args[i]<<endl;
    }
}

/*
* Adds an action to a list of actions.
* We have to wrap around basic data structres so that the yacc file accepts it.
*/
struct AFH_ACTION_LIST* add_to_action_list(AFH_ACTION_LIST* action_list, struct AFH_ACTION* action) {
    /* Initialise the list if not yet initialised */
    if (action_list == NULL) {
        action_list = new struct AFH_ACTION_LIST;
    }
    /* Add the action to the list */
    action_list->action_list.push_back(action);

    return action_list;
}

/*
* Converts AFH_ACTION to json.
*/
json convert_action_to_json(struct AFH_ACTION* action) {
    json j;
    j[ACTION_TYPE] = action->type;
    j[ARGS] = json::object();

    for (int i = 0; i < action->n_args; i++) {
        /*
        * Here we have to do this hack to remove the quotes from the string.
        */
        action->args[i] = std::regex_replace(action->args[i], std::regex("\""), "");

        if (action->type == CLICK_ACTION || action->type == HOVER_ACTION || action->type == CLICK_IF_PRESENT_ACTION || action->type == WAIT_UNTIL) {
            switch(i) {
                case CLICK_INDEX_INDEX :
                    j[ARGS][INDEX] = action->args[i];
                    break;
                case CLICK_SUBJECT_INDEX :
                    j[ARGS][SUBJECT] = action->args[i];
                    break;
                case CLICK_ATTRIBUTE_INDEX :
                    j[ARGS][ATTRIBUTE] = action->args[i];
                    break;
                default :
                    break;
            }
        } else if (action->type == TYPE_ACTION) {
            switch(i) {
                case TYPE_INDEX_INDEX :
                    j[ARGS][INDEX] = action->args[i];
                    break;
                case TYPE_SUBJECT_INDEX :
                    j[ARGS][SUBJECT] = action->args[i];
                    break;
                case TYPE_ATTRIBUTE_INDEX :
                    j[ARGS][ATTRIBUTE] = action->args[i];
                    break;
                case TYPE_USER_INPUT_INDEX :
                    j[ARGS][USER_INPUT] = action->args[i];
                    break;
                default :
                    break;
            }
        } else if (action->type == OPEN_ACTION || action->type == WAIT_ACTION || action->type == EXECJS_ACTION) {
            j[ARGS][SUBJECT] = action->args[i];
        } else if (action->type == ASSERT_ACTION) {
            switch(i) {
                case ASSERT_SUBJECT_INDEX :
                    j[ARGS][SUBJECT] = action->args[i];
                    break;
                case ASSERT_ATTRIBUTE_INDEX :
                    j[ARGS][ATTRIBUTE] = action->args[i];
                    break;
                default :
                    break;
            }
            /* We don't allow searching by index in asserts. */
            j[ARGS][INDEX] = EMPTY_STRING;
        }
    }
    return j;
}

/*
* Converts the AFH_ACTION_LIST to json string.
*/
void convert_action_list_to_json(AFH_ACTION_LIST* action_list) {
    /* Initialising the json */
    json j;
    j[COMMANDS] = json::array();
    for (struct AFH_ACTION* action : action_list->action_list) {
        j[COMMANDS].push_back(convert_action_to_json(action));
    }
    cout<<std::setw(4)<<j<<std::endl;
}
