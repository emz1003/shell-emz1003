#include "shell.h"

int main (int argc, char *argv[]) {
    char input[1024];
    while(strcmp(input, "exit")) {
     printf("[shell]: ");
     fgets(input, sizeof input, stdin);
     input[strlen(input) - 1] = '\0';
     execute(input);
   }

   //changedir("");
}
