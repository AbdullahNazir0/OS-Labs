#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void) {

    pid_t pid;

    printf("I am the parent process and pid is: %d\n", getpid());
    printf("Here I am before use of forking\n");

    pid = fork();

    printf("Here I am just after forking\n");

    if(pid == 0) {
        printf("I am the child process and pid is: %d\n", getpid());
        printf("I am loading ,,hello'' process\n");
        execl("hello.out", "hello.out", NULL);
    } else {
        printf("I am the parent process and pid is %d\n", getpid());
    }
}