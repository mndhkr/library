
#include <stdlib.h>
#include "def.h"
#include "circular_linked_list.h"


clist *clcreate(void);
bool clinsert(clist *list, void *value);
bool cladd(clist *list, void *value);
// aggiusta il conteggio dei nodi dopo una manipolazione manuale.
int cladjc(clist *list);
void clseekreset(clist* list);
clnode *clgetnextnode(clist* list);
clnode *clgetprevnode(clist* list);
clnode *llgetnextnode(clist* list);
clnode *llgetprevnode(clist* list);
void* clgetnextvalue(clist* list);
void* clgetprevvalue(clist* list);
bool llhasnext(clist *list);
bool llhasprev(clist *list);
void* llgetnextvalue(clist* list);
void* llgetprevvalue(clist* list);
// clist delete node (elimina il nodo con free)
void cldelnode(clist* list, clnode* node, bool free);
void cldelvalue(clist *list, void* value, bool all, bool free);
void clpush(clist *list, void* value);
void* clpop(clist *list);
void* clpeek(clist *list);
void clappend(clist *list, void *value);
bool clinspos(clist *list, void *value, int pos);
bool clset(clist* list, int pos, void* value);
void* clget(clist* list, int pos);
clnode* clgetnode(clist* list, int pos);
//void clsetnode(clist* list, void* value, int pos);



struct list_functions *create_list_functions_pointer() {
    struct list_functions* listf;
    listf = calloc(1, sizeof(struct list_functions));
    listf->add = &cladd;
    listf->adjust_count = &cladjc;
    listf->append = &clappend;
    listf->clist_next_node = &clgetnextnode;
    listf->clist_next_value = & clgetnextvalue;
    listf->clist_prev_node = &clgetprevnode;
    listf->clist_prev_value = &clgetprevvalue;
    listf->create = &clcreate;
    listf->delete_by_value = &cldelvalue;
    listf->delete_node = &cldelnode;
    listf->get = &clget;
    listf->get_node = &clgetnode;
    listf->has_next = &llhasnext;
    listf->has_prev = &llhasprev;
    listf->insert = &clinsert;
    listf->insert_at = &clinspos;
    listf->llist_next_node = &llgetnextnode;
    listf->llist_next_value = &llgetnextvalue;
    listf->llist_prev_node = &llgetprevnode;
    listf->llist_prev_value = &llgetprevvalue;
    listf->peek = &clpeek;
    listf->pop = &clpop;
    listf->push = &clpush;
    listf->seek_reset = &clseekreset;
    listf->set = &clset;
    return listf;
}

void setup_list_functions_struct(list_functions *listf) {
    listf->add = &cladd;
    listf->adjust_count = &cladjc;
    listf->append = &clappend;
    listf->clist_next_node = &clgetnextnode;
    listf->clist_next_value = &clgetnextvalue;
    listf->clist_prev_node = &clgetprevnode;
    listf->clist_prev_value = &clgetprevvalue;
    listf->create = &clcreate;
    listf->delete_by_value = &cldelvalue;
    listf->delete_node = &cldelnode;
    listf->get = &clget;
    listf->get_node = &clgetnode;
    listf->has_next = &llhasnext;
    listf->has_prev = &llhasprev;
    listf->insert = &clinsert;
    listf->insert_at = &clinspos;
    listf->llist_next_node = &llgetnextnode;
    listf->llist_next_value = &llgetnextvalue;
    listf->llist_prev_node = &llgetprevnode;
    listf->llist_prev_value = &llgetprevvalue;
    listf->peek = &clpeek;
    listf->pop = &clpop;
    listf->push = &clpush;
    listf->seek_reset = &clseekreset;
    listf->set = &clset;
}

// ----------------------------------------------


clist *clcreate() {
    clist *list = calloc(1, sizeof(clist));
    list->header = null;
    list->count = 0;
    list->seek = null;
    return list;
}

bool clinsert(clist *list, void *value) {
    if(list->count == 0) {
        clnode *node = calloc(1, sizeof(clnode));
        node->value = value;
        node->next = node;
        node->prev = node;
        list->count = 1;
        list->header = node;
        return true;
    } else {
        clnode *last = list->header->prev;
        clnode *node = calloc(1, sizeof(clnode));
        node->value = value;
        last->next = node;
        list->header->prev = node;
        node->prev = last;
        node->next = list->header;
        if(list->header->next == list->header) {
            list->header->next = node;
        }
        list->count++;
        return true;
    }
}

bool cladd(clist *list, void *value) {
    return clinsert(list, value);
}

int clcount(clist* list) {
    return list->count;
}

// aggiusta il conteggio dei nodi dopo una manipolazione manuale.
int cladjc(clist *list) {
    int count = 0;
    clnode *node;
    node = list->header;
    
    if(node == null) {
        list->count = 0;
        return 0;
    }
    
    if(list->header->value) {
        do {
            count++;
            node = node->next;
        } while(node != list->header);
    }
    
    list->count = count;
    
    return count;
}

void clseekreset(clist* list)
{
    list->seek = null;
}

clnode *clgetnextnode(clist* list)
{
    if(list->count == 0)
        return null;
    
    if(list->seek == null) {
        list->seek = list->header;
        return list->seek;
    }
    
    list->seek = list->seek->next;
    return list->seek;
}


clnode *clgetprevnode(clist* list) {
    
    if(list->count == 0)
        return null;
    
    if(list->seek == null) {
        list->seek = list->header->prev;
        return list->seek;
    }
    
    list->seek = list->seek->prev;
    return list->seek;
}

clnode *llgetnextnode(clist* list) {
    if(list->count == 0) {
        return null;
    }
    
    if(list->seek->next == list->header) {
        return null;
    } else {
        return clgetnextnode(list);
    }
}

clnode *llgetprevnode(clist* list) {
    if(list->count == 0) {
        return null;
    }
    
    if(list->seek->prev == list->header->prev) {
        return null;
    } else {
        return clgetprevnode(list);
    }
}

void* clgetnextvalue(clist* list)
{
    clnode *node = clgetnextnode(list);
    if(node)
        return node->value;
    else
        return null;
}

void* clgetprevvalue(clist* list) {
    clnode *node = clgetprevnode(list);
    if(node)
        return node->value;
    else
        return null;
}

bool llhasnext(clist *list) {
    if(list->count == 0) {
        return false;
    }
    
    if(list->seek == null) {
        return true;
    }
    
    if(list->seek->next && list->seek->next != list->header) {
        return true;
    } else {
        return false;
    }
}

bool llhasprev(clist *list) {
    if(list->count == 0) {
        return false;
    }
    
    if(list->seek == null) {
        return true;
    }
    
    if(list->seek->prev && list->seek->prev != list->header->prev) {
        return true;
    } else {
        return false;
    }
}


void* llgetnextvalue(clist* list) {
    if(list->count == 0)
        return null;
    
    if(list->seek == null) {
        list->seek = list->header;
        return list->seek->value;
    }
    
    if(list->seek->next == list->header) {
        return null;
    } else {
        return clgetnextvalue(list);
    }
}

void* llgetprevvalue(clist* list) {
    if(list->count == 0)
        return null;
    
    if(list->seek == null) {
        list->seek = list->header->prev;
        return list->seek->value;
    }
    
    if(list->seek->prev == list->header->prev) {
        return null;
    } else {
        return clgetprevvalue(list);
    }
}


// clist delete node (elimina il nodo con free)
void cldelnode(clist* list, clnode* node, bool freevalue) {
    if(list->count == 0) return;
    if(node && node->next && node->prev) {
        if(list->count == 1) {
            list->header = null;
            list->count = 0;
            if(freevalue) {
                free(node->value);
            }
            free(node);
        } else {
            clnode* prevnode = node->prev;
            clnode* nextnode = node->next;
            prevnode->next = nextnode;
            nextnode->prev = prevnode;
            if(freevalue) {
                free(node->value);
            }
            free(node);
        }
        list->count--;
    }
} 

/*
// clist unlink node (slinka il nodo dalla lista)
void clulnode(clist** list, cnode* node) {
    if(node && node->next && node->prev) {
        if(node == *list) {
            *list = clcreate();
        } else {
            cnode* prevnode = node->prev;
            cnode* nextnode = node->next;
            prevnode->next = nextnode;
            nextnode->prev = prevnode;
        }
    }
} 
*/

