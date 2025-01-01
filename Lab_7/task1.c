// ************************************************************************************************
// OS Lab #7 Task 1
//
// Programmer: Abdullah Nazir
// Date: 01-01-2025
// ************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

int SIZE = 0;

void *findAverage(void *args) {
    int *arr = (int *)args;
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += arr[i];
    }
    printf("The average value is %.2f\n", (float)sum / SIZE);
    return NULL;
}

void *findMax(void *args) {
    int *arr = (int *)args;
    int max = arr[0];
    for (int i = 1; i < SIZE; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    printf("The maximum value is %d\n", max);
    return NULL;
}

void *findMin(void *args) {
    int *arr = (int *)args;
    int min = arr[0];
    for (int i = 1; i < SIZE; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    printf("The minimum value is %d\n", min);
    return NULL;
}

int main(int argc, char *argv[]) {
    SIZE = argc - 1;
    if(SIZE < 1) {
        printf("Please provide some numbers\n");
        return -1;
    }
    int *arr = (int *)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, findAverage, (void *)arr);
    pthread_create(&thread2, NULL, findMax, (void *)arr);
    pthread_create(&thread3, NULL, findMin, (void *)arr);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    free(arr);
    return 0;
}
