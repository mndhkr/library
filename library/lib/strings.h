
#include <stdbool.h>

typedef char* String;
typedef char* string;



/* Returns a newly allocated string. The user is 
 * responsible to free it */
String strConcat(char* s1, char* s2);

int strLength(char* s);

bool strEquals(char* s1, char *s2);

// end esclusivo
String substring(char* s, int start, int end);

int strIndex(char* str, char* pattern);

bool strIn(char* str, char* pattern);

String *strSplitChars(char* s, char *sep);

String trim(String str);
string strCopy(string str);
