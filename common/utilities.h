#ifndef __utilities_h__
#define __utilities_h__
#include"../../cJSON/cJSON.h"

char ** dynamicAddStringArr(char*arr[], char * item, size_t * size);
char * dynamicAddString(char*arr, char item, size_t  size);
char* readFile(char * filename);
void lazyRender(cJSON * jsonArr, char* eles[], int sz, int nol);
#endif


