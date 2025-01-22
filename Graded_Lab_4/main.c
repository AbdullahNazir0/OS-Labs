#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long int factorial = 1;
pthread_mutex_t mutex;

struct Input {
    int start;
    int end;
};

void *findFactorial(void *args) {
    struct Input *input = (struct Input *)args;
    // long int partialResult = 1;

    for(int i = input->start; i <= input->end; i++) {
        pthread_mutex_lock(&mutex);
        factorial *= i;
        pthread_mutex_unlock(&mutex);
    }

    // pthread_mutex_lock(&mutex);
    // factorial *= partialResult;
    // pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[]) {

    int N = atoi(argv[1]);
    if(!N) {
        printf("Invalid input\n");
        return 0;
    }

    pthread_t t1, t2;
    struct Input input1, input2;
    input1.start = 1;
    input1.end = N/2;
    input2.start = N/2 + 1;
    input2.end = N;

    pthread_create(&t1, NULL, findFactorial, (void *)&input1);
    pthread_create(&t2, NULL, findFactorial, (void *)&input2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("The factorial of %d is %ld\n", N, factorial);
    return 0;
}
