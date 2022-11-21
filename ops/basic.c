#include<stdio.h>
#include<curses.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<stdarg.h>
#include<pthread.h>
#include"../curt.h"
#include"../common/fetch.h"
#include<curl/curl.h>

#include"../../cJSON/cJSON.h"
#include"constants.h"
#include"operations.h"
#include"../common/utilities.h"


char * getAccsResponse(int u){
  char url[512];
  sprintf(url, "%s?operation=%s&userid=%d", OPTPROCESSOR_DBOPS_API, accs_list_op, u);
  char *res = fetchWithToken(url, NULL, 0);
  return res;
}

int accounts_list(int u)
{
  char* res = getAccsResponse(u);
  // printw("data fetched: %s",res);
  cJSON *jsonObj = cJSON_Parse(res);
  if(cJSON_IsString(jsonObj)){
    printw("res: %s", res);
    }
    else{
      printw("\n");
      // cJSON * element;
      // cJSON_ArrayForEach(element, jsonObj){
      //   printw("Id: %s\n", cJSON_GetObjectItem(element, "AccountId")->valuestring);
      // }
      char *eles[] = { "AccountId", "AccountName", "AssociatedEmail" };
      int count = 3;
      
      for(int i = 0; i< count; i++){
        printw("%s ",eles[i]);
      }
      printw("\n");
      lazyRender(jsonObj, eles, count, 2);
    }

  cJSON_Delete(jsonObj);
  free(res);
  return 0;
}

int check_in_accounts(char* acc_id, int u){
  char* res = getAccsResponse(u);
  // printw("data fetched: %s",res);
  cJSON *jsonObj = cJSON_Parse(res);
  if(cJSON_IsString(jsonObj)){
    return 0;
    }
    else{
      cJSON * element;
      cJSON_ArrayForEach(element, jsonObj){
        if(strcmp(acc_id, cJSON_GetObjectItem(element, "AccountId")->valuestring) == 0){
          return 1;
        }
      }
    }

  cJSON_Delete(jsonObj);
  free(res);
  return 0;
}
