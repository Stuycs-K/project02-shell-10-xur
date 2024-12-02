#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

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