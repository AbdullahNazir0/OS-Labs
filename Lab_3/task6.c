#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int size = argc - 1;
    int *array = (int *) malloc(size * sizeof(int));

    for(int i = 0; i < size; i++){
        array[i] = atoi(argv[i + 1]);
    }

    int min = array[0];
    int secondMin = array[0];
    if (array[0] < array[1]) {
        min = array[0];
        secondMin = array[1];
    } else {
        min = array[1];
        secondMin = array[0];
    }

    for (int i = 2; i < size; i++) {
        if (array[i] < min) {
            secondMin = min;
            min = array[i]; 
        } else if (array[i] < secondMin && array[i] != min) {
            secondMin = array[i]; 
        }
    }

    printf("Second Min: %d", secondMin);

    return 0;
}