#include "shell.h"

int execute(char * line) {
  char ** commands = parse_args(line, ";");
  while(*commands) {
    char ** args = parse_args(*commands, " ");
    commands++;
    if (is_forkable(*args))
    {
      printf("it's forkable\n");
      int status;
      pid_t child = fork();
      wait(&status);
      execvp(*args, args);
      exit(child);
    }
    else
    {
      printf("not implemented yet\n");
    }
  }
  return 0;

}

int is_forkable(char * arg) {
  return strcmp(arg, "cd") || strcmp(arg, "exit");
}

char ** parse_args(char *line, char * sep){
  char ** ans;
  ans = malloc(1024);
  char *curr = line;
  int count = 0;
  while (curr){
    ans[count] = strsep(&curr, sep);
    count++;
  }
  return ans;
}

void changedir(); //E

void exit(); //K
