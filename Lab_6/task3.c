#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int pipe1[2], pipe2[2], pipe3[2];
    pipe(pipe1);

    pid_t pid = fork();
    if (pid < 0)
    {
        printf("Fork Failed\n");
        exit(-1);
    }

    if (pid == 0)
    {
        int fd = open("error.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
        
        dup2(fd, STDERR_FILENO);
        close(fd);

        close(pipe1[0]);
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[1]);

        execlp("ls", "ls", "/", "-lR", NULL);
    }
    else
    {

        close(pipe1[1]);
        pipe(pipe2);

        pid = fork();
        if (pid < 0)
        {
            printf("Fork Failed\n");
            exit(-1);
        }

        if (pid == 0)
        {
            dup2(pipe1[0], 0);
            close(pipe1[0]);

            close(pipe2[0]);
            dup2(pipe2[1], 1);
            close(pipe2[1]);

            execlp("grep", "grep", "Nov", NULL);
        }
        else
        {

            close(pipe1[0]);
            close(pipe2[1]);

            pipe(pipe3);

            pid = fork();
            if (pid < 0)
            {
                printf("Fork Failed\n");
                exit(-1);
            }

            if (pid == 0)
            {
                dup2(pipe2[0], 0);
                close(pipe2[0]);

                close(pipe3[0]);
                dup2(pipe3[1], 1);
                close(pipe3[1]);

                execlp("sort", "sort", NULL);
            }
            else
            {

                close(pipe2[0]);
                close(pipe3[1]);

                pid = fork();
                if (pid < 0)
                {
                    printf("Fork Failed\n");
                    exit(-1);
                }

                if (pid == 0)
                {
                    dup2(pipe3[0], 0);
                    close(pipe3[0]);

                    execlp("less", "less", NULL);
                }
                else
                {

                    close(pipe3[0]);

                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                }
            }
        }
    }

    return 0;
}
