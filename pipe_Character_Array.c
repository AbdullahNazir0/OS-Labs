#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    char buffer[100];
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("Pipe failed");
        exit(1);
    }

    char arr[] = "Hello from Parent";

    if (fork() == 0)
    {

        close(fd[1]);
        printf("Child Process (Parent ID: %d) \n", getppid());
        read(fd[0], buffer, sizeof(buffer)); //
        printf("Child received: %s\n", buffer);
        close(fd[0]);
        exit(0);
    }
    else
    {

        close(fd[0]);
        printf("Parent Process (ID: %d) \n", getpid());
        write(fd[1], arr, strlen(arr) + 1);
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
