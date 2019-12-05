#include "shell.h"

int main() {
    char stuff[] = "ls -a -l;echo hi";
    execute(stuff);
    return 0;
}