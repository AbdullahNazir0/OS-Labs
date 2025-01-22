// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>

// pthread_mutex_t mutex;
// int arr[10];
// int s = 10;

// void *producer(void *args) {
//     for(int i = 0; i < s; i++) {
//         pthread_mutex_lock(&mutex);
//         arr[i] = rand() % 10;
//         pthread_mutex_unlock(&mutex);
//     }
//     return NULL;
// }

// void *consumer(void *args) {
//     for(int i = 0; i < s; i++) {
//         pthread_mutex_lock(&mutex);
//         printf("%d ", arr[i]);
//         pthread_mutex_unlock(&mutex);
//     }
//     return NULL;
// }

// int main(int argc, char *argv[]) {

//     pthread_t t1, t2;
//     pthread_create(&t1, NULL, producer, NULL);
//     pthread_create(&t2, NULL, consumer, NULL);

//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);

//     return 0;
// }


// #include <stdio.h>
// #include <pthread.h>

// pthread_mutex_t mutex;
// int in = 0;
// int out = 0;
// int arr[10];
// int count = 0;

// void *producer(void *args) {
//     for(int i = 0; i < 10; i++){
//         while(count == 10) {}

//         arr[in] = i;
//         in = (in + 1) % 10;

//         pthread_mutex_lock(&mutex);
//         count--;
//         pthread_mutex_unlock(&mutex);
//     }
//     return NULL;
// }

// void *consumer(void *args) {
//     for(int i = 0; i < 10; i++) {
//         while(count == 0) {}

//         printf("%d ", arr[out]);
//         out = (out + 1) % 10;

//         pthread_mutex_lock(&mutex);
//         count--;
//         pthread_mutex_unlock(&mutex);
//     }
//     return NULL;
// }

// int main(int argc, char *argv[]) {

//     pthread_t t1, t2;
//     pthread_create(&t1, NULL, producer, NULL);
//     pthread_create(&t2, NULL, consumer, NULL);

//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);

//     return 0;
// }


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// pthread_mutex_t mutex;
int s = 10;
int in = 0;
int out = 0;
int arr[10];
int count = 0;

void *producer(void *args) {
    for(int i = 0; i < 10; i++){
        while(count == 10) {}

        arr[in] = i;
        in = (in + 1) % 10;

        sem_wait(&s);
        count--;
        sem_post(&s);
    }
    return NULL;
}

void *consumer(void *args) {
    for(int i = 0; i < 10; i++) {
        while(count == 0) {}

        printf("%d ", arr[out]);
        out = (out + 1) % 10;

        sem_wait(&s);
        count++;
        sem_post(&s);
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t t1, t2;
    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
