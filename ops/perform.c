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
#include"reporting.h"
int getIdx(char* str){
    if(strstr(str, "show@{0}") != NULL )
    return 0;
    if(strstr(str, "show@{1}") != NULL )
    return 1;
    if(strstr(str, "show@{2}") != NULL )
    return 2;
    if(strstr(str, "show@{3}") != NULL )
    return 3;
    if(strstr(str, "show@{4}") != NULL )
    return 4;
    if(strstr(str, "show@{5}") != NULL )
    return 5;
    if(strstr(str, "show@{6}") != NULL )
    return 6;
    if(strstr(str, "show@{7}") != NULL )
    return 7;
    if(strstr(str, "show@{8}") != NULL )
    return 8;
    if(strstr(str, "show@{9}") != NULL )
    return 9;
    if(strstr(str, "show@{10}") != NULL )
    return 10;
    if(strstr(str, "show@{11}") != NULL )
    return 11;
}


int handle_reporting(char *argv[], int argvlen){
    if(argvlen > 2){
            if(strcmp(argv[0], "download") == 0)
            {
                int idxTemplate = findInArray("-t", argv, argvlen);
                if(idxTemplate == -1)
                    idxTemplate = findInArray("--template", argv, argvlen);
                int idxMulti = findInArray("-m", argv, argvlen);
                if(idxMulti == -1)
                    idxMulti = findInArray("--multi", argv, argvlen);
                
                int orient_l = findInArray("--orient-l", argv, argvlen);

                int multi = 0;
                if(idxMulti > 0){
                    multi = 1;
                }
                char o[2] = "p";
                if(orient_l > 0)
                    o[0] = 'l';


                char* acc = current_account;
                if(!multi){
                    int idxAcc = findInArray("-ac", argv, argvlen);
                    if(idxAcc == -1)
                        idxAcc = findInArray("--account", argv, argvlen);
                    if((idxAcc == -1 || idxAcc == argvlen - 1 ) && current_account == NULL){
                        printw("No Account set. You might want to try with `-ac <accountid>` or simply `--multi`\n", argv[1]);
                        return 1;
                    }
                    if(current_account == NULL){
                        acc = argv[idxAcc+1];
                    }
                }
                char* allAttrs[] = {"-m","--multi","--orient-l","-ac","--account"};
                int minidx = argvlen;
                for(int i = 0; i < 5; i++){
                    int curIdx = findInArray(allAttrs[i], argv, argvlen);
                    if(curIdx > idxTemplate){
                        if(curIdx<minidx)
                            minidx = curIdx;
                    }
                }

                if(idxTemplate > 0 && idxTemplate < (minidx - 1)){
                    char templateName[1024] = "";
                    for(int i = idxTemplate + 1; i < minidx; i++){
                        if(i == idxTemplate + 1)
                            strcat(templateName, argv[i]);
                        else{
                            strcat(templateName, " ");
                            strcat(templateName, argv[i]);
                        }
                    }
                    // printw("Requesting download...\n");
                    download(userid, acc, o, templateName, multi);
                    return 1;
                }
            }
        }

        if(argvlen > 0){
            if(strcmp(argv[0], "templates") == 0)
            {
                int idxMulti = findInArray("-m", argv, argvlen);
                if(idxMulti == -1)
                    idxMulti = findInArray("--multi", argv, argvlen);
                int multi = 0;
                if(idxMulti > 0){
                    multi = 1;
                }
                templates(userid, multi);
                return 1;
            }
        }

        if(argvlen > 1)
            printw("Invalid `reporting`. Try `reporting download -t <template> [--multi]`\n", argv[1]);
        else
            printw("Invalid `reporting`. Try `reporting templates [--multi]`\n", argv[1]);
        return 1;
}

int handle_express(char *argv[], int argvlen){
    if(argvlen > 2){
            if(strcmp(argv[0], "show") == 0 || (strstr(argv[0], "show@{") != NULL))
            {
                int suggToShowIdx = -1;
                if(strstr(argv[0], "show@{") != NULL){
                    suggToShowIdx = getIdx(argv[0]);
                }

                int idxTool = findInArray("--tool", argv, argvlen);
                

                char* acc = current_account;
                int idxAcc = findInArray("-ac", argv, argvlen);
                if(idxAcc == -1)
                    idxAcc = findInArray("--account", argv, argvlen);
                if((idxAcc == -1 || idxAcc == argvlen - 1 ) && current_account == NULL){
                    printw("No Account set. You might want to try with `-ac <accountid>` or simply `--multi`\n", argv[1]);
                    return 1;
                }
                if(current_account == NULL)
                    acc = argv[idxAcc+1];
                // }
                // char* allAttrs[] = {"-m","--multi","--orient-l","-ac","--account"};
                // int minidx = argvlen;
                // for(int i = 0; i < 5; i++){
                //     int curIdx = findInArray(allAttrs[i], argv, argvlen);
                //     if(curIdx > idxTemplate){
                //         if(curIdx<minidx)
                //             minidx = curIdx;
                //     }
                // }

                // if(idxTool > 0 && idxTool < (argvlen - 1)){
                //     char tool[1024] = "";
                //     for(int i = idxTemplate + 1; i < minidx; i++){
                //         if(i == idxTemplate + 1)
                //             strcat(templateName, argv[i]);
                //         else{
                //             strcat(templateName, " ");
                //             strcat(templateName, argv[i]);
                //         }
                //     }
                //     // printw("Requesting download...\n");
                //     download(userid, acc, o, templateName, multi);
                //     return 1;
                // }

                 if(idxTool > 0 && idxTool < (argvlen - 1)){
                    suggestions(userid, acc, argv[idxTool + 1], suggToShowIdx);
                    return 1;
                }
            }
        }

        printw("Invalid `express`. Try `express show --tool <toolname>`\n", argv[1]);
        return 1;
}


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

    if(strcmp(command, "reporting") == 0){
        //reporting
        return handle_reporting(argv, argvlen);
    }

    if(strcmp(command, "express") == 0){
        //reporting
        return handle_express(argv, argvlen);
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

