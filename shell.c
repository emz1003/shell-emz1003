#include "shell.h"

int execute(char * line) {
  char ** commands = parse_args(line, ";");
  while(*commands) {
    char ** args = parse_args(*commands, " ");
    int status;
    wait(&status);
    if (is_forkable(*args))
    {
      int child = fork();
      if(child == 0){
        execvp(*args, args);
        exit(0);
      } else {
        wait(&status);
      }
    }
    else
    {
      printf("not implemented yet\n");
      execvp(*args, args);
    }

    commands++;
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

void changedir(char *input){ //K
  char s[100];
  printf("The current working directory: %s\n", getcwd(s, 100));
  chdir(input);
  printf("The current working directory: %s\n", getcwd(s, 100));
}
