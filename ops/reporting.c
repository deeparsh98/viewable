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
#include<time.h>
#include<unistd.h>

int templates(int u, int multi){
    char attrs[256];
    sprintf(attrs, "&isMulti=%d", multi);
    
    char* res = getResponseForOp(u, report_templates, OPTPROCESSOR_DBOPS_API, attrs);
    //free(tm);
    
    char* url = NULL;
    int error = 0;
    
    //     printw("res: %s", res);
    cJSON *jsonObj = cJSON_Parse(res);
    if(cJSON_IsString(jsonObj)){
        printw("res: %s", res);
        }
        else{
            //printw("\n%s",res);
            char *eles[] = { "name" };
            int count = 1;
            
            for(int i = 0; i< count; i++){
                printw("%s ",eles[i]);
            }
            printw("\n");
            lazyRender(jsonObj, eles, count, 5);
        }

    free(res);
    cJSON_Delete(jsonObj);



    return 0;
}

int download(int u, char* acc, char* o, char* t, int multi)
{
    time_t timer = time(NULL);
    struct tm* tm = localtime(&timer);
    char attrs[256];
    char date[16];
    char template[128];
    escape(t,template);
    sprintf(date, "%d_%d_%d", tm->tm_mday, tm->tm_mon, tm->tm_year);
    sprintf(attrs, "&accountId=%s&orient=%s&isMulti=%d&template=%s&currentDate=%s", acc, o, multi, template, date);
    
    char* res = getResponseForOp(u, report_pdf_path, OPTPROCESSOR_DBOPS_API, attrs);
    //free(tm);
    
    char* url = NULL;
    int error = 0;
    
    //     printw("res: %s", res);
    cJSON *jsonObj = cJSON_Parse(res);
    if(cJSON_IsString(jsonObj)){
        printw("res: %s", res);
        }
        else{
            url = cJSON_GetObjectItem(jsonObj, "url")->valuestring;
            error = cJSON_GetObjectItem(jsonObj, "error")->valueint;
        }

    free(res);
    if(error)
        printw("Unknown Error while requesting download!");
    else{
        // printw("Generating the report..\n");
        
        char filepath[FILENAME_MAX];
        
        sprintf(filepath, "/mnt/c/viewable/report_%s.pdf", date);
        for(int i = 0; i< 60; i++){
            // printw(".");
            sleep(2);
            if(downloadFileAtPath(url, filepath)){
                break;
            }
        }
        
        if(downloadFileAtPath(url, filepath))
            printw("Done. Find your report inside `c/viewable/report_%s.pdf`\n", date);
        else
            printw("Failed. Error while downloading the report\n", filepath);
        
    }

    cJSON_Delete(jsonObj);



    return 0;
}
