#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "execute.h"

void parse_args( char * line, char ** arg_ary ) {
    char * token = NULL;
    int counter = 0;
    while ((token = strsep(&line, " "))) {
        arg_ary[counter] = token;
        counter++;
    } 
    arg_ary[counter] = NULL;
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
            break;
        }

        //semicolon check
        int semicolcounter = 0;
        int i = 0;
        while (buffer[i]) {
            if (buffer[i]==';') {
                semicolcounter++;
            }
        }
        if (semicolcounter) {
            char * token = NULL;
            char * buffsemicolon[semicolcounter+2];
            int i2 = 0;
            while ((token = strsep(&buffer, ";"))) {
                buffsemicolon[i2] = token;
                i2++;
            } 
            buffsemicolon[i2] = NULL;
            i2 = 0;
            while (buffsemicolon[i2]) {
                char * args[16];
                parse_args(buffsemicolon[i2], args);
                int counter = 0;
                while (args[counter]) {
                    if (!strcmp(args[counter], "|")) {
                        printf("hi\n");
                    }
                    counter++;
                }
                execute(args[0], args);
            }
        }
        else {
            //for space separation
            char * args[16];
            parse_args(buffer, args);
            int counter = 0;
            while (args[counter]) {
                if (!strcmp(args[counter], "|")) {
                    printf("hi\n");
                }
                counter++;
            }
            execute(args[0], args);
        }
    }
    return 0;
}