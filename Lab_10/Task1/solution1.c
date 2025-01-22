#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define numberOfChopsticks 25
sem_t chopsticks[ numberOfChopsticks ];
sem_t table;

void *philosopher(void *args) {
    int i = *(int *)args;
    printf("Philosopher %d is thinking\n", i);

    printf("Philosopher %d is now sitting at the table\n", i);
    sem_wait(&table);

    printf("Philosopher %d is hungry\n", i);

    sem_wait(&chopsticks[i]);
    sem_wait(&chopsticks[(i + 1) % numberOfChopsticks]);

    printf("Philosopher %d is eating\n", i);

    sem_post(&chopsticks[i]);
    sem_post(&chopsticks[(i + 1) % numberOfChopsticks]);

    printf("Philosopher %d has finished eating\n", i);

    printf("Philosopher %d is now leaving the table\n", i);
    sem_post(&table);

    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t philosophers[numberOfChopsticks];

    for (int i = 0; i < numberOfChopsticks; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }
    sem_init(&table, 0, 4);

    for (int i = 0; i < numberOfChopsticks; i++) {
        int *id = (int *)malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&philosophers[i], NULL, philosopher, (void *)id);
    }

    for (int i = 0; i < numberOfChopsticks; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < numberOfChopsticks; i++) {
        sem_destroy(&chopsticks[i]);
    }
    sem_destroy(&table);

    return 0;
}
