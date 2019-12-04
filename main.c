#include "shell.h"

int main () {
   char line[] = "ls -a -l";
   printf("Using parse_args to run ls -a -l:\n");
   char ** args = parse_args(line, " ");
   execvp(args[0], args);

   //changedir("");
}
