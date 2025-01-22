#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define numberOfChopsticks 5
sem_t chopsticks[ numberOfChopsticks ];
sem_t maxEating; // 2 philosophers can eat at a time

void *philosopher(void *args) {
    int i = *(int *)args;
    printf("Philosopher %d is thinking\n", i);

    printf("Philosopher %d is hungry\n", i);

    sem_wait(&maxEating);

    if(i % 2 == 0) {
        sem_wait(&chopsticks[i]);
        sem_wait(&chopsticks[(i + 1) % numberOfChopsticks]);
    } else {
        sem_wait(&chopsticks[(i + 1) % numberOfChopsticks]);
        sem_wait(&chopsticks[i]);
    }

    printf("Philosopher %d is eating\n", i);

    sem_post(&chopsticks[i]);
    sem_post(&chopsticks[(i + 1) % numberOfChopsticks]);

    printf("Philosopher %d has finished eating\n", i);

    sem_post(&maxEating);

    printf("Philosopher %d is now leaving the table\n", i);

    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t philosophers[numberOfChopsticks];

    for (int i = 0; i < numberOfChopsticks; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }
    sem_init(&maxEating, 0, 2);

    for (int i = 0; i < numberOfChopsticks; i++) {
        int *id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void *)id);
    }

    for (int i = 0; i < numberOfChopsticks; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < numberOfChopsticks; i++) {
        sem_destroy(&chopsticks[i]);
    }
    sem_destroy(&maxEating);

    return 0;
}
