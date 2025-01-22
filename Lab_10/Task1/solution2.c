#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define numberOfChopsticks 5
sem_t chopsticks[ numberOfChopsticks ];
sem_t lock; // for critical section to check if both are available

void *philosopher(void *args) {
    int i = *(int *)args;
    printf("Philosopher %d is thinking\n", i);

    sem_wait(&lock);

    printf("Philosopher %d is hungry\n", i);

    if(sem_trywait(&chopsticks[i]) == 0 || sem_trywait(&chopsticks[(i + 1) % numberOfChopsticks]) == 0) {
        printf("Philosopher %d is eating\n", i);
    } else {
        if (sem_trywait(&chopsticks[i]) == 0) {
            sem_post(&chopsticks[i]);
        }
        if (sem_trywait(&chopsticks[(i + 1) % numberOfChopsticks]) == 0) {
            sem_post(&chopsticks[(i + 1) % numberOfChopsticks]);
        }
        printf("Philosopher %d is waiting for chopsticks\n", i);
    }

    sem_post(&lock);

    sem_post(&chopsticks[i]);
    sem_post(&chopsticks[(i + 1) % numberOfChopsticks]);

    printf("Philosopher %d has finished eating\n", i);

    printf("Philosopher %d is now leaving the table\n", i);

    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t philosophers[numberOfChopsticks];

    for (int i = 0; i < numberOfChopsticks; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }
    sem_init(&lock, 0, 1);

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
    sem_destroy(&lock);

    return 0;
}
