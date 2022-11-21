#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<stdarg.h>
#include<pthread.h>
#include"login.h"
#include<curses.h>
#include"ops/perform.h"
#include"common/utilities.h"

int free_all(){
    logout();
}

int main(int argc, char *argv[]){

    if ( (stdscr = initscr()) == NULL ) {
        /* Error handling here */
        exit(EXIT_FAILURE);
    }
    scrollok(stdscr,TRUE);
    char ** args = (char **)malloc(sizeof(char*) * (argc - 1));

    for(int i = 1; i< argc; i++){
        args[i-1] = argv[i];
    }

    argc --;

    while(1){
        if(!perform(argc, args)){
            free(args);
            break;
        }
        free(args);
        printw("\n");
        char command[1024];
        command[0] = '\0';
        wgetnstr(stdscr, command, 1023);

        args = (char**)malloc(1*sizeof(char*));
        char *token;
    
        /* get the first token */
        token = strtok(command, " ");
        size_t size = 0;
        if(token != NULL){
            args[0] = token;
            size = 1;
        }
        /* walk through other tokens */
        while( 1 ) {
            token = strtok(NULL, " ");
            if(token == NULL){
                break;
            }
            dynamicAddStringArr(args, token, &size);
        }
        argc = (int)size;
    }


free_all();
    getch();
    endwin();
    return 0;
}


