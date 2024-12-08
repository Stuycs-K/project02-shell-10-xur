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
  printf(".%s. and .%s.\n", buff[0], buff[1]);
  buff[i2] = NULL;
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
  pclose(fpo);
  pclose(fpi);
}
