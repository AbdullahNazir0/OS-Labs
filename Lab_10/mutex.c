#include <stdio.h>
#include <pthread.h>

int val = 0;
pthread_mutex_t mutex;

void *increment(void *args) {
    pthread_mutex_lock(&mutex);
    val++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *decrement(void *args) {
    pthread_mutex_lock(&mutex);
    val--;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;
    for(long int i = 0; i < 10000000000000; i++) {
        pthread_create(&t1, NULL, increment, NULL);
        pthread_create(&t2, NULL, decrement, NULL);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
    }

    printf("The value of val is %d\n", val);

    return 0;
}
