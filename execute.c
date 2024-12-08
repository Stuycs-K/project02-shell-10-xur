#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*PRINTERROR
    - No arguments, returns 0 representing successful execution
    - Prints error number and message based on errno set by other functions
*/
int printerror(){
  printf("error number %d\n",errno);
  printf("error: %s\n", strerror(errno));
  return 0;
}

/*EXECUTE
    - Takes char * (string) and char ** (array of strings)
    - Executes command in string and utilizes args for command from array of strings
    - Command 'cd' is specially handled, otherwise commands passed into execvp
    - Forks into child and parent processes
    - No return value
*/
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
