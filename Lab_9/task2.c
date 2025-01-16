#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 100
#define NUM_THREADS 10

int array[ARRAY_SIZE]; 
int sum = 0;       
pthread_mutex_t lock; 

typedef struct
{
    int start;
    int end;
} ThreadArgs;

void *partial_sum(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int local_sum = 0;
    
    for (int i = args->start; i < args->end; i++)
    {
        local_sum += array[i];
    }

    pthread_mutex_lock(&lock);
    sum += local_sum;
    pthread_mutex_unlock(&lock);

    free(arg); 
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int elements_per_thread = ARRAY_SIZE / NUM_THREADS;

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = i + 1;
    }

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        ThreadArgs *args = malloc(sizeof(ThreadArgs));
        if (args == NULL)
        {
            perror("Failed to allocate memory for thread arguments");
            exit(EXIT_FAILURE);
        }

        args->start = i * elements_per_thread;
        args->end = (i + 1) * elements_per_thread;

        pthread_create(&threads[i], NULL, partial_sum, (void *)args);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&lock);

    printf("Total sum: %d\n", sum);

    return 0;
}
