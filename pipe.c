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

void gopipe(char * args){
  char * token = NULL;
  char * buff[3];
  int i2 = 0;
  char * tb = args;
  while ((token = strsep(&args, "|"))) {
      buff[i2] = token;
      i2++;
  }
  buff[i2] = NULL;
  //processing the before pipe
  char * args2[16];
  parse_args(buff[0], args2);
  int counter2 = 0;
  int rediri = 0;
  while (args2[counter2]) {
      if (!strcmp(args2[counter2], "<")) {
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
                rediri++;
                int stdin_backup = dup(STDIN_FILENO);
                dup2(f, STDIN_FILENO);
                args2[counter2] = NULL;
                buff[0][counter2] = '\0';
                close(f);
            }
            break;
          }
      }
      counter2++;
  }
  //processing the after pipe
  char * args3[16];
  parse_args(buff[1], args3);
  int counter3 = 0;
  int rediro = 0;
   while (args3[counter3]) {
      if (!strcmp(args2[counter3], ">")) {
          if (!args2[counter3+1]) {
              printf("Failed redirect stdin\n");
              break;
          }
          else {
            printf("Redirecting stdout to file: %s\n", args3[counter3 + 1]); // debug
            int f = open(args3[counter3+1], O_WRONLY | O_TRUNC);
            if (f==-1) {
                printerror();
            }
            else {
                rediro++;
                int stdout_backup = dup(STDOUT_FILENO);
                dup2(f, STDOUT_FILENO);
                args3[counter3] = NULL;
                buff[1][counter3] = '\0';
                close(f);
            }
            break;
          }
      }
      counter3++;
  }

  FILE * fpo = (popen(buff[0], "r"));
  if (!fpo) {
    printerror();
  }
  FILE * fpi = (popen(buff[1], "w"));
  if (!fpi) {
    printerror();
    pclose(fpo);
  }
  char buffer[128];
  int tread;
    while ((tread = read(fileno(fpo), buffer, sizeof(buffer))) > 0) {
        if (write(fileno(fpi), buffer, tread)==-1) {
            printerror();
            break;
        }
    }
  if (rediri) {
    dup2(stdin_backup, STDIN_FILENO);
    close(stdin_backup);
  }
  if (rediro) {
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);
  }
  pclose(fpo);
  pclose(fpi);
}
