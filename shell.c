#include "shell.h"

int execute_c(char * command); //E and K

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

void changedir(char *input){ //K
  char s[100];
  printf("The current working directory: %s\n", getcwd(s, 100));
  chdir(input);
  printf("The current working directory: %s\n", getcwd(s, 100));
}
