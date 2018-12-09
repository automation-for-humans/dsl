struct AFH_JSON {
    char type[100];
    char attribute[100];

    char args[10][100];
    int n_args;
};

void print_AFH_JSON(struct AFH_JSON s) {
    printf("[TYPE] : %s\n", s.type);
    for (int i = 0; i < s.n_args; i++) {
        printf("[ARGUMENT] %d : %s\n", i, s.args[i]);
    }
}
