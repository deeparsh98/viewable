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



int accounts_list(int u)
{
  char* res = getResponseForOp(u, accs_list_op, OPTPROCESSOR_DBOPS_API, "");
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
      lazyRender(jsonObj, eles, count, 5);
    }

  cJSON_Delete(jsonObj);
  free(res);
  return 0;
}

int suggestions(int u, char* acc, char* toolName, int i)
{
  char attrs[256];
    sprintf(attrs, "&accountId=%s&tool=%s", acc, toolName);
  char* res = getResponseForOp(u, express_sugg_path, OPTPROCESSOR_DBOPS_API, attrs);
  // printw("data fetched: %s",res);
  cJSON *jsonObj = cJSON_Parse(res);
  if(cJSON_IsString(jsonObj)){
    printw("res: %s", res);
    }
    else{
      printw("\n");
      
    // printw("res: %s", res);
      cJSON * element;
      if(cJSON_GetObjectItem(jsonObj, "error")->valueint){
        printw("Error: %s\n", cJSON_GetObjectItem(jsonObj, "message")->valuestring);
      }
      else{
        cJSON* element;
        int idx = 0;
        cJSON * suggs = cJSON_GetObjectItem(jsonObj, "suggestions");
        cJSON_ArrayForEach(element, suggs){
          if(i == -1 || i == idx){
            
            cJSON* inner;
              cJSON_ArrayForEach(inner, element){
                printw("%s : %s", inner->string, inner->valuestring);
                printw("\n");
            }
            if(i==-1){
              printw("Tap for next suggestion...");
              getch();
            }
            printw("\n");
          }
          idx++;
        }
      }
    }

  cJSON_Delete(jsonObj);
  free(res);
  return 0;
}

int check_in_accounts(char* acc_id, int u){
  char* res = getResponseForOp(u, accs_list_op, OPTPROCESSOR_DBOPS_API, "");
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
