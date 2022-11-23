#ifndef __utilities_h__
#define __utilities_h__
#include"../../cJSON/cJSON.h"

char ** dynamicAddStringArr(char*arr[], char * item, size_t * size);
char * dynamicAddString(char*arr, char item, size_t  size);
char* readFile(char * filename);
void lazyRender(cJSON * jsonArr, char* eles[], int sz, int nol);
int findInArray(char* find, char* strArr[], int size);
char * getResponseForOp(int u, char* op, char* endpoint, char* additionalAttrs);
int downloadFileAtPath(char* url, char* filepath);
void escape(char* query, char* out);
#endif


