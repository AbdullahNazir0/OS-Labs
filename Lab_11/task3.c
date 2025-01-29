#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t accessLock, readersLock, writerLock, readerLimit, orderLock;
int readersCount = 0, readersCompleted = 0;

void *reader(void *args) {

    sem_wait(&orderLock);
    sem_wait(&readerLimit);

    sem_wait(&readersLock);
    readersCount++;
    if(readersCount == 1) {
        sem_wait(&accessLock);
    }
    sem_post(&readersLock);

    printf("Reader is reading\n");
    usleep(100000);
    printf("Reader is done reading\n");

    sem_wait(&readersLock);
    readersCount--;
    readersCompleted++;
    if(readersCount == 0) {
        sem_post(&accessLock);
    }
    sem_post(&readersLock);
    
    if (readersCompleted == 5) {
        readersCompleted = 0;     
        sem_post(&writerLock);  
    } else {
        sem_post(&orderLock); 
    }

    return NULL;
}

void *writer(void *args) {

    sem_wait(&writerLock);
    sem_wait(&accessLock);

    printf("Writer is writing\n");
    usleep(100000);
    printf("Writer is done writing\n");

    sem_post(&accessLock);
    for (int i = 0; i < 5; i++) {
        sem_post(&readerLimit);
    }
    sem_post(&orderLock);

    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t readers[8], writers[3];

    sem_init(&accessLock, 0, 1);
    sem_init(&readersLock, 0, 1);
    sem_init(&writerLock, 0, 0);
    sem_init(&readerLimit, 0, 5);
    sem_init(&orderLock, 0, 1);

    for (int i = 0; i < 8; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    for (int i = 0; i < 8; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&accessLock);
    sem_destroy(&readersLock);
    sem_destroy(&writerLock);
    sem_destroy(&readerLimit);
    sem_destroy(&orderLock);

    return 0;
}