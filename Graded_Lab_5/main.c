#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>

int buffer[5];
int in = 0;
int out = 0;

sem_t lock;
sem_t producerLock;
sem_t consumerLock;

void *producer(void *args) {
    int id = *(int *)args;
    free(args);

    for(int i = 0; i < 10; i++) {
        sem_wait(&producerLock);
        sem_wait(&lock);

        buffer[in] = i + 1;
        printf("Producer %d: Produced item %d\n", id, buffer[in]);
        in = (in + 1) % 5;

        sem_post(&lock);
        sem_post(&consumerLock);

        usleep(100000);
    }

    return NULL;
}

void *consumer(void *args) {
    int id = *(int *)args;
    free(args);

    for(int i = 0; i < 10; i++) {
        sem_wait(&consumerLock);
        sem_wait(&lock);

        int item = buffer[out];
        printf("Consumer %d: Consumed item %d\n", id, item);
        out = (out + 1) % 5;

        sem_post(&lock);
        sem_post(&producerLock);

        usleep(150000);
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t producers[2], consumers[2];

    sem_init(&lock, 0, 1);
    sem_init(&producerLock, 0, 5);
    sem_init(&consumerLock, 0, 0);

    // for(int i = 0; i < 2; i++) {
    //     pthread_create(&producers[i], NULL, producer, NULL);
    //     pthread_create(&consumers[i], NULL, consumer, NULL);

    //     pthread_join(producers[i], NULL);
    //     pthread_join(consumers[i], NULL);
    // }

    for(int i = 0; i < 2; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&producers[i], NULL, producer, id);
    }

    for(int i = 0; i < 2; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&consumers[i], NULL, consumer, id);
    }

    for(int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
    }

    for(int i = 0; i < 2; i++) {
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&lock);
    sem_destroy(&producerLock);
    sem_destroy(&consumerLock);

    return 0;
}