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
    cout<<"[TYPE] : "<<s->type<<"\n";
    for (int i = 0; i < s->n_args; i++) {
        cout<<"[ARGUMENT] "<<i<<" : "<<s->args[i]<<"\n";
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
    j[TYPE] = action->type;
    j[ARGS] = json::array();
    for (int i = 0; i < action->n_args; i++) {
        /*
        * Here we ave to do this hack to remove the quotes from the string.
        */
        j[ARGS].push_back(std::regex_replace(action->args[i], std::regex("\""), ""));
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
