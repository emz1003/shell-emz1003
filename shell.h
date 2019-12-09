#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>

int execute(char * line);
char ** parse_args(char * line, char * sep);
void change_dir( char * input);
void redirect(char** args, int * status);
void fork_run( char ** args, int * status);
