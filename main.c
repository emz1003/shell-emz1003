#include "shell.h"

int main (int argc, char *argv[]) {
    char path[256];
    char input[1024];
    int parent = getpid();
    while(getpid() == parent) {
        getcwd(path, 256);
        char * temp;
        temp = tildapath(path);
        printf("%s[shell]: ", temp);
        fgets(input, sizeof input, stdin);
        input[strlen(input) - 1] = '\0';
        if(execute(input)){
            break;
        }
    }
    return 0;
}
