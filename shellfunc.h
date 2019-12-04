#include <stdio.h>
#include <stdlib.h>

int execute_c(char * command);
char ** parse_args(char *line, char * sep); //E
void changedir(); //E
void exit(); //K