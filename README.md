# shell-emz1003

Kaitlyn Lau and Emily Zhang Period 10
Systems Programming Project 1

1) Our shell reads in one line at a time like it should. It will keep prompting the user
for a command until "exit" is inputted or other shortcuts such as CTRL-C are used.
Both cd and exit can be used in our shell. Our shell can also read and separate multiple
commands on one line with ;. We are assuming that every command line is being parsed with a delimiter of one character long.

2) A description of what features you attempted to implement but were unsuccessful

3) Any bugs or things you want me to know about your program

4) Our function headers are also listed in shell.h!

int execute(char * line);
  //Returns 0 to continue executing, 1 to end the program
  //Line is the command line input
  //This execute function forks and exes the command line argument

char ** parse_args(char * line, char * sep);
  //Returns a char** that represents the individual tokens after parsing
  //Line is the input that is being parsed, sep is the delimiter
  //This parse_args function parses the inputted line based on the delimiter

void change_dir( char * input);
  //Returns nothing
  //Input is the directory that the function is changing into
  //This change_dir function acts as the cd function for a shell

void redirect(char** args, int * status);
  //Returns nothing
  //Args is the array of parsed tokens that is being read from the command line
  //This redirect function redirects files using dup2 and dup

int is_redir(char ** args);
  //Returns an int: 0 if no redir symbol and 1 if redir symbol is present
  //Args is the array of parsed tokens that is being read from the command line
  //This is_redir function checks to see if the command line input has a redirecting character

void fork_run(char ** args, int * status);
  //Returns nothing
  //Args is the array of parsed tokens that are being read from the command line
  //This fork_run function forks and execs the command being inputted
