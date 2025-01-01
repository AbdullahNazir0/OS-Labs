#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

struct Array {
    int *array;
    int size;
};

void *findSum(void *ptr) {
    struct Array *arr = (struct Array *)ptr;
    int *sum = 0;
    for(int i = 0; i < arr->size; i++) {
        *sum += arr->array[i];
    }

    return (void *)sum;
}

int main(int argc, char *argv[]) {
    struct Array arr;
    arr.size = argc - 1;
    if(arr.size < 1) {
        printf("Invalid arguments\n");
        return -1;
    }

    arr.array = (int *)malloc(arr.size * sizeof(int));
    for(int i = 0; i < arr.size; i++) {
        arr.array[i] = atoi(argv[i + 1]);
    }

    pthread_t tid;
    int *result;
    pthread_create(&tid, NULL, findSum, &arr);
    pthread_join(tid, (void **)&result);
    printf("The sum is %d", *result);

    free(arr.array);

    return 0;
}
