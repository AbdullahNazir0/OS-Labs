#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t writerLock, lock;
int readerCount = 0;

void *reader(void *arg)
{

    sem_wait(&lock);
    readerCount++;
    if (readerCount == 1)
    {
        sem_wait(&writerLock);
    }
    sem_post(&lock);

    printf("Reader is reading\n");
    usleep(100000);
    printf("Reader is done reading\n");

    sem_wait(&lock);
    readerCount--;
    if (readerCount == 0)
    {
        sem_post(&writerLock);
    }

    return NULL;
}

void *writer(void *arg)
{

    sem_wait(&writerLock);
    printf("Writer is writing\n");
    usleep(100000);
    printf("Writer is done writing\n");
    sem_post(&writerLock);

    return NULL;
}

int main(int agrc, char *argv[])
{

    pthread_t readers[5], writers[5];
    sem_init(&writerLock, 0, 1);
    sem_init(&lock, 0, 1);

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

    sem_destroy(&writerLock);
    sem_destroy(&lock);

    return 0;
}