#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

struct Input {
    int start; int end;
};

void *threadFactorial(void *args) {
    struct Input *input = (struct Input *)args;

    int *subFactorial = (int *)malloc(sizeof(int));
    *subFactorial = 1;
    for(int i = input->start; i <= input->end; i++) 
        *subFactorial *= i;

    printf("The thread factorial is %d\n", *subFactorial);
    return (void *)subFactorial;
}

int main(int argc, char *argv[]) {

     if (argc != 3) {
        printf("Usage: %s <N> <M>\n", argv[0]);
        return -1;
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    if(N <= 0 || M <= 0 || N < M) {
        printf("Please give valid command line arguments.\n");
        return (-1);
    }

    int perThread = N / M;
    int init = 1;

    pthread_t tids[M];
    struct Input *inputs = (struct Input *)malloc(M * sizeof(struct Input));

    for(int i = 0; i < M; i++) {
        i[inputs].start = init;
        i[inputs].end = (i == M - 1) ? N : (init + perThread - 1);
        init =  i[inputs].end + 1;

        pthread_create(&i[tids], NULL, threadFactorial, (void *)&i[inputs]);
    }

    int factorial = 1;
    for(int i = 0; i < M; i++) {
        int *subFactorial;
        pthread_join(i[tids], (void **)&subFactorial);
        factorial *= *subFactorial;
        free(subFactorial);
    }

    printf("The factorial is %d\n", factorial);

    free(inputs);
    return 0;
}