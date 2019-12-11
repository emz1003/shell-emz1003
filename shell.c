#include "shell.h"

int execute(char * line) {
  char ** commands = parse_args(line, ";");
  while(*commands) {
    char ** args = parse_args(*commands, " "); // string array of cammands
    int status;
    if (strcmp(line, "cd") && strcmp(line, "exit") && !is_redir(args)) // if not cd or exit
    {
      fork_run(args, &status);
    } else if (is_redir(args)) {
      redirect(args, &status);
    } else if (!strcmp(*args, "cd")){ // change directory
        char *temp = *++args;
        if(temp){
          change_dir(temp);
        }
        else {change_dir("~");}
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
  char *homedir;
  if ((homedir = getenv("HOME")) == NULL) {
    pw = getpwuid(getuid());
    homedir = pw->pw_dir;
  }
  if(strcmp("~", input)){
    chdir(input);
  }
  else {
    chdir(homedir);
  }
}

void redirect(char ** args, int * status){
    // prior to finding <>, save the args to another argseg then after finding > or <, set that to redir
    // find filename by taking the argument after the < or >
    char *redir;   // holds < or >
    char **argseg = malloc(1024); // holds the arguments before < or >
    char ** argseg_mem = argseg;
    char *file;
    while (args)
    {
      if (strcmp(*args, ">") && strcmp(*args, "<"))
      { //if *argmem is not < or >
        *argseg_mem = *args;
        argseg_mem++;
        args++;
      } else {
        redir = *args;
        file = *++args;
        break;
     }
  }

  // create file if not exists and openwith RDWR or else open and RDWR
  int f;
  int backup;
  int io;
  f = open(file, O_RDWR | O_EXCL | O_CREAT, 0644);
  if (f < 0){
    f = open(file, O_RDWR);
  }

  if (strcmp(redir, ">")){ //then redir is <
    io = STDIN_FILENO;
  }
  else { //then redir is >
    io = STDOUT_FILENO;
  }
  backup = dup(io); // backup created for STDIN
  dup2(f, io);      // f takes the place of STDIN_FILENO
  fork_run(argseg, status);
  close(f);
  dup2(backup, io);
}

int is_redir(char ** args) {
  while(*args) {
    if (!strcmp(*args, ">") || !strcmp(*args, "<")) // if args has redirect symbols
      return 1;
    args++;
  }
  return 0;
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
