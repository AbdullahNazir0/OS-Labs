#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    pid = fork();
    if(pid < 0) {
        printf("Fork Failed\n");
        exit(-1);
    }
    if(pid == 0) {
        int file_fd = open("input.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);
        dup2(file_fd, 1);
        close(file_fd);
        execlp("ls", "ls", "/", "-l", NULL);
    } else {
        wait(NULL);
    }
}