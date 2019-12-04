#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

int execute_c(char * command);
char ** parse_args(char *line, char * sep); //K
void changedir(); //E
void exit(); //K
