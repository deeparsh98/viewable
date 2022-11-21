#include<stdio.h>
#include<math.h>
#include<time.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"soundex.h"
#include"constants.h"


void soundex(char* name, char* s)
{
    int si = 1;
    char c;

    //                 ABCDEFGHIJKLMNOPQRSTUVWXYZ
    char mappings[] = "01230120022455012623010202";

    s[0] = toupper(name[0]);

    for(int i = 1, l = strlen(name); i < l; i++)
    {
        c = toupper(name[i]) - 65;

        if(c >= 0 && c <= 25)
        {
            if(mappings[c] != '0')
            {
                if(mappings[c] != s[si-1])
                {
                    s[si] = mappings[c];
                    si++;
                }

                if(si > 3)
                {
                    break;
                }
            }
        }
    }

    if(si <= 3)
    {
        while(si <= 3)
        {
            s[si] = '0';
            si++;
        }
    }
}

char* findRelated(char * toCheck)
{
    char sorig[] = "     ";
    char scheck[] = "     ";
    soundex(toCheck, scheck);
    for(int i = 0; i < commC; i++)
    {
        soundex(commands[i], sorig);
        if(strcmp(sorig, scheck) == 0){
            return commands[i];
        }
    }
    return NULL;
}