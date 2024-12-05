#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>

int main(int argc, char *argv[]) {

    int fd1[2], fd2[2];
    pipe(fd1); // pipe for ls -> grep
    pipe(fd2); // pipe for grep -> more

    pid_t pid;
    pid = fork();
    if(pid < 0) {
        printf("Fork failed\n");
        exit(-1);
    }
    if(pid == 0) {
        // child1
        close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);
        dup2(fd1[1], 1);
        close(fd1[1]);

        execlp("ls", "ls", NULL);
        printf("execlp failed\n");
        exit(-1);
    } else {
        pid = fork();
        if(pid < 0) {
            printf("Fork failed\n");
            exit(-1);
        }
        if(pid == 0) {
            // child2
            close(fd1[1]);
            close(fd2[0]);
            dup2(fd1[0], 0);
            close(fd1[0]);
            dup2(fd2[1], 1);
            close(fd2[1]);

            execlp("grep", "grep", "user", NULL);
            printf("execlp failed\n");
            exit(-1);
        } else {
            // parent
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[1]);
            dup2(fd2[0], 0);
            close(fd2[0]);

            int fd = open("output.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);
            dup2(fd, 1);
            close(fd);

            execlp("more", "more", NULL);
            printf("execlp failed\n");
            exit(-1);
        }
    }

}
