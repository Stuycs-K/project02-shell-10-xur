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
        char * home = getenv("HOME");
        if (!args[1]) {
            if (chdir(home)==-1) {
                printerror();
            }
        }
        else if (chdir(args[1])==-1) {
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
                printerror();
            }
        } 
        else { //parent
            wait(NULL);
        }
    }
}