#include "shell.h"

int execute(char * line) {
  char ** commands = parse_args(line, ";");
  while(*commands) {
    char ** args = parse_args(*commands, " ");
    int status;
    if (strcmp(*args, "cd"))
    { 
      wait(&status);
      int child = fork();
      if(child == 0){
        execvp(*args, args);
        exit(0);
      } else {
        wait(&status);
      }
    }
    else {
      args++;
      printf("%s\n", *args);
      changedir(*args);
    }

    commands++;
  }
  return 0;

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

void changedir(char *input){
  char s[100];
  chdir(input);
}
