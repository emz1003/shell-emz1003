#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

int execute(char * line);
char ** parse_args(char *line, char * sep); //K
void changedir(); //E
int is_forkable(char * arg);
