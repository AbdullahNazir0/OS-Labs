#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    printf("I am before fork\n");

    fork();

    printf("I am after forking\n");
    printf("\t I am process having process id %d and parent process id is %d\n", getpid(), getppid());

    return 0;
}