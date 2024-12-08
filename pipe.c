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

/* GOPIPE
  - Takes char * (string)
  - Separates string into two pieces around the | pipe operator
  - Executes first string command and pipes output into the input of the second string command
  - Executes second string command
  - No return value
*/
void gopipe(char * args){
  char * token = NULL;
  char * buff[3];
  int i2 = 0;
  char * tb = args;
  while ((token = strsep(&args, "|"))) {
      buff[i2] = token;
      i2++;
  }
  //printf(".%s. and .%s.\n", buff[0], buff[1]); //debug
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
