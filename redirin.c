#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include "execute.h"

void redirin(char ** args, int counter){
    printf("Redirecting stdin to file: %s\n", args[counter + 1]); // debug
    int f = open(args[counter+1], O_RDONLY);
    if (f==-1) {
        printerror();
    }
    else {
        int stdin_backup = dup(STDIN_FILENO);
        dup2(f, STDIN_FILENO);
        args[counter] = NULL;
        execute(args[0], args);
        dup2(stdin_backup, STDIN_FILENO);
        close(stdin_backup);
        close(f);
    }
}