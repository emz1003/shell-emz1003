#include "shell.h"

int execute_c(char * command);

char ** parse_args(char *line, char * sep){
  char ** ans;
  ans = malloc(1024);
  char *curr = line;
  int count = 0;
  while (curr){
    ans[count] = strsep(&curr, " ");
    count++;
  }
  return ans;
}

void changedir(); //E

void exit(); //K
