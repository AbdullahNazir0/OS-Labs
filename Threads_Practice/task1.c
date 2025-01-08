#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int size = 0;

void *findMean(void *args) {
    int *arr = (int *)args;
    int *sum = (int *)malloc(sizeof(int));
    for (int i = 0; i < size; i++) {
        *sum += arr[i];
    }
    double *mean = (double *)malloc(sizeof(double));
    *mean = (double)(*sum) / size;
    return (void *)mean;
}
void *find4thMax(void *args) {
    int *arr = (int *)args;
    int max = arr[0];
    int secMan = arr[1];
    int thirdMax = arr[2];
    int fourthMax = arr[3];

    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            fourthMax = thirdMax;
            thirdMax = secMan;
            secMan = max;
            max = arr[i];
        } else if (arr[i] > secMan) {
            fourthMax = thirdMax;
            thirdMax = secMan;
            secMan = arr[i];
        } else if (arr[i] > thirdMax) {
            fourthMax = thirdMax;
            thirdMax = arr[i];
        } else if (arr[i] > fourthMax) {
            fourthMax = arr[i];
        }
    }

    int *res = (int *)malloc(sizeof(int));
    *res = fourthMax;
    return (void *)res;
}
void *find2ndMin(void *args) {
    int *arr = (int *)args;
    int min = arr[0];
    int secMin = arr[1];

    for (int i = 0; i < size; i++) {
        if (arr[i] < min) {
            secMin = min;
            min = arr[i];
        } else if (arr[i] < secMin) {
            secMin = arr[i];
        }
    }

    int *res = (int *)malloc(sizeof(int));
    *res = secMin;
    return (void *)res;
}
int isPrime(int num) {
    int flag = 0;
    for(int i = 2; i < num / 2; i++) {
        if(num % i == 0) {
            return 0;
        }
    }
    return 1;
}
void *findEvenOddPrime(void *args) {
    int *arr = (int *)args;
    int count = 0;
    printf("Even Numbers:");
    for(int i = 0; i < size; i++) {
        if(arr[i] % 2 == 0) {
            printf(" %d ", arr[i]);
            count++;
        }
    }
    printf("\nTotal Even Numbers are: %d", count);
    printf("\nOdd Numbers:");
    count = 0;
    for(int i = 0; i < size; i++) {
        if(arr[i] % 2 != 0) {
            printf(" %d ", arr[i]);
            count++;
        }
    }
    printf("\nTotal Even Numbers are: %d", count);
    printf("\nPrime Numbers:");
    int flag = 0;
    count = 0;
    for(int i = 0; i < size; i++) {
        if(isPrime(arr[i]) && arr[i] != 0 && arr[i] != 1) {
            printf(" %d ", arr[i]);
            count++;
        }
    }
    printf("\nTotal Prime Numbers: %d\n", count);
}

int main(int argc, char *argv[]) {

    size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    pthread_t p1, p2, p3, p4;
    pthread_create(&p1, NULL, findMean, (void *)arr);
    pthread_create(&p2, NULL, find4thMax, (void *)arr);
    pthread_create(&p3, NULL, find2ndMin, (void *)arr);
    pthread_create(&p4, NULL, findEvenOddPrime, (void *)arr);

    double *mean;
    int *fourthMax;
    int *secondMin;

    pthread_join(p1, (void *)&mean);
    pthread_join(p2, (void *)&fourthMax);
    pthread_join(p3, (void *)&secondMin);
    pthread_join(p4, NULL);

    printf("The mean of array is: %.2f\n", *mean);
    printf("The fourth max of array is: %d\n", *fourthMax);
    printf("The second min of array is: %d\n", *secondMin);

    free(arr);
    free(mean);
    free(fourthMax);
    free(secondMin);

    return 0;
}
