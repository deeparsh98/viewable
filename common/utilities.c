#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<stdarg.h>
#include<pthread.h>
#include<curses.h>
#include"../../cJSON/cJSON.h"
#include"fetch.h"

char ** dynamicAddStringArr(char*arr[], char * item, size_t* size){
    arr = realloc(arr, (*size * sizeof(char*))+ sizeof(char*));
    arr[*size] = item;
    (*size) ++;
    return arr;
}

char * dynamicAddString(char*arr, char item, size_t* size){
    arr = realloc(arr, *size + sizeof(char));
    arr[*size] = item;
    (*size) ++;
    return arr;
}

char* readFile(char * filename){
    FILE* ptr;
    char ch;
    ptr = fopen(filename, "r");
 
    if (NULL == ptr) {
        printw("Error: Can't open file : %s\n", filename);
        return NULL;
    }
 
 
    char * str = (char*) malloc(sizeof(char) * 0);
    size_t size = 0;
    while (!feof(ptr)) {
        ch = fgetc(ptr);
        str = dynamicAddString(str, ch, &size);
    }
    str = dynamicAddString(str, '\0', &size);
    fclose(ptr);
    return str;
}

int findInArray(char* find, char* strArr[], int size){
    for(int i=0; i<size; i++){
        if(strcmp(find, strArr[i])==0){
            return i;
        }
    }
    return -1;
}


int downloadFileAtPath(char* url, char* filepath){
    
    int succ = downloadFile(url, filepath);
    if(succ){
        char* content = readFile(filepath);
        if (strstr(content, "AccessDenied") != NULL || strstr(content, "<Error>") != NULL) {
            remove(filepath);
            return 0;
        }
    }
    return succ;
}

char * getResponseForOp(int u, char* op, char* endpoint, char* additionalAttrs){
  char url[512];
  sprintf(url, "%s?operation=%s&userid=%d%s", endpoint, op, u, additionalAttrs);
  
  char *res = fetchWithToken(url, NULL, 0);
  return res;
}

void escape(char* query, char* out){
    CURL *curl = curl_easy_init();
    if(curl) {
    char *output = curl_easy_escape(curl, query, 0);
    if(output) {
        sprintf(out, "%s", output);
        curl_free(output);
    }
    curl_easy_cleanup(curl);
    }
}

void lazyRender(cJSON * jsonArr, char* eles[], int sz, int nol){
    int idx = 0;
    cJSON* i;
    for(i = (jsonArr != NULL) ? (jsonArr)->child : NULL; i != NULL && idx < nol; i = i->next){ 
        int j = 0;
        while(j<sz){
            printw("%s ", cJSON_GetObjectItem(i, eles[j])->valuestring);
            j++;
        }
        printw("\n");
        idx ++;
    }

    char ch = getch();
    while(ch != 'q' && ch != 'Q' && i -> next != NULL){
        int j = 0;
        while(j<sz){
            printw("%s ", cJSON_GetObjectItem(i, eles[j])->valuestring);
            j++;
        }
        
        printw("\n");
        ch = getch();
        i = i-> next;
    }
    if(ch == 'q'){
        int y,x;
        getyx(stdscr, y, x);
        move(y, x-1);
        delch();
        printw("--stopped\n");
    }

    if(ch != 'q' && ch != 'Q' && i -> next == NULL){
        printw("No more Rows: Press any key...");
        getch();
    }
}

// void lazyRender2(cJSON * jsonArr, int sz, int nol){
//     int idx = 0;
//     cJSON* i;
//     for(i = (jsonArr != NULL) ? (jsonArr)->child : NULL; i != NULL && idx < nol; i = i->next){ 
//         int j = 0;
//         while(j<sz){
//             printw("%s ", cJSON_GetObjectItem(i, eles[j])->valuestring);
//             j++;
//         }
//         printw("\n");
//         idx ++;
//     }

//     char ch = getch();
//     while(ch != 'q' && ch != 'Q' && i -> next != NULL){
//         int j = 0;
//         while(j<sz){
//             printw("%s ", cJSON_GetObjectItem(i, eles[j])->valuestring);
//             j++;
//         }
        
//         printw("\n");
//         ch = getch();
//         i = i-> next;
//     }
//     if(ch == 'q'){
//         int y,x;
//         getyx(stdscr, y, x);
//         move(y, x-1);
//         delch();
//         printw("--stopped\n");
//     }

//     if(ch != 'q' && ch != 'Q' && i -> next == NULL){
//         printw("No more Rows: Press any key...");
//         getch();
//     }
// }