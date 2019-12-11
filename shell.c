#include "shell.h"

int execute(char * line) {
  char ** commands = parse_args(line, ";");
  while(*commands) {
    char *command = calloc(1024, sizeof(char));
    strcpy(command, *commands);
    char ** args = parse_args(command, " "); // string array of cammands
    int status;
    if (strcmp(*args, "cd") && strcmp(*args, "exit") && !is_redir(args) && !is_pipe(args)) // if not cd or exit
    {
      fork_run(args, &status);
    } else if (is_redir(args)) {
      redirect(args, &status);
    } else if (is_pipe(args)) {
      pipes(*commands, &status);
    } else if (!strcmp(*args, "cd")){ // change directory
      change_dir(*++args);
    } else { // returns true for ending the program
      return 1;
    }
    commands++;
    free(command);
  }
  return 0;
}

char ** parse_args(char *line, char * sep){
  char ** ans;
  ans = malloc(1024);
  char *curr = line;
  int count = 0;
  while (curr){
    if (!strcmp(sep, " ")){
      char *temp = strsep(&curr, sep);
      if(strcmp(temp , "")){
        ans[count]= temp;
        count++;
      }
    }
    else{
      ans[count] = strsep(&curr, sep);
      count++;
    }
  }
  return ans;
}

void change_dir(char *input){
  chdir(input);
}

void redirect(char** args, int * status){
    // prior to finding <>, save the args to another argseg then after finding > or <, set that to redir
    // find filename by taking the argument after the < or >
    char *redir;   // holds < or >
    char **argseg = malloc(1024); // holds the arguments before < or >
    char *file;
    while (args)
    {
      if (strcmp(*args, ">") && strcmp(*args, "<"))
      { //if *argmem is not < or >
        *argseg = *args;
        argseg++;
        args++;
      } else {
        redir = *args;
        file = *++args;
        break;
     }
  }

  int f;
  int backup;
  f = open(file, O_RDWR | O_EXCL | O_CREAT, 0644);
  if (f < 0){
    f = open(file, O_RDWR);
  }
  if (strcmp(redir, ">")){ //then redir is <
    printf("%d\n", f);
    backup = dup(STDIN_FILENO);
    dup2(f, STDIN_FILENO);
  }
  else { //then redir is >
    printf("%d\n", f);
    backup = dup(STDOUT_FILENO);
    dup2(STDOUT_FILENO, f);
  }
  fork_run(argseg, status);
  close(f);
  dup2(f, backup);
}

int is_redir(char ** args) {
  while(*args) {
    if (!strcmp(*args, ">") || !strcmp(*args, "<")) // if args has redirect symbols
      return 1;
    args++;
  }
  return 0;
}

int is_pipe(char **args){
  while(*args) {
    if (!strcmp(*args, "|")) // if args has pipe
      return 1;
    args++;
  }
  return 0;
}

void pipes(char * command, int * status){
  printf("command recieved: %s\n", command);
  FILE * f = popen(command, "w");
  pclose(f);
}

void fork_run(char ** args, int * status) {
  int child = fork();
  if (child == 0)
  {
    execvp(*args, args);
    exit(0);
  }
  else
  {
    wait(status);
  }
}
