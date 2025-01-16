#include <stdio.h>
#include <pthread.h>
long compare_and_set(long *flag, long expected, long new);
asm(/* compile with 64-bit compiler*/
    "compare_and_set:;"
    "movq %rsi,%rax;"
    "lock cmpxchgq %rdx,(%rdi);"
    "retq;");
long count, flag = 0, expected = 0, new = 1;
void *increment(void *ptr)
{
    for (unsigned int i = 0; i < 2000000; i++)
    {
        while (compare_and_set(&flag, expected, new) != 0)
            ;
        count++;
        flag = 0;
    }
    pthread_exit(0);
}
void *decrement(void *ptr)
{
    for (unsigned int i = 0; i < 2000000; i++)
    {
        while (compare_and_set(&flag, expected, new) != 0)
            ;
        count--;
        flag = 0;
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