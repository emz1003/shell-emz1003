# shell-emz1003

Kaitlyn Lau and Emily Zhang Period 10
Systems Programming Project 1

Features: <br />
  -Forks and executes commands!  <br />
  -Parses multiple commands on on line! <br />
  -Keeps prompting the user for a command until "exit" is inputted or other shortcuts such as CTRL-C are used. <br />
  -Both cd and exit can be used in our shell. <br />
  -Parses multiple commands on one line! <br />
  -Redirects using >, <! <br />
  -Can run simple pipes! <br />
  -Will return to the home directory if "cd ~" is entered or just cd by itself <br />
  -Replaces the home directory with ~/ <br />

Attempted: <br />

Bugs: <br />
  -When you do ./program < TEST_COMMANDS.txt, it prints out our shell directory many times in the beginning and end of the file, not sure why <br />
  -When you do ./program < TEST_COMMANDS.txt, it could also stop at the redirect test, even though redirecting works normally <br />
  -After we replaced the home directory with ~/, seg faults occur if you enter a blank line into the shell <br />

Files & Function Headers:

shell.c <br />
  int execute(char * line); <br />
    -Returns 0 to continue executing, 1 to end the program <br />
    -Line is the command line input <br />
    -This execute function forks and exes the command line argument

  char ** parse_args(char * line, char * sep); <br />
    -Returns a char** that represents the individual tokens after parsing <br />
    -Line is the input that is being parsed, sep is the delimiter <br />
    -This parse_args function parses the inputted line based on the delimiter <br />

  void change_dir( char * input); <br />
    -Returns nothing <br />
    -Input is the directory that the function is changing into <br />
    -This change_dir function acts as the cd function for a shell <br />

  char * get_homedir(); <br />
    -Returns a char* of the path of the home directory <br />
    -Nothing is inputted into the function <br />
    -This get_homedir function gets the path of the home directory <br />

  void redirect(char* command, int * status);<br />
    -Returns nothing<br />
    -Command is the entire input that is being read from the command line, status is a variable storing a number that tells you how the process ended<br />
    -This redirect function redirects files using dup2 and dup<br />

  int is_redir(char ** args);<br />
    -Returns an int: 0 if no redir symbol and 1 if redir symbol is present<br />
    -Args is the array of parsed tokens that is being read from the command line<br />
    -This is_redir function checks to see if the command line input has a redirecting character<br />

  void fork_run(char ** args, int * status);<br />
    -Returns nothing<br />
    -Args is the array of parsed tokens that are being read from the command line<br />
    -This fork_run function forks and execs the command being inputted<br />

  int is_pipe(char ** args);<br />
    -Returns an int: 0 if no pipe symbol and 1 if pipe symbol is present<br />
    -Args is the array of parsed tokens that is being read from the command line<br />
    -This is_pipe function checks to see if the command line input has a redirecting character<br />

  void pipes(char * command, int * status);<br />
    -Returns nothing<br />
    -Command is the command line input, status is a variable storing a number that tells you how the process ended<br />
    -This pipes function implements simple pipes using popen()<br />

  char * tildapath (char * path); <br />
    -Returns a char* of the new path with ~/ replacing the home directory <br />
    -Command is the command line input, status is a variable storing a number that tells you how the process ended<br />
    -This tildapath function takes in the path and creates a new path with the home directory with a tilda<br />
