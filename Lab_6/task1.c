#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    if(pid < 0) {
        exit(EXIT_FAILURE);
    }
    if(pid == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execlp("ls", "ls", "/", "-l", NULL);
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execlp(">", ">", "input.txt", NULL);
        exit(EXIT_FAILURE);
    }

    return 0;
}
