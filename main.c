#include "shell.h"

int main (int argc, char *argv[]) {
    char path[256];
    char input[1024];
    int parent = getpid();
    while(getpid() == parent) {
        getcwd(path, 256);
        char homedirec[256];
        strncpy(homedirec, path, strlen(get_homedir()));
        if(!strcmp(homedirec, get_homedir())){
            char temp[256];
            strncpy(temp, path + strlen(get_homedir()), strlen(path)-strlen(get_homedir()));
            strcpy(path, "~");
            strcat(path, temp);
        }
        printf("%s[shell]: ", path);
        fgets(input, sizeof input, stdin);
        input[strlen(input) - 1] = '\0';
        if(execute(input))
            break;
    }
    return 0;
}
