// ************************************************************************************************
// OS Lab #7 Task 2
//
// Programmer: Abdullah Nazir
// Date: 02-01-2025
// ************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

double sum = 0;

struct threadArgs {
    int start;
    int end;
    int n;
};

void *computePi(void *args) {
    struct threadArgs *tArgs = (struct threadArgs *) args;
    double threadSum = 0;
    for(int i = tArgs->start; i < tArgs->end; i++) {
        threadSum += (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
    }

    sum += threadSum;
    return NULL;
}

int main(int argc, char *argv[]) {
    int size = argc - 1;
    if(size < 2) {
        printf("Please provide at number of threads and n.\n");
        return -1;
    }
    int numberOfThreads = atoi(argv[1]);
    int n = atoi(argv[2]);
    if(n < 100000 || n % numberOfThreads != 0) {
        printf("Please provide a number n >= 100000 and n should be divisible by number of threads.\n");
        return -1;
    }

    pthread_t threads[numberOfThreads];
    for(int i = 0; i < numberOfThreads; i++) {
        struct threadArgs *args = malloc(sizeof(struct threadArgs));
        args->start = i * (n / numberOfThreads);
        args->end = (i + 1) * (n / numberOfThreads);
        pthread_create(&threads[i], NULL, computePi, (void *) args);
    }

    for(int i = 0; i < numberOfThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    double pi = sum * 4;
    printf("Estimated value of pi is: %.2f\n", pi);

    return 0;
}
