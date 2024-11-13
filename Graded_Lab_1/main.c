#include <stdio.h>
#include <stdlib.h>

int findSum(int[], int);
double findAverage(int[], int);
int findMin(int[], int);
int findMax(int[], int);

int main(int argc, char *argv[]) {

    // Get integer array from terminal
    int size = argc - 1;
    int arr[size];
    for(int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    printf("The sum is %d\n", findSum(arr, size));
    printf("The average is %f\n", findAverage(arr, size));
    printf("The min is %d\n", findMin(arr, size));
    printf("The max is %d\n", findMax(arr, size));

    return 1;
}

int findSum(int arr[], int size) {
    int s = 0;
    for (int i = 0; i < size; i++) {
        s += arr[i];
    }
    return s;
}

double findAverage(int arr[], int size) {
    int sum = findSum(arr, size);
    if(sum == 0) {
      return 0.0;
    }
    return sum / size;
}

int findMin(int arr[], int size) {
    if(size == 0) {
        return -1;
    }

    int min = arr[0];
    for(int i = 1; i < size; i++) {
	if(arr[i] < min) {
		min = arr[i];
	}
    }
    return min;
}

int findMax(int arr[], int size) {
    if (size == 0) {
        return -1;
    }

    int max = arr[0];
    for(int i = 1; i < size; i++) {
	    if(arr[i] > max) {
		    max = arr[i];
	    }
    }
    return max;
}
