#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void parse_args( char * line, char ** arg_ary ) {
    char * token = NULL;
    int counter = 0;
    while ((token = strsep(&line, " "))) {
        arg_ary[counter] = token;
        counter++;
    } 
    arg_ary[counter] = NULL;
}