#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

sem_t lock;
sem_t employeeLock;

void *handleJob(void *args) {
    int *employee = (int *)args;
    sem_wait(&employeeLock);
    for(int i = 0; i < 2; i++) {
        sem_wait(&lock);
        printf("Employee %d job %d is working\n", *employee, i + 1);
        usleep(100000);
        printf("Job %d finished\n", i + 1);
        sem_post(&lock);
    }
    sem_post(&employeeLock);
    
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t threads[10];
    int employees[10];
    sem_init(&lock, 0, 1);
    sem_init(&employeeLock, 0, 1);

    for (int i = 0; i < 10; i++) {
        employees[i] = i;
        pthread_create(&threads[i], NULL, handleJob, &employees[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&lock);
    sem_destroy(&employeeLock);

    return 0;
}