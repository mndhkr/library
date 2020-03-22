
#include <stdbool.h>

typedef struct clnode {
    struct clnode *next;
    struct clnode *prev;
    void* value;
} clnode;

typedef struct clist {
    clnode *header;
    int count;
    clnode *seek;
} clist;

typedef clist list;

struct list_functions {
    clist* (*create)(void);
    bool    (*insert)(clist*, void*);
    bool    (*add)(clist*, void*);
    int     (*adjust_count)(clist*);
    void    (*seek_reset)(clist*);
    clnode* (*clist_next_node)(clist*);
    clnode* (*clist_prev_node)(clist*);
    clnode* (*llist_next_node)(clist*);
    clnode* (*llist_prev_node)(clist*);
    void*   (*clist_next_value)(clist*);
    void*   (*clist_prev_value)(clist*);
    bool    (*has_next)(clist*);
    bool    (*has_prev)(clist*);
    void*   (*llist_next_value)(clist*);
    void*   (*llist_prev_value)(clist*);
    
    void    (*delete_node)(clist*, clnode*, bool);
    void    (*delete_by_value)(clist*, void*, bool, bool);
    void    (*push)(clist*, void*);
    void*   (*pop)(clist*);
    void*   (*peek)(clist*);
    void    (*append)(clist*, void*);
    bool    (*insert_at)(clist*, void*, int);
    bool    (*set)(clist*, int, void*);
    void*   (*get)(clist*, int);
    clnode* (*get_node)(clist*, int);
    //void    (*set_node)(clist* list, void* value, int pos);
};

typedef struct list_functions list_functions;

struct list_functions * create_list_functions_pointer(void);
void setup_list_functions_struct(list_functions* listf);


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








