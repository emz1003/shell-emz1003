#include "shell.h"

int execute(char * line) {
  char ** commands = parse_args(line, ";");
  char ** commandscpy = commands;
  while(*commands) {
    char *command = calloc(1024, sizeof(char));
    strcpy(command, *commands);
    char ** args = parse_args(command, " "); // string array of cammands
    char ** argscpy = args;
    int status;
    if (strcmp(*args, "cd") && strcmp(*args, "exit") && !is_redir(args) && !is_pipe(args)) // if not cd or exit
    {
      fork_run(args, &status);
    } else if (is_redir(args)) {
      redirect(args, &status);
    } else if (is_pipe(args)) {
      pipes(*commands, &status);
    } else if (!strcmp(*args, "cd")){ // change directory
        char *temp = *++args;
        if(temp){ //if cd isn't inputted by itself, just do cd on the input
          change_dir(temp);
        }
        else {change_dir("~");} //otherwise, go to the home directory!
    } else { // returns true for ending the program
      return 1;
    }
    free(command);
    free(argscpy);
    commands++;
  }

    free(commandscpy);
  return 0;
}

char ** parse_args(char *line, char * sep){
  char ** ans = calloc(1024, sizeof(char));
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
  char * homedir = get_homedir();
  if(strcmp("~", input)){
    chdir(input);
  }
  else {
    chdir(homedir);
    if(errno){ //see if any error
      printf("Error number: %d\n", errno);
      printf("Error message: %s\n", strerror(errno));
    }
  }
}

char * get_homedir() {
  char * homedir;
  if ((homedir = getenv("HOME"))){
    pw = getpwuid(getuid());
    return pw->pw_dir;
  }
  return NULL;
}

void redirect(char ** args, int * status){
    // prior to finding <>, save the args to another argseg then after finding > or <, set that to redir
    // find filename by taking the argument after the < or >
    char *redir;   // holds < or >
    char **argseg = calloc(1024, sizeof(char)); // holds the arguments before < or >
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
  if(errno){ //see if any error
    printf("Error number: %d\n", errno);
    printf("Error message: %s\n", strerror(errno));
  }
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
  // free(argseg);
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
  FILE * f = popen(command, "w");
  pclose(f);
}

void fork_run(char ** args, int * status) {
  int child = fork();
  if(errno){ //see if any error
    printf("Error number: %d\n", errno);
    printf("Error message: %s\n", strerror(errno));
  }
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
