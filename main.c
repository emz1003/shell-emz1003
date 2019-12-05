#include "shell.h"

int main (int argc, char *argv[]) {
   char input[1024];
   while(strcmp(input, "exit")) {
     printf("[shell]: ");
     fgets(input, sizeof input, stdin);
     input[strlen(input) - 1] = '\0';
     char ** args = parse_args(input, " ");
     execvp(args[0], args);
   }

   //changedir("");
}
