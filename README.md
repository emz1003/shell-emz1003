# shell-emz1003

Kaitlyn Lau and Emily Zhang Period 10
Systems Programming Project 1

1) Our shell reads in one line at a time like it should. It will keep prompting the user
for a command until "exit" is inputted or other shortcuts such as CTRL-C are used.
Both cd and exit can be used in our shell. Our shell can also read and separate multiple
commands on one line with ;.

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
  
void redirect(char* redir, char* file);
