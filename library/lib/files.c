//
//  files.c
//  library
//
//  Created by Shimoda on 22/03/2020.
//  Copyright © 2020 Shimoda. All rights reserved.
//

#include "stdinclude.h"


file *openFile(string path, enum fileOpenMode mode) {
    file *file = alloc(sizeof(file),1);
    string mode_ = "r";
    if(mode == read) {
        mode_ = "r";
    }
    if(mode == write) {
        mode_ = "w";
    }
    if(mode == read_write) {
        mode_ = "rw";
    }
    if(mode == append) {
        mode_ = "a";
    }
    file->fp = fopen(path, mode_);
    file->seek = 0;
    return file;
}


vvector *readLines(file *f) {
    if(f == null) return null;
    
    vvector *v = vvcreate();
    
    char *currentLine;
    
    while(1) {
        char c;
        int count = 0;
        while((c = fgetc(f->fp)) != '\n' && c != EOF) {
            count++;
        }
        if(count == 0 && c != EOF) {
            continue;
        }
        if(count == 0 && c == EOF) {
            break;
        }
        fseek(f->fp, -count-1, SEEK_CUR);
        currentLine = alloc(sizeof(char), count+1);
        for(int i = 0; i < count; i++) {
            currentLine[i] = fgetc(f->fp);
        }
        fgetc(f->fp);
        currentLine[count] = 0;
        vvadd(v, trim(currentLine));
        if(c == EOF) break;
    }
    
    vvtrim(v);
    return v;
}

// Legge una riga, le righe vuote sono omesse.
char *readLine(file *f) {
    if(f == null) return null;
    
    char *currentLine = NULL;
    
    fseek(f->fp, f->seek, SEEK_SET);
    while(1) {
        char c;
        int count = 0;
        
        while((c = fgetc(f->fp)) != '\n' && c != EOF) {
            count++;
        }
        if(count == 0 && c != EOF) {
            continue;
        }
        if(count == 0 && c == EOF) {
            break;
        }
        fseek(f->fp, -count-1, SEEK_CUR);
        if(c == EOF) count++;
        currentLine = alloc(sizeof(char), count+1);
        for(int i = 0; i < count; i++) {
            currentLine[i] = fgetc(f->fp);
        }
        fgetc(f->fp);
        currentLine[count] = 0;
        f->seek = ftell(f->fp);
        break;
    }
    
    return trim(currentLine);
}
