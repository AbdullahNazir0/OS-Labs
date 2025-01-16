#include <stdio.h>
#include <pthread.h>

int flag[2] = { 0, 0 };
int turn = 0;

long count;

void *increment(void *ptr) {
    for (unsigned int i = 0; i < 1000000; i++)
    {
        flag[0] = 1;
        turn = 1;
        while (flag[1] == 1 && turn == 1)
        {
        }
        count++;
        flag[0] = 0;
    }
    pthread_exit(0);
}
void *decrement(void *ptr)
{
    for (unsigned int i = 0; i < 1000000; i++)
    {
        flag[1] = 1;
        turn = 0;
        while (flag[0] == 1 && turn == 0)
        {
        }
        count--;
        flag[1] = 0;
    }
    pthread_exit(0);
}
int main()
{
    count = 100;
    pthread_t pid1, pid2;
    printf("\nInitial value of Count is %ld ", count);
    pthread_create(&pid1, NULL, &increment, NULL);
    pthread_create(&pid2, NULL, &decrement, NULL);
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    printf("\nFinal value of Count is %ld ", count);
    printf("\nIs it correct? \n");
    return 0;
}