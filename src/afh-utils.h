#include <JSON.h>

struct AFH_ACTION {
    char type[100];

    char args[10][500];
    int n_args;
};

void print_afh_action(struct AFH_ACTION s) {
    printf("[TYPE] : %s\n", s.type);
    for (int i = 0; i < s.n_args; i++) {
        printf("[ARGUMENT] %d : %s\n", i, s.args[i]);
    }
}

/*
* Converts AFH_ACTION to JSON string.
*/
void get_afh_action_json(struct AFH_ACTION s) {

}
