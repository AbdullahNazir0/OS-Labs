#include <stdio.h>

int main(int argc, char *argv[]) {

    int arr[20];
    int size = 20;

    printf("The entered sequence is: \n");
    for(int i = 0; i < 20; i++) {
        scanf("%d", &arr[i]);
        if(arr[i] == -99) {
            size = i;
            break;
        }
    }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size - 1 - i; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("Updated sequence is: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}