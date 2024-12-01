#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>

int main(int argc, char *argv[]) {
    int pipe_fd[2];
    pipe(pipe_fd);

    pid_t pid;
    pid = fork();
    if(pid < 0) {
        printf("Fork Failed\n");
        exit(-1);
    }
    if(pid == 0) {
        int fd = open("input.txt", O_RDONLY);
        dup2(fd, 0);
        close(fd);
        dup2(pipe_fd[1], 1);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execlp("grep", "grep", "m", NULL);
    } else {
        pid = fork();
        if(pid < 0) {
            printf("Fork Failed\n");
            exit(-1);
        }
        if(pid == 0) {
            dup2(pipe_fd[0], 0);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
            dup2(fd, 1);
            close(fd);
            execlp("sort", "sort", NULL);
        } else {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            wait(NULL);
            wait(NULL);
        }
    }
}