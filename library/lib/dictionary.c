
#include "def.h"
#include "dictionary.h"

#include <stdlib.h>

dict* dictcreate();
dictaddret dictadd(dict *d, void* key, void* value, bool (*equals)(void* key1, void *key2));
void dictremove(dict* d, void* key, bool (*equals)(void* key1, void *key2), bool freekv);
void* dictget(dict* d, void* key, bool (*equals)(void* key1, void *key2));


struct list_functions *listf;


struct dictionary_functions *create_dictionary_functions_pointer() {
    struct dictionary_functions *dict = calloc(1, sizeof(struct dictionary_functions));
    dict->add = &dictadd;
    dict->create = &dictcreate;
    dict->get = &dictget;
    dict->remove = &dictremove;
    return dict;
}

void setup_dictionary_functions_struct(dictionary_functions* dictf) {
    dictf->add = &dictadd;
    dictf->create = &dictcreate;
    dictf->get = &dictget;
    dictf->remove = &dictremove;
}
// ----------------------------------------------


dict* dictcreate() {
    dict* d = calloc(1, sizeof(dict));
    listf = create_list_functions_pointer();
    d->dict = listf->create();
    return d;
}

dictaddret dictadd(dict* d, void* key, void* value, bool (*equals)(void* key1, void* key2)) {
    
    listf->seek_reset(d->dict);
    while(listf->has_next(d->dict)) {
        dictnode* dnode = (dictnode*)listf->llist_next_value(d->dict);
        if(dnode) {
            if(equals == null) {
                if(dnode->key == key) {
                    return dkeypresent;
                }
            } else {
                if(equals(dnode->key, key)) {
                    return dkeypresent;
                }
            }
        } else {
            break;
        }
    }
    
    dictnode* dnode = calloc(1, sizeof(dictnode));
    dnode->key = key;
    dnode->value = value;
    listf->insert(d->dict, dnode);
    return dkeyadded;   
}

void dictremove(dict* d, void* key, bool (*equals)(void* key1, void *key2), bool freekv)
{
    listf->seek_reset(d->dict);
    while(listf->has_next(d->dict)) {
        dictnode* dnode = (dictnode*)listf->llist_next_value(d->dict);
        if(equals == null) {
            if(dnode->key == key) {
                if(freekv) {
                    free(dnode->key);
                    free(dnode->value);
                }
                listf->delete_by_value(d->dict, dnode, true, true);
            }            
        } else {
            if(equals(dnode->key, key)) {
                if(freekv) {
                    free(dnode->key);
                    free(dnode->value);
                }
                listf->delete_by_value(d->dict, dnode, true, true);
            }
        }
    }
}

void* dictget(dict* d, void* key, bool (*equals)(void* key1, void *key2))
{
    listf->seek_reset(d->dict);
    while(listf->has_next(d->dict)) {
        dictnode* dnode = (dictnode*)listf->llist_next_value(d->dict);
        if(equals == null) {
            if(dnode->key == key) {
                return dnode->value;
            }            
        } else {
            if(equals(dnode->key, key)) {
                return dnode->value;
            }
        }
    }
    return NULL;
}
