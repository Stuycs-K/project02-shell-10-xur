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

void parse_args( char * line, char ** arg_ary ) {
    char * token = NULL;
    int counter = 0;
    while ((token = strsep(&line, " "))) {
        arg_ary[counter] = token;
        counter++;
    }
    arg_ary[counter] = NULL;
}

void pipe(char * args){
  char * token = NULL;
  char * buff[3];
  int i2 = 0;
  char * tb = args;
  while ((token = strsep(&args, "|"))) {
      buff[i2] = token;
      i2++;
  }
  buff[i2] = NULL;
  i2 = 0;
  //Process Before pipe
  char * args2[16];
  parse_args(buff[i2], args2);
  int counter2 = 0;
  int redir = 0;
  while (args2[counter2]) {
      if (!strcmp(args2[counter2], "<")) {
          redir++;
          if (!args2[counter2+1]) {
              printf("Failed redirect stdin\n");
              break;
          }
          else {
            printf("Redirecting stdin to file: %s\n", args2[counter2 + 1]); // debug
            int f = open(args2[counter2+1], O_RDONLY);
            if (f==-1) {
                printerror();
            }
            else {
                int stdin_backup = dup(STDIN_FILENO);
                dup2(f, STDIN_FILENO);
                args2[counter2] = NULL;
                execute(args2[0], args2); //THIS CANT BE EXECUTE, MUST BE CUSTOM BEHAVIOR
                dup2(stdin_backup, STDIN_FILENO);
                close(stdin_backup);
                close(f);
            }
              break;
          }
      }
      counter2++;
  }
  if (!redir) {
      execute(args2[0], args2); //THIS CANT BE EXECUTE, MUST BE CUSTOM BEHAVIOR
  }
  i2++;
}
