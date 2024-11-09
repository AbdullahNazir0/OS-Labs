#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status = 0;
    
    printf("Hello World!\n");
    
    pid = fork();
    if(pid < 0) {
        perror("bad fork\n");
        exit(-1);
    }
    
    if(pid == 0) {
        printf("I am the child process.\n");
    }
    else {
        wait(&status);
        printf("I am the parent process.\n");
    }

    return 0;
}