#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <pthread.h>

unsigned int count;
void *increment(void *ptr)
{
    for (unsigned int i = 0; i < 500000; i++)
        count++;
}
void *decrement(void *ptr)
{
    for (unsigned int i = 0; i < 500000; i++)
        count--;
}
int main()
{
    count = 3;
    printf("\nInitial value of Count is %d ", count);
    pthread_t pid1, pid2;
    pthread_create(&pid1, NULL, &increment, NULL);
    pthread_create(&pid2, NULL, &decrement, NULL);
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    printf("\nFinal value of Count is %d ", count);
    printf("\nIs it correct? \n");
    return 0;
}