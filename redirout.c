#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include "execute.h"

/*REDIROUT
    - Takes char ** (array of strings) and int counter
    - Locates file to which stdout should be redirected using counter and array of strings
    - Sets stdout as the file, then executes, then reverts stdout
    - No return value
*/
void redirout(char ** args, int counter){
    //printf("Redirecting stdout to file: %s\n", args[counter + 1]); // debug
    int f = open(args[counter+1], O_WRONLY | O_TRUNC);
    if (f==-1) {
        printerror();
    }
    else {
        int stdout_backup = dup(STDOUT_FILENO);
        dup2(f, STDOUT_FILENO);
        args[counter] = NULL;
        execute(args[0], args);
        dup2(stdout_backup, STDOUT_FILENO);
        close(stdout_backup);
        close(f);
    }
}
