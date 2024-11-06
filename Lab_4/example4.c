#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid;

    printf("I am the original process with PID %d and PPID %d\n", getpid(), getppid());

    pid = fork();
    if(pid > 0) {
        printf("I am the parent with PID %d and PPID %d\n", getpid(), getppid());
        printf("My child's PID is %d\n", pid);
    } else if(pid == 0) {
        sleep(4);
        printf("I am the child with PID %d and PPID %d\n", getpid(), getppid());
    }
    printf("PID %d terminates\n", getpid());

    return 0;
}