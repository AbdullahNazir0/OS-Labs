#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    int *arr = (int *)malloc((argc - 1) * sizeof(int));

    // printf("\nArray from Terminal: ");
    for (int i = 0; i < argc - 1; i++)
    {
        arr[i] = atoi(argv[i + 1]);
    }

    int fd1[2];
    int fd2[2];

    pipe(fd1);
    pipe(fd2);

    pid_t pid = fork();
    if (pid == 0)
    {
        close(fd1[1]);
        close(fd2[0]);

        int receivedArr[100];
        read(fd1[0], receivedArr, sizeof(receivedArr));
        close(fd1[0]);

        int sum = 0;
        for (int i = 0; i < argc - 1; i++)
        {
            sum = sum + receivedArr[i];
        }

        write(fd2[1], &sum, sizeof(sum));
        close(fd2[1]);
    }
    else
    {
        close(fd1[0]);
        close(fd2[1]);

        // Send array to child
        write(fd1[1], arr, (argc - 1) * sizeof(int));
        close(fd1[1]);

        int sum;
        read(fd2[0], &sum, sizeof(sum));
        close(fd2[0]);

        printf("The sum of the array is %d\n", sum);
        wait(NULL); // Wait for the child to finish
    }

    return 0;
}
