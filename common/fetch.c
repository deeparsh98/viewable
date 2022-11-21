#include<stdio.h>
#include<curses.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<stdarg.h>
#include<pthread.h>
#include"../curt.h"
#include"fetch.h"

#include<curl/curl.h>


extern int SKIP_PEER_VERIFICATION;
extern int SKIP_HOSTNAME_VERIFICATION;
const int MAX_DATA_SIZE = 16384;


size_t write_data(void *ptr, size_t size, size_t nmemb, struct url_data *data) {
    size_t index = data->size;
    size_t n = (size * nmemb);
    char* tmp;
    data->size += (size * nmemb);
#ifdef DEBUG
    fprintf(stderr, "data at %p size=%ld nmemb=%ld\n", ptr, size, nmemb);
#endif
    tmp = realloc(data->data, data->size + 1); /* +1 for '\0' */

    if(tmp) {
        data->data = tmp;
    } else {
        if(data->data) {
            free(data->data);
        }
        fprintf(stderr, "Failed to allocate memory.\n");
        return 0;
    }

    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';
    return size * nmemb;
}

char* fetchWithHeaders(char * url, struct curl_httppost* params, int post, char* headers)
{
  CURL *curl;
  CURLcode res;
 
 int fail = 0;
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
  struct url_data data;
    data.size = 0;
    data.data = malloc(1024); /* init buffer */
    if(NULL == data.data) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }

    data.data[0] = '\0';
  if(curl) {

// struct curl_httppost *formpost=NULL;
// struct curl_httppost *lastptr=NULL;

// char * postParams = (char*) malloc(sizeof(params));
// int len = sizeof(postParams) / sizeof(postParams[0]);
// char **array = malloc(len * 2 * sizeof(char *));  // twice as we need two flag variables for 

// for( int i = 0; i < 2 * len; i += 2){
//     array[i] = malloc((sizeof(postParams) / sizeof(postParams[0])) * sizeof(char *));

// }

struct curl_slist *headerlist=NULL;

    curl_easy_setopt(curl, CURLOPT_URL, url);
 
if(post){
    
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
    // printw("%s",params);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, params);
}
if(headers != NULL && strlen(headers)){
headerlist = curl_slist_append(headerlist, headers);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
}
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK){

      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }
    else{
        //printw("%s",data.data);
    }
    
    
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  else{
    free(data.data);
    data.data = "error";
  }
 
  curl_global_cleanup();
 
  return data.data;
}

char* fetch(char * url, struct curl_httppost* params, int post)
{
  return fetchWithHeaders(url, params, post, NULL);
}


char* fetchWithToken(char * url, struct curl_httppost* params, int post)
{
  char buf[2056];

  sprintf(buf, "Content-Language:%s", tk);

  return fetchWithHeaders(url, params, 0, buf);
}