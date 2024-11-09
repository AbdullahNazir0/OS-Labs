#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    pid_t pid;
    pid = fork();
    if(pid > 0) {
        while(1) {
            sleep(100);
        }
    } else if(pid == 0) {
        exit(0);
    }
}