#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int printerror(){
  printf("error number %d\n",errno);
  printf("error: %s\n", strerror(errno));
  return 0;
}

void execute(char * cmd, char ** args) {
    if (!strcmp(cmd, "cd")) {
        if (!args[1]) {
            printf("Missing cd argument");
        }
        if (chdir(args[1])==-1) {
            printerror();
        }
    }
    else {
        pid_t p = fork();
        if (p<0) {
            printerror();
        }
        else if (!p) { //child
            if (execvp(cmd, args)==-1) {
                printf("culprit\n");
                printerror();
            }
        } 
        else { //parent
            wait(NULL);
        }
    }
}