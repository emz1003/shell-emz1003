#include "shell.h"

int execute(char * line) {
  char ** commands = parse_args(line, ";");
  char ** commandscpy = commands;
  while(*commands) {
    char *command = calloc(1024, sizeof(char)); // strsep will be used on this
    strcpy(command, *commands);
    char ** args = parse_args(command, " "); // string array of cammands
    char ** argscpy = args;
    int status;
    if (strcmp(*args, "cd") && strcmp(*args, "exit") && !is_redir(*commands) && !is_pipe(args)) // if not cd or exit
    {
      fork_run(args, &status);
    } else if (is_redir(*commands)) {
      redirect(*commands, &status);
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
      printf("%d: %s\n", errno, strerror(errno));
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

void redirect(char * command, int * status){
    // prior to finding <>, save the args to another argseg then after finding > or <, set that to redir
    char *arro = calloc(64, sizeof(char));
    int a = 0;
    for (int i = 0; i < 64; i++) {
      if((command[i] == '>') || (command[i] == '<')) {
        arro[a] = command[i];
        a++;
      }
    }
    arro[a] = 0;

    // find filename by taking the argument after the < or >
    char ** args = parse_args(command, "<>");
    char ** parsed_arg = parse_args(args[0], " ");
    int io[64];
    int f[64];
    int backup[64];
    for( int i = 0; args[i+1]; i++) {
      char * file = args[i+1];

      char **arr = parse_args(file, " ");
      file = *arr;

      f[i] = open(file, O_RDWR | O_EXCL | O_CREAT, 0644);
      if (f[i] < 0)
      {
        f[i] = open(file, O_RDWR);
      }

      if (arro[i] == '<')
      { //then redir is <
        io[i] = STDIN_FILENO;
      }
      else
      { //then redir is >
        io[i] = STDOUT_FILENO;
      }
      backup[i] = dup(io[i]); // backup created for io
      dup2(f[i], io[i]);      // f takes the place of io
    }

    fork_run(parsed_arg, status);

    for(int i = 0; f[i]; i++){
      close(f[i]);
      dup2(backup[i], io[i]);
    }
    // // create file if not exists and openwith RDWR or else open and RDWR
    free(parsed_arg);
    free(args);
}

int is_redir(char * command) {
  while(*command) {
    if ((*command == '>') || (*command == '<')) // has redirect symbols
      return 1;
    command++;
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
