//
//  files.h
//  library
//
//  Created by Shimoda on 22/03/2020.
//  Copyright © 2020 Shimoda. All rights reserved.
//

#ifndef files_h
#define files_h

#include <stdio.h>
enum fileOpenMode {
    read,
    write,
    read_write,
    append,
    create
};

typedef struct file {
    FILE* fp;
    unsigned long seek;
} file;

file *openFile(string path, enum fileOpenMode mode);
vvector *readLines(file *f);
char *readLine(file *f);



#endif /* files_h */
