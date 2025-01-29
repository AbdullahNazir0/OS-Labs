#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t accessLock, readersLock, orderLock;
int readersCount = 0, order = 0;

void *reader(void *arg) {

    sem_wait(&orderLock);
    sem_wait(&readersLock);
    readersCount++;
    if(readersCount == 1) {
        sem_wait(&accessLock);
    }
    sem_post(&readersLock);
    sem_post(&orderLock);

    printf("Reader is reading\n");
    usleep(100000);
    printf("Reader is done reading\n");

    sem_wait(&readersLock);
    readersCount--;
    if(readersCount == 0) {
        sem_post(&accessLock);

    }
    sem_post(&readersLock);

    return NULL;
}

void *writer(void *arg) {

    sem_wait(&orderLock);
    sem_wait(&accessLock);
    sem_post(&orderLock);

    printf("Writer is writing\n");
    usleep(100000);
    printf("Writer is done writing\n");

    sem_post(&accessLock);

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t readers[5], writers[5];
    sem_init(&accessLock, 0, 1);
    sem_init(&readersLock, 0, 1);
    sem_init(&orderLock, 0, 1);

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&readers[i], NULL, reader, NULL);
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&accessLock);
    sem_destroy(&readersLock);
    sem_destroy(&orderLock);

    return 0;
}