#include <stdio.h>  // input output -> printf scanf
#include <stdlib.h> // malloc atoi()
#include <unistd.h> // fork() pipe() write() read()
#include <sys/types.h>
#include <pthread.h>
// One thread and I will find the sum of an array
int size = 0;

void *sum(void *ptr)
{
    int *newarr = (int *)ptr;
    int *sum = (int *)malloc(sizeof(int));
    *sum = 0;
    for (int i = 0; i < size; i++)
    {
        *sum = *sum + newarr[i];
    }
    printf("\nSum Calculated by thread: %d", *sum);

    return sum;
}

int main(int argc, char *argv[])
{
    size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));

    printf("Size: %d\n", size);
    // Printing Array from Command line
    printf("Array from Terminal: ");
    for (int i = 0; i < size; i++)
    {
        arr[i] = atoi(argv[i + 1]);
        printf("%d ", arr[i]);
    }

    pthread_t tid;
    // void*
    pthread_create(&tid, NULL, sum, (void *)arr);

    void *mainsum;
    pthread_join(tid, &mainsum);
    printf("Sum Returned from Thread: %d", *(int *)mainsum);

    return 0;
}
