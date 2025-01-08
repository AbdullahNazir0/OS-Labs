#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

struct ThreadArgs {
    int *arr;
    int start;
    int end;
};
struct SecondThreadResult {
    double mean;
    int median;
    int mode;
};

void *find3rdMax(void *args);
void *findMeanMedianMode(void *args);
double findMean(int *arr, int start, int end);
int findMedian(int *arr, int start, int end);
int findMode(int *arr, int start, int end);

int main(int argc, char **argv) {

    int size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    pthread_t t1, t2;
    struct ThreadArgs *targs1 = malloc(sizeof(struct ThreadArgs));
    struct ThreadArgs *targs2 = malloc(sizeof(struct ThreadArgs));

    int mid = size / 2;
    targs1->arr = arr;
    targs1->start = 0;
    targs1->end = mid;

    targs2->arr = arr;
    targs2->start = mid;
    targs2->end = size;

    pthread_create(&t1, NULL, find3rdMax, (void *)targs1);
    pthread_create(&t2, NULL, findMeanMedianMode, (void *)targs2);

    int *thirdMax;
    struct SecondThreadResult *result;

    pthread_join(t1, (void *)&thirdMax);
    pthread_join(t2, (void *)&result);

    printf("The third max is %d\n", *thirdMax);
    printf("The mean is %.2f\n", result->mean);
    printf("The median is %d\n", result->median);
    printf("The mode is %d\n", result->mode);

    free(arr);
    free(targs1);
    free(targs2);
    free(thirdMax);
    free(result);

    return 0;
}

void *find3rdMax(void *args) {
    struct ThreadArgs *tArgs = (struct ThreadArgs *)args;

    int max = -1, secondMax = -1, thirdMax = -1;
    for(int i = tArgs->start; i < tArgs->end; i++) {
        if(tArgs->arr[i] > max) {
            thirdMax = secondMax;
            secondMax = max;
            max = tArgs->arr[i];
        } else if(tArgs->arr[i] > secondMax) {
            thirdMax = secondMax;
            secondMax = tArgs->arr[i];
        } else if(tArgs->arr[i] > thirdMax) {
            thirdMax = tArgs->arr[i];
        }
    }

    if (thirdMax == -1) {
            thirdMax = max;
        }

    int *result = (int *)malloc(sizeof(int));
    *result = thirdMax;
    return (void *)result;
}
void *findMeanMedianMode(void *args) {
    struct ThreadArgs *tArgs = (struct ThreadArgs *)args;

    struct SecondThreadResult *result = (struct SecondThreadResult *)malloc(sizeof(struct SecondThreadResult));
    result->mean = findMean(tArgs->arr, tArgs->start, tArgs->end);
    result->median = findMedian(tArgs->arr, tArgs->start, tArgs->end);
    result->mode = findMode(tArgs->arr, tArgs->start, tArgs->end);

    return (void *)result;
}
double findMean(int *arr, int start, int end) {
    double mean = 0;
    for(int i = start; i < end; i++) {
        mean += arr[i];
    }
    mean /= (end - start);
    return mean;
}
int findMedian(int *arr, int start, int end) {
    int size = end - start;
    // for(int i = start; i < end - 1; i++) {
    //     int flag = 0;
    //     for(int j = start; j < end - 1 - i; j++) {
    //         if(arr[j] > arr[j + 1]) {
    //             int temp = arr[j];
    //             arr[j] = arr[j + 1];
    //             arr[j + 1] = temp;
    //             flag = 1;
    //         }
    //     }
    //     if(flag == 0)
    //         break;
    // }

    // if(size % 2 != 0)
    //     return arr[size / 2];

    // return (arr[(size / 2) - 1] + arr[size / 2]) / 2;

    int *temp = (int *)malloc(size * sizeof(int)); // Copy array
    for (int i = 0; i < size; i++) {
        temp[i] = arr[start + i];
    }

    // Sort copied array
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (temp[j] > temp[j + 1]) {
                int tempVal = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = tempVal;
            }
        }
    }

    int median = (size % 2 == 0) ? (temp[size / 2 - 1] + temp[size / 2]) / 2 : temp[size / 2];
    free(temp);
    return median;
}
int findMode(int *arr, int start, int end) {
    int size = end - start;

    // int *freq = (int *)malloc(size * sizeof(int));
    // for(int i = start; i < end; i++) {
    //     freq[i] = 0;
    //     for(int j = start; j < end; j++) {
    //         if(arr[i] == arr[j] && i != j) {
    //             freq[i]++;
    //         }
    //     }
    // }
    // int mode = freq[0];
    // for(int i = start; i < end; i++) {
    //     if(freq[i] > mode) {
    //         mode = freq[i];
    //     }
    // }
    // free(freq);
    // return mode;

    int max = arr[0];
    for(int i = start + 1; i < end; i++) {
        if(arr[i] > max)
            max = arr[i];
    }
    int freq[max + 1];
    for(int i = 0; i < max; i++) {
        freq[i] = 0;
    }
    for(int i = start; i < end; i++) {
        freq[arr[i]]++;
    }
    int mode = arr[0];
    int maxFreq = freq[arr[0]];
    for(int i = start; i < end; i++) {
        if(freq[arr[i]] > maxFreq) {
            maxFreq = freq[arr[i]];
            mode = arr[i];
        }
    }
    return mode;
}
