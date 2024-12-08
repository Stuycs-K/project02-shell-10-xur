#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include "execute.h"
#include "redirin.h"
#include "redirout.h"
#include "pipe.h"

/* PARSE ARGS
  - Takes a char * (string) and empty char ** (array of strings)
  - Function separates the string by spaces and puts each substring into the array of strings
  - No return value but array of strings is modified/filled
*/
void parse_args( char * line, char ** arg_ary ) {
    char * token = NULL;
    int counter = 0;
    while ((token = strsep(&line, " "))) {
        arg_ary[counter] = token;
        counter++;
    } 
    arg_ary[counter] = NULL;
} 

/* PRINT ASCII
    - Debug function, takes a char * (string)
    - Prints ascii values corresponding to each character of the string
    - No return value
*/
void printascii(char * line) {
    int counter = 0;
    while (line[counter]) {
        printf("%d\n", line[counter]);
        counter++;
    }
}

/* MAIN
    - No arguments
    - While true loop ensures terminal continues running/prompting until exit or CTRL+D used
    - Returns 0 if executed successfully.
*/
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
            //printf("i see %s\n", buffer); //debug
            //printascii(buffer); //debug
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
                if (strstr(buffsemicolon[i2], "|")) {
                    gopipe(buffsemicolon[i2]);
                }
                else {
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
                                redirin(args, counter);
                                break;
                            }
                        }
                        else if (!strcmp(args[counter], ">")) {
                            redir++;
                            if (!args[counter+1]) {
                                printf("Failed redirect stdout\n");
                                break;
                            }
                            else {
                                redirout(args, counter);
                                break;
                            }
                        }
                        counter++;
                    }
                    if (!redir) {
                        execute(args[0], args);
                    }
                }
            i2++;
            }
        }
        else {
            //for space separation
            if (strstr(buffer, "|")) {
                gopipe(buffer);
            }
            else {
                char * args[16];
                parse_args(buffer, args);
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
                            redirin(args, counter);
                            break;
                        } 
                    }
                    else if (!strcmp(args[counter], ">")) {
                        redir++;
                        if (!args[counter+1]) {
                            printf("Failed redirect stdout\n");
                            break;
                        }
                        else {
                            redirout(args, counter);
                            break;
                        }
                    }
                    counter++;
                }
                if (!redir) {
                    execute(args[0], args);
                }
            }
        }
    }
    return 0;
}