#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    int fd1[2];

    pipe(fd);
    pipe(fd1);

    pid_t pid = fork();
    pid_t pid1 = fork();
    pid_t pid2 = fork();

    if (pid == 0)
    {
        // c1
        close(fd[0]);
        close(fd1[0]);
        close(fd1[1]);
        dup2(fd[1], 1);
        execlp("ls", "ls", "/", NULL);
        return 0;
    }
    if (pid1 == 0)
    {
        // c2
        close(fd[1]);
        close(fd1[0]);
        dup2(fd[0], 0);
        dup2(fd1[1], 1);
        execlp("sort", "sort", "-r", NULL);
        return 0;
    }
    if (pid2 == 0)
    {
        close(fd1[1]);
        close(fd[0]);
        close(fd[1]);
        dup2(fd1[0], 0);
        execlp("grep", "grep", "bin", NULL);
        return 0;
    }

    close(fd[0]), close(fd[1]), close(fd[0]), close(fd[1]);
    close(fd1[0]), close(fd1[1]), close(fd1[0]), close(fd1[1]);

    // waitpid(pid1, NULL, WUNTRACED);
}