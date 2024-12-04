#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "execute.h"

int printerror(){
  printf("error number %d\n",errno);
  printf("error: %s\n", strerror(errno));
  return 0;
}

void parse_args( char * line, char ** arg_ary ) {
    char * token = NULL;
    int counter = 0;
    while ((token = strsep(&line, " "))) {
        arg_ary[counter] = token;
        counter++;
    } 
    arg_ary[counter] = NULL;
}

void printascii(char * line) {
    int counter = 0;
    while (line[counter]) {
        printf("%d\n", line[counter]);
        counter++;
    }
}

int main(){
    while (1) {
        char cwd[100];
        getcwd(cwd, sizeof(cwd));
        printf("\n%s/ $ ", cwd);
        fflush(stdout);
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin)==NULL) {
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strcmp(buffer, "exit") == 0) {
            printf("i see %s\n", buffer); //debug
            printascii(buffer); //debug
            break; //weird behavior where if errno2 occurs, must type exit twice to exit. tried printing to debug but doesnt help.
        }

        //semicolon check
        int semicolcounter = 0;
        int i = 0;
        while (buffer[i]) {
            if (buffer[i]==';') {
                semicolcounter++;
            }
            i++;
        }
        if (semicolcounter) {
            char * token = NULL;
            char * buffsemicolon[semicolcounter+2];
            int i2 = 0;
            char * tb = buffer;
            while ((token = strsep(&tb, ";"))) {
                buffsemicolon[i2] = token;
                i2++;
            } 
            buffsemicolon[i2] = NULL;
            i2 = 0;
            while (buffsemicolon[i2]) {
                char * args[16];
                parse_args(buffsemicolon[i2], args);
                int counter = 0;
                int redir = 0;
                while (args[counter]) {
                    if (!strcmp(args[counter], "<")) {
                        redir++;
                        if (!args[counter+1]) {
                            printf("Failed redirect stdin\n");
                            break;
                        }
                        else {
                            int f = open(args[counter+1], O_RDONLY);
                            if (f==-1) {
                                printerror();
                                break;
                            }
                            int stdin = STDIN_FILENO;
                            int stdin2 = dup(stdin);
                            dup2(f, stdin);
                            char buffer2[100];
                            if (fgets(buffer2, sizeof(buffer2), stdin)==NULL) {
                                break;
                            }
                            buffer2[strcspn(buffer2, "\n")] = '\0';
                            if (strcmp(buffer2, "exit") == 0) {
                                printf("i see %s\n", buffer2); //debug
                                printascii(buffer2); //debug
                                break; //weird behavior where if errno2 occurs, must type exit twice to exit. tried printing to debug but doesnt help.
                            }
                            char * args2[16];
                            parse_args(buffer2, args2);
                            int counter = 0;
                            while (args2[counter]) {
                                /*if (!strcmp(args2[counter], "|")) {
                                    printf("hi\n");
                                }*/
                                counter++;
                            }
                            execute(args2[0], args2);
                            fflush(stdin);//not needed when a child process exits, becaue exiting a process will flush automatically.
                            dup2(stdin2, stdin); //sets the stdout entry to backup_stdout, which is the original stdout
                        }
                    }
                    /*if (!strcmp(args[counter], "|")) {
                        printf("hi\n");
                    }*/
                    counter++;
                }
                execute(args[0], args);
                i2++;
            }
        }
        else {
            //for space separation
            char * args[16];
            parse_args(buffer, args);
            int counter = 0;
            while (args[counter]) {
                /*if (!strcmp(args[counter], "|")) {
                    printf("hi\n");
                }*/
                counter++;
            }
            execute(args[0], args);
        }
    }
    return 0;
}