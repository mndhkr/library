

#include "circular_linked_list.h"

typedef struct dict {
    clist *dict;
} dict;

typedef struct dict dict;

typedef struct dictnode {
    void* key;
    void* value;
} dictnode;

typedef enum dictaddret {
    dkeypresent,
    dkeyadded
} dictaddret;

struct dictionary_functions {
    dict*       (*create)(void);
    dictaddret  (*add)(dict*, void* key, void* value, bool (*equals)(void*, void*));
    void        (*remove)(dict*, void* key, bool (*equals)(void*, void*), bool);
    void*       (*get)(dict*, void* key, bool (*equals)(void*, void*));
};

typedef struct dictionary_functions dictionary_functions;

struct dictionary_functions * create_dictionary_functions_pointer(void);
void setup_dictionary_functions_struct(dictionary_functions* dictf);
