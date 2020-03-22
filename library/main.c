#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/stdinclude.h"

int lldeftype;


void print_retains_and_value(memory_functions memf, int* ptr);


/*
void experiment() {

    DIR* dr = opendir("c:\\Users\\Shimoda\\");
    struct dirent* de;

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory");
        return 0;
    }

    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL)
        printf("%s\n", de->d_name);

    closedir(dr);
    return 0;
}
*/

bool streq(void* s1, void* s2) {
    if(strcmp((char*)s1, (char*)s2) == 0) {
        return true;
    }
    return false;
}

void teststatic() {
    static int y = 0;
    printf("%d\n", y);
}

void print_retains_and_value(memory_functions memf, int* ptr) {
    printf("retains: %d, value: %d\n", memf.getRetains(ptr), *ptr);
}

//struct list_functions *listf;

int main(int argc, char *argv[])
{
    list_functions listf;
    setup_list_functions_struct(&listf);
    //listf = setup_list_functions();
    
    
    printlns("testing list....");
    
    clist *lista = listf.create();
    int *n;
    for(int i = 0; i < 10; i++) {
        n = calloc(1, sizeof(int));
        *n = i;
        listf.insert(lista, n);
    }
    
    while(listf.has_next(lista)) {
        void *value = listf.llist_next_value(lista);
        printf("%p\t%d\n", value, *(int*)value);
    }
    
    println;
    
    
    printlns("testing vector....");
    
    vector_functions vecf;
    get_vector_funcs(&vecf);
    
    vvector* v = vecf.create();
    
    for(int i = 0; i < 100; i++) {
        n = calloc(1, sizeof(int));
        *n = i;
        vecf.push(v, n);
    }
    
    println;
    println;
    
    while(vecf.has_next(v)) {
        void* value = vecf.get_next(v);
        printf("%p\t%d\n", value, *(int*)value);
    }
    
    printlnn(3);
    
    
    
    for(int i = 0; i < 50; i++) {
        printf("num = %2d\tsize: %2d\tcount: %2d\n", *(int*)vecf.pop(v), v->size, v->count);
    }
    
    println;
    printlns("testing dictionary....");
    
    dictionary_functions dicf;
    setup_dictionary_functions_struct(&dicf);
    
    dict* dic = dicf.create();
    
    dicf.add(dic, "ciao", "test1", null);
    dicf.add(dic, "come", "prova1", null);
    dicf.add(dic, "stai", "test2", null);
    dicf.add(dic, "?", "prova2", null);
    
    char* s1 = (char*)dicf.get(dic, "stai", streq);
    char *s2 = (char*)dicf.get(dic, "come", streq);
    
    printf("%s\t%s\n", s1, s2);
    
    
    println;
    printlns("testing Strings....");
    
   
    String ciao = "ciao";
    
    String teststring = strConcat(ciao, ciao);
    
    if(strEquals(ciao, ciao)) {
        printlns(teststring);
    }
    
    println;
    
    printlns(substring(teststring, 2, 6));
    
    println;println;
    

    printf("Testo le funzioni di memoria....\n\n");

    memory_functions memf;
    setup_memory_functions(&memf);

    int* num = memf.alloc(sizeof(int), 1);

    print_retains_and_value(memf, num);

    memf.retain(num);

    print_retains_and_value(memf, num);

    *num = 10;
    
    print_retains_and_value(memf, num);

    memf.release(&num);

    print_retains_and_value(memf, num);

    memf.release(&num);

    printf("num new value: %p\n", num);
    //print_retains_and_value(memf, num);

    println;
    println;

    //experiment();
    
    s1 = "Ciao";
    s2 = "Come stai?";
    string s3 = strConcat(s1, " ");
    s3 = strConcat(s3, s2);
    s3 = strConcat(s3, "\n");
    print(s3);
    
    char** str = strSplitChars(s3, "Cs?a");
    
    for(int i = 0; str[i]!= null; i++) {
        printf("\"%s\"\n", str[i]);
    }
    
    
    file *f = openFile("/Users/shimoda/test.txt", read);
    vvector *lines = readLines(f);
    for(int i = 0; i < lines->count; i++) {
        printf("newline: \"%s\"\n", lines->vector[i]);
    }
    
    print("\n");
    print("\n");
    print("\n");
    print("\n");

    char* currentLine;
    while((currentLine = readLine(f))) {
        printf("\"%s\"\n", currentLine);
    }
    
    string in = input("Ciao: ");
    print(in);
}


