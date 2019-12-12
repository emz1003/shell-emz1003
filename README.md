# shell-emz1003

Kaitlyn Lau and Emily Zhang Period 10
Systems Programming Project 1

Features: <br />
  -Forks and executes commands!  <br />
  -Parses multiple commands on on line! <br />
  -Keeps prompting the user for a command until "exit" is inputted or other shortcuts such as CTRL-C are used.
  -Both cd and exit can be used in our shell.
  -Parses multiple commands on one line!
  -Redirects using >, <!
  -Can run simple pipes!
  -Will return to the home directory if "cd ~" is entered or just cd by itself

Attempted:

Bugs:
  -Cannot find foo for some reason, cat foo and rm foo
  -

Files & Function Headers:

shell.c
  int execute(char * line);
    -Returns 0 to continue executing, 1 to end the program
    -Line is the command line input
    -This execute function forks and exes the command line argument

  char ** parse_args(char * line, char * sep);
    -Returns a char** that represents the individual tokens after parsing
    -Line is the input that is being parsed, sep is the delimiter
    -This parse_args function parses the inputted line based on the delimiter

  void change_dir( char * input);
    -Returns nothing
    -Input is the directory that the function is changing into
    -This change_dir function acts as the cd function for a shell

  char * get_homedir();
    -Returns a char* of the path of the home directory
    -Nothing is inputted into the function
    -This get_homedir function gets the path of the home directory

  void redirect(char** args, int * status);
    -Returns nothing
    -Args is the array of parsed tokens that is being read from the command line, status is a variable storing a number that tells you how the process ended
    -This redirect function redirects files using dup2 and dup

  int is_redir(char ** args);
    -Returns an int: 0 if no redir symbol and 1 if redir symbol is present
    -Args is the array of parsed tokens that is being read from the command line
    -This is_redir function checks to see if the command line input has a redirecting character

  void fork_run(char ** args, int * status);
    -Returns nothing
    -Args is the array of parsed tokens that are being read from the command line
    -This fork_run function forks and execs the command being inputted

  int is_pipe(char ** args);
    -Returns an int: 0 if no pipe symbol and 1 if pipe symbol is present
    -Args is the array of parsed tokens that is being read from the command line
    -This is_pipe function checks to see if the command line input has a redirecting character

  void pipes(char * command, int * status);
    -Returns nothing
    -Command is the command line input, status is a variable storing a number that tells you how the process ended
    -This pipes function implements simple pipes using popen()
