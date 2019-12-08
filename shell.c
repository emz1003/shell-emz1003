#include "shell.h"

int execute(char * line) {
  char ** commands = parse_args(line, ";");
  while(*commands) {
    char ** args = parse_args(*commands, " "); // string array of cammands
    int status;
    if (strcmp(line, "cd") && strcmp(line, "exit")) // if not cd or exit
    {
      wait(&status);
      int child = fork();
      if(child == 0){
        execvp(*args, args);
        exit(0);
      } else {
        wait(&status);
      }
    } else if (!strcmp(*args, "cd")){ // change directory
      change_dir(*++args);
    } else { // returns true for ending the program
      return 1;
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

void change_dir(char *input){
  char s[100];
  chdir(input);
}

void redirect(char* redir, char *file){
  if (strcmp(redir, ">")){ //then redir is <
    dup(stdin);
    dup2(file, stdin);

  }
  else { //then redir is >
    dup(stdout);
    dup2(file, stdout);
  }
}
