#include "shell.h"

int main (int argc, char *argv[]) {
    char path[256];
    char input[1024];
    while(1) {
        getcwd(path, 256);
        printf("%s[shell]: ", path);
        fgets(input, sizeof input, stdin);
        input[strlen(input) - 1] = '\0';
        if(execute(input))
            break;
    }
    return 0;
}
