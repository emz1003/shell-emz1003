#include "shell.h"

int main (int argc, char *argv[]) {
    char path[256];
    char input[1024];
    while(strcmp(input, "exit")) {
        getcwd(path, 256);
        printf("%s[shell]: ", path);
        fgets(input, sizeof input, stdin);
        input[strlen(input) - 1] = '\0';
        execute(input);
   }

   //changedir("");
}
