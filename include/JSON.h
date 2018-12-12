enum DATA_TYPE {
    INTEGER,
    DOUBLE,
    STRING,
    ARRAY,
    JSON
};

struct JSON {
    int integerValue;
    double doubleValue;
    char* stringValue;

    /* Stores what type of JSON is */
    enum DATA_TYPE type;

    /* Stores key and values */
    int numKeys;
    int maxKeys;
    char** keys;
    struct JSON** values;
};

struct JSON* makeJson() {
    struct JSON* j = (struct JSON*) malloc(sizeof(struct JSON));

    j->integerValue = 0;
    j->doubleValue = 0.0;
    j->stringValue = NULL;
    j->type = INTEGER;
    j->numKeys = 0;
    j->keys = NULL;
    j->values = NULL;

    return j;
}

struct JSON* makeJsonInt(int value) {
    struct JSON* j = makeJson();
    j->integerValue = value;
    j->type = INTEGER;
    return j;
}

struct JSON* makeJsonDouble(double value) {
    struct JSON* j = makeJson();
    j->doubleValue = value;
    j->type = DOUBLE;
    return j;
}

struct JSON* makeJsonString(char* value) {
    struct JSON* j = makeJson();
    char* s = (char*) malloc(strlen(value) + 1);
    j->stringValue = s;
    j->type = STRING;
    return j;
}

struct JSON* initJsonArray() {
    struct JSON* j = makeJson();
    j->type = ARRAY;
    return j;
}

int addKey(struct JSON* j, char *key) {
    /*
    * If we are full in capacity or have not allocated memory ever.
    */
    if (j->numKeys >= j->maxKeys) {
        if (j->maxKeys == 0) {
            j->numKeys = 1;
            j->maxKeys = 1;
            j->keys = (char**) malloc(sizeof(char*));
            j->values = (struct JSON**) malloc(sizeof(struct JSON**));
        } else {
            /*
            * We double the memory everytime it's full.
            * TODO: Is this a good heuristic for JSON usecase ?
            */
            j->maxKeys *= 2;
            j->keys = (char**) realloc(j->keys, sizeof(char*) * j->maxKeys);
            j->values = (struct JSON**) realloc(j->values, sizeof(struct JSON**) * j->maxKeys);
        }
    }
    j->keys[j->numKeys] = (char*) malloc(sizeof(char) * (strlen(key) + 1));

    strcpy(j->keys[j->numKeys], key);
    j->numKeys += 1;

    return j->numKeys - 1; // We have already incremented the numKeys :p.
}

void addKeyValInt(struct JSON* j, char* key, int value) {
    int index = addKey(j, key);
    j->values[index] = makeJsonInt(value);
}

void addKeyValDouble(struct JSON* j, char* key, double value) {
    int index = addKey(j, key);
    j->values[index] = makeJsonDouble(value);
}

void addKeyValString(struct JSON* j, char* key, char* value) {
    int index = addKey(j, key);
    j->values[index] = makeJsonString(value);
}

void addKeyValArray(struct JSON* j, char* key, struct JSON* value);
