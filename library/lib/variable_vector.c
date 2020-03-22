


#include <stdlib.h>
#include "def.h"
#include "variable_vector.h"
#include "memory.h"


vvector* vvcreate(void);
int vvcount(vvector* v);
int vvsize(vvector* v);
void vvincrement(vvector *v);
int vvappend(vvector *v, void* elem);
int vvadd(vvector *v, void* elem);
int vvpush(vvector* v, void *elem);
void* vvpeek(vvector* v);
void* vvpop(vvector* v);
bool vvhasnext(vvector* v);
bool vvhasprev(vvector* v);
void* vvgetnext(vvector *v);
void* vvgetprev(vvector *v);


struct vector_functions *setup_vector_functions() {
    struct vector_functions *vec = calloc(1, sizeof(struct vector_functions));
    vec->add = &vvadd;
    vec->append = &vvappend;
    vec->count = &vvcount;
    vec->create = &vvcreate;
    vec->get_next = vvgetnext;
    vec->get_prev = &vvgetprev;
    vec->has_next = &vvhasnext;
    vec->has_prev = &vvhasprev;
    vec->peek = &vvpeek;
    vec->pop = &vvpop;
    vec->push = &vvpush;
    vec->size = &vvsize;
    return vec;
}


void get_vector_funcs(vector_functions* vecf) {
    vecf->add = &vvadd;
    vecf->append = &vvappend;
    vecf->count = &vvcount;
    vecf->create = &vvcreate;
    vecf->get_next = vvgetnext;
    vecf->get_prev = &vvgetprev;
    vecf->has_next = &vvhasnext;
    vecf->has_prev = &vvhasprev;
    vecf->peek = &vvpeek;
    vecf->pop = &vvpop;
    vecf->push = &vvpush;
    vecf->size = &vvsize;
}

// ----------------------------------------------


vvector* vvcreate() {
    vvector *new_vector = (vvector*)calloc(1, sizeof(vvector));
    new_vector->count = 0;
    new_vector->increment = VV_DEFAULT_INCREMENT;
    new_vector->vector = calloc(new_vector->increment, sizeof(void*));
    new_vector->size = new_vector->increment;
    new_vector->seek = -1;
    return new_vector;
}

int vvcount(vvector* v) {
    return v->count;
}

int vvsize(vvector* v)
{
    return v->size;
}

void vvincrement(vvector *v) {
    v->vector = (void**)realloc(v->vector, (v->size + v->increment) * sizeof(void*));
    v->size += v->increment;
    for(int i = v->count; i < v->size; i++) {
        v->vector[i] = null;
    }
}

void vvsetinc(vvector *v, int inc) {
    if(inc > 0 && inc < 1000000) {
        v->increment = inc;
    }
}

int vvappend(vvector *v, void* elem) {
    if(v->size == v->count) {
        vvincrement(v);
    }
    
    int pos = v->count;
    v->vector[pos] = elem;
    v->count++;
    return pos;
}

int vvadd(vvector *v, void* elem) {
    return vvappend(v, elem);
}

int vvpush(vvector* v, void *elem) {
    return vvappend(v, elem);
}

void* vvpeek(vvector* v) {
    if(v->count > 0)
        return v->vector[v->count-1];
    else
        return null;
}

void* vvpop(vvector* v) {
    if(v->count > 0) {
        void* val = v->vector[v->count-1];
        v->vector[v->count-1] = null;
        v->count--;
        if(v->size - v->count >= VV_DEFAULT_INCREMENT + 5 && v->size > v->increment) {
            v->vector = (void**)realloc(v->vector, (v->size - v->increment) * sizeof(void*));
            v->size -= v->increment;
            for(int i = v->count; i < v->size; i++) {
                v->vector[i] = null;
            }
        }
        return val;
    }

    return null;
}

bool vvhasnext(vvector* v) {
    if(v->seek < (v->count-1)) {
        return true;
    } else {
        return false;
    }
}

bool vvhasprev(vvector* v) {
    if(v->seek > 0 && v->seek <= v->count) {
        return true;
    } else {
        return false;
    }
}

void* vvgetnext(vvector *v) {
    if(v->seek < v->count - 1) {
        v->seek++;
        return v->vector[v->seek];
    }
    else
        return null;
    
}

void* vvgetprev(vvector *v) {
    if(v->seek > 0) 
        return v->vector[--v->seek];
    else
        return null;
    
}

void vvtrim(vvector *v) {
    if(v->count < v->size) {
        v->vector = (void**)realloc(v->vector, (v->count) * sizeof(void*));
        v->size = v->count;
    }
}
