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
    return 0;
}