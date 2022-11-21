#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<stdarg.h>
#include<pthread.h>
#include<curses.h>
#include"basic.h"
#include"../common/utilities.h"
#include"../curt.h"
#include"../login.h"
#include"../common/soundex.h"

int callcommand(char * command, char *argv[], int argvlen){

    if(strcmp(command, "exit") == 0){
        return 0;
    }
    if(strcmp(command, "--help") == 0 || strcmp(command, "help") == 0){
        char * content = readFile("/mnt/c/viewable/viewable/README.md");
        if(content == NULL){
            printw("Unknown issue while running help command.");
        }
        if(strlen(content) > 0){
           printw("\n%s\n",content);
        }
           free(content);
        if(strcmp(command, "--help") == 0)
            return 0;
        return 1;
    }
    if(strcmp(command, "accounts") == 0){
        //accounts list
        accounts_list(userid);
        return 1;
    }

    if(strcmp(command, "current") == 0){
        if(argvlen > 1){
            if((strcmp(argv[0], "--account") == 0 || strcmp(argv[0], "-ac") == 0)
            && (strcmp(argv[1], "--user") == 0 || strcmp(argv[1], "-u") == 0)
            || (strcmp(argv[1], "--account") == 0 || strcmp(argv[1], "-ac") == 0)
            && (strcmp(argv[0], "--user") == 0 || strcmp(argv[0], "-u") == 0)){
                printw("Current User: %d w/ Parent: %d\n", display_userid, userid );
                printw("Current Account: %s\n", current_account);
            }
        }
        else if(argvlen > 0){
            if(strcmp(argv[0], "--account") == 0 || strcmp(argv[0], "-ac") == 0){
                printw("Current Account: %s\n", current_account);
            }
            else if(strcmp(argv[0], "--user") == 0 || strcmp(argv[0], "-u") == 0){
                printw("Current User: %d w/ Parent: %d\n", display_userid, userid );
            }
            else
                printw("Invalid `current`. Should be with one of `-u` or `-ac`\n", argv[1]);
        }
        else{
            printw("Invalid `current`. Should be with one of `-u` or `-ac`\n", argv[1]);
        }
        return 1;
    }

    if(strcmp(command, "set") == 0){
        if(argvlen > 1){
            if(strcmp(argv[0], "--account") == 0 || strcmp(argv[0], "-ac") == 0){
                if(check_in_accounts(argv[1], userid)){
                    current_account = (char*) malloc(sizeof(char)*16);
                    strcpy(current_account, argv[1]);
                    printw("Done.\n");
                }
                else{
                    printw("Account `%s` is not linked with Optmyzr.\n", argv[1]);
                }
            }
            else{
                printw("Not a valid set attribute. Try `--account or -ac`\n", argv[1]);
            }
        }
        else{
            printw("Invalid set. Should be of form `set -<attr> <value>`\n", argv[1]);
        }
        return 1;
    }

    char * maybe = findRelated(command);
    if(maybe != NULL) printw("Did you mean `%s`? Try `help` or optmyzr --help or optmyzr -h :)\n", maybe);
    else printw("Invalid command `%s`. Try `help` or optmyzr --help or optmyzr -h :)\n", command);
    return 1;

}


int perform(int argc, char *args[]){
    if(argc > 0){
        if(strcmp(args[0], "--help") == 0 || strcmp(args[0], "-h") == 0){
            return callcommand("--help", NULL, argc);
        }
    }
    if(tk == NULL || strlen(tk) <= 0){
        if(init_login()){
            printw("Login Successful!\n\n");
        }
        else{
            printw("Log In Failed! Please check email and password");
            return 0;
        }
    }
    // printw("%d %s", argc, args[0]);
    if(argc > 0){
        char ** ptr = args + 1;
        return callcommand(args[0], ptr, argc - 1);
    }
    else{
        printw("Try `help` or optmyzr --help or optmyzr -h :)\n");
        return 1;
    }
    return 1;
}

