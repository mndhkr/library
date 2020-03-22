
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "stdinclude.h"



/* Returns a newly allocated string. The user is 
 * responsible to free it */
String strConcat(char* s1, char* s2)
{
    int length = strlen(s1) + strlen(s2) + 1;
    String str = (String)calloc(length, sizeof(char));
    sprintf(str, "%s%s", s1, s2);
    return str;
}

int strLength(char* s) {
    if(s == null)
        return 0;
    return strlen(s);
}

bool strEquals(char* s1, char *s2) {
    return strcmp(s1, s2) == 0;
}

// end esclusivo
String substring(char* s, int start, int end) {
    int length = strlen(s);
    String newstring = null;
    if(start >= 0 && start < end && end <= length) {
        int newlen = end - start;
        newstring = calloc(newlen, sizeof(char));
        int i = 0;
        for(i = start; i < end; i++) {
            newstring[i - start] = s[i];
        }
        newstring[i-start] = '\0';
    }
    return newstring;
}

int strIndex(char* str, char* pattern) {
    int p_len = strLength(pattern);
    int s_len = strLength(str);
    for(int i = 0; i < s_len; i++) {
        if(p_len+i <= s_len) {
            char *sub = substring(str, i, strLength(pattern)+i);
            if(strEquals(sub, pattern)) {
                return i;
            }
        }
    }
    return -1;
}

bool strIn(char* str, char* pattern) {
    if(strIndex(str, pattern) >= 0) {
        return true;
    } else {
        return false;
    }
}

// Returns array of trimmed splits on each char of <code>sep</code>
String *strSplitChars(char* s, char *sep) {
    int count = 1;
    char *str = s;
    for(int i = 0; i < strLength(str); i++) {
        for(int j = 0; j < strLength(sep); j++) {
            if(str[i] == sep[j]) {
                count++;
                break;
            }
        }
    }
    //printf("count: %d\n", count);
    char** strings = calloc(count+1, sizeof(char*));
    count = 0;

    while(1) {
        int min = INT_MAX;
        int sep_index;
        for(int j = 0; j < strLength(sep); j++) {
            sep_index = strIndex(str, substring(sep, j, j+1));
            if(sep_index >= 0 && sep_index < min) min = sep_index;
        }
        if(min == INT_MAX) break;
        sep_index = min;
        //printf("sep_index: %u\n", sep_index);
        char* sub = substring(str, 0, sep_index);
        sub = trim(sub);
        if(sub == null)
        {
            str = substring(str, sep_index+1, strLength(str));
            continue;
        }
        //printf("sub: %s\n", sub);
        strings[count++] = sub;
        if(sep_index+1 < strLength(str)) {
            str = substring(str, sep_index+1, strLength(str));
            str = trim(str);
        } else {
            str = 0;
            break;
        }
        //printf("str: %s\n", str);
    }
    strings[count] = str;

    strings[++count] = 0; // BUG?
    return strings;
}

String trim(String str) {
    if(str == null) return null;
    int start = 0;
    int end = strLength(str);
    while(str[start] == ' ' || str[start] == '\n') {
        start++;
    }
    while(str[end-1] == ' '|| str[end-1] == '\n') {
        end--;
    }
    return substring(str, start, end);
}

string strCopy(string str) {
    string buffer = alloc(strLength(str)+1, sizeof(char));
    sprintf(buffer, "%s", str);
    return buffer;
}