void cldelvalue(clist *list, void* value, bool all, bool freevalue) {
    if(list->count == 0) return;
    if(list->count == 1) {
        if(list->header->value == value) {
            if(freevalue) {
                free(list->header->value);
            }
            free(list->header);
            list->header = null;
            list->count--;
        }
    } else {
        clnode *prev, *next;
        int count = list->count;
        clnode *node = list->header;
        for(int i = 0; i < count; i++) {
            if(node->value == value) {
                prev = node->prev;
                next = node->next;
                if(freevalue) {
                    free(node->value);
                }
                node->value = null;
                prev->next = next;
                next->prev = prev;
                node = node->next;
                free(node);
                list->count--;
                if(!all) break;
            } else {
                node = node->next;
            }
        }
    }
}

/*
cnode* clulvalue(clist **list, void* value, bool all) {
    if(clcount(*list) == 1) {
        if(*list->value == value) {
            cnode *node = *list;
            *list = clcreate();
            return node;
        }
    } else {
        cnode *prev, *next;
        int count = clcount(list);
        cnode *node = list;
        for(int i = 0; i < count; i++) {
            if(node->value == value) {
                prev = node->prev;
                next = node->next;
                if(free) {
                    free(node->value);
                }
                node->value = null;
                prev->next = next;
                next->prev = prev;
                node = node->next;
                free(node);
                if(!all) break;
            } else {
                node = node->next;
            }
        }
    }
}
*/

void clpush(clist *list, void* value) {
    clinsert(list, value);
}

void* clpop(clist *list) {
    if(list->header->prev) {
        clnode *node = list->header->prev;
        void *value = node->value;
        cldelnode(list, node, false);
        return value;
    }
    return null;
}

void* clpeek(clist *list) {
    return clget(list, -1);
}

void clappend(clist *list, void *value) {
    clinsert(list, value);
}

bool clinspos(clist *list, void *value, int pos) {
    int count = list->count;

    if(count == 0) {
        clinsert(list, value);
        return true;
    } else if(count > 0) {
        clnode* node = list->header;
        for(int i = 0; i < pos; i++)
            node = node->next;
        clnode *next = node->next;
        clnode* newnode = calloc(1, sizeof(clnode));
        newnode->value = value;
        newnode->next = next;
        newnode->prev = node;
        if(pos == 0) {
            list->header = node;
        }
        list->count++;
        return true;
    }

    return false;
}

// #include <stdio.h>
// void llprint(clist *list) {
//     int count = clcount(list);
//     clist *node = list;
//     for(int i = 0; i < count; i++) {
//         printf("%x\t%d\n", node, *(int*)node->value);
//         node = node->next;
//     }
//     return;
// }


bool clset(clist* list, int pos, void* value) {
    int count = list->count;
    if(count == 0) return false;
    
    clnode *node = list->header;
    
    if(pos >= 0) {
        for(int i = 0; i < pos; i++) {
            node = node->next;
        }
    } else {
        for(int i = 0; i > pos; i--) {
            node = node->prev;
        }
    }
    
    node->value = value;
    return true;
}

void* clget(clist* list, int pos) {
    int count = list->count;
    if(count == 0) return null;
    
    clnode *node = list->header;
    
    if(pos >= 0) {
        for(int i = 0; i < pos; i++) {
            node = node->next;
        }
    } else {
        for(int i = 0; i > pos; i--) {
            node = node->prev;
        }
    }
    
    return node->value;
}

clnode* clgetnode(clist* list, int pos) {
    int count = list->count;
    if(count == 0) return null;
    
    clnode *node = list->header;
    
    if(pos >= 0) {
        for(int i = 0; i < pos; i++) {
            node = node->next;
        }
    } else {
        for(int i = 0; i > pos; i--) {
            node = node->prev;
        }
    }
    
    return node;
}

// TODO: sistemare questa, dovrebbe inserire un nodo.
void clsetnode(clist* list, void* value, int pos) {
    clinspos(list, value, pos);
}







