#ifndef __fetch_h__
#define __fetch_h__
#include<stddef.h>
#include<curl/curl.h>


struct url_data {
    size_t size;
    char* data;
};



struct post_data {
    char* name;
    char* value;
};

char* fetchWithToken(char * url, struct curl_httppost* params, int post);
char* fetch(char * url, struct curl_httppost* params, int post);
char* fetchWithHeaders(char * url, struct curl_httppost* params, int post, char* headers);

size_t response_callback(char* buffer, size_t size,
    size_t nitems, void* userdata);

int downloadFile(char* url, char* filepath);
#endif


