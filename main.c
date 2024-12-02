#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

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
        printf("%s/ $", cwd);
        fflush(stdout);
        char buffer[100];
        fgets(buffer, sizeof(buffer), stdin);
        char * args[16];
        parse_args(buffer, args);
    }
}