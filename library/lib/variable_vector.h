

#include <stdbool.h>


#define VV_DEFAULT_INCREMENT 10

typedef struct vvector {
    void** vector;
    int increment;
    int count; // the number of actual elements;
    int size; // the maximum actual number of possible elements, ic est the size of the array;
    int seek;
} vvector;

typedef vvector vector;

struct vector_functions {
    vvector*    (*create)(void);
    int         (*count)(vvector*);
    int         (*size)(vvector*);
    int         (*append)(vvector*, void*);
    int         (*add)(vvector*, void*);
    int         (*push)(vvector*, void*);
    void*       (*peek)(vvector*);
    void*       (*pop)(vvector*);
    bool        (*has_next)(vvector*);
    bool        (*has_prev)(vvector*);
    void*       (*get_next)(vvector*);
    void*       (*get_prev)(vvector*);
};

typedef struct vector_functions vector_functions;

struct vector_functions *setup_vector_functions(void);
void get_vector_funcs(vector_functions *vecf);
