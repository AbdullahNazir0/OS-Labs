#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    pid_t pid;
    printf("Hello World!\n");
    printf("I'm the parent process and pid is: %d\n", getpid());
    printf("Here I am before use of forking\n");
    
    pid = fork();
    printf("Here I am just after forking\n");
    if(pid == 0) {
        printf("I am the child process and pid is: %d\n", getpid());
    } else if(pid > 0) {
        printf("I am the parent process and pid is: %d\n", getpid());
    } else if(pid < 0) {
        printf("Error fork failed\n");
    }

    return 0;
}