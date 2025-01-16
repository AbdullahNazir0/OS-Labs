#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int shared_variable;     
int flag = 0;      
pthread_mutex_t lock;  
pthread_cond_t cond_var; 

void *sender(void *arg)
{
    for (int i = 1; i <= 10; i++)
    {
        pthread_mutex_lock(&lock);
        while (flag)
        {
            pthread_cond_wait(&cond_var, &lock);
        }
        shared_variable = i; 
        printf("Thread #1: Sent %d\n", i);
        flag = 1;                  
        pthread_cond_signal(&cond_var); 
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

void *reciever(void *arg)
{
    for (int i = 1; i <= 10; i++)
    {
        pthread_mutex_lock(&lock);
        while (!flag)
        {
            pthread_cond_wait(&cond_var, &lock);
        }
        printf("Thread #2: Received %d\n", shared_variable); 
        flag = 0;                                   
        pthread_cond_signal(&cond_var);                
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1, thread2;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond_var, NULL);

    pthread_create(&thread1, NULL, sender, NULL);
    pthread_create(&thread2, NULL, reciever, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond_var);

    return 0;
}
