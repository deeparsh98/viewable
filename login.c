#include<stdio.h>
#include<curses.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<stdarg.h>
#include<pthread.h>
#include"curt.h"
#include"common/fetch.h"
#include<curl/curl.h>

#include"../cJSON/cJSON.h"
#include"constants.h"


int oauth(char * email, char * password)
{
    int success = 0;
// char postParams[128];
//  sprintf(postParams, "password=%s&email=%s", password, email);
 
// struct curl_httppost *postParams =NULL;
// struct curl_httppost *lastptr=NULL;
// static const char buf[] = "Expect:";

// curl_formadd(&postParams,
//              &lastptr,
//              CURLFORM_COPYNAME, "email",
//              CURLFORM_COPYCONTENTS, email,
//              CURLFORM_COPYNAME, "password",
//              CURLFORM_COPYCONTENTS, password,
//              CURLFORM_END);


char url[512];
 sprintf(url, "%s?token=%s&password=%s&email=%s", OAUTH_PATH, API_KEY, password, email);
  char *res = fetch(url, NULL, 0);
        cJSON *jsonObj = cJSON_Parse(res);
    if(cJSON_IsString(jsonObj)){
    printw("res: %s", res);
    }
    else{
        cJSON* token = cJSON_GetObjectItem(jsonObj, "token");

    userid = cJSON_GetObjectItem(jsonObj, "uid") -> valueint;
    display_userid = cJSON_GetObjectItem(jsonObj, "duid") -> valueint;
    tk = (char *) malloc(1024 * sizeof(char));
    memcpy(tk, token->valuestring, sizeof(char) * strlen(token->valuestring));
        logged = 1;
    cJSON_Delete(jsonObj);
    success = true;
    }
free(res);

return success;
}
  

int init_login(){
    char s[256], p[256] = "";
    printw("Enter Optmyzr Name\n");
    scanw("%s",s);
    printw("Enter Password\n");
    char ch;
    ch = getch();
    int y,x;
    getyx(stdscr, y, x);
    move(y, x-1);
    delch();
    addch('*');
    while(ch != 10){
        strncat(p, &ch, 1);
        ch = getch();
        
        getyx(stdscr, y, x);
        move(y, x-1);
        delch();
        if(ch != 10)
            addch('*');
    }
    
    return oauth(s,p);
}



void logout(){
    if(tk != NULL && strlen(tk)){
    int sz = strlen(tk) * sizeof(char);
    // printw("size:%d", sz);
    if(sz <= 1024)
        memset(tk, 0, sz);
    free(tk);
    tk = NULL;
    }
    
    logged = 0;
    userid = -1;
    if(current_account != NULL)
        free(current_account);
    display_userid = -1;
}