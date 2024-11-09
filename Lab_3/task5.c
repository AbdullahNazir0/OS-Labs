#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if(argc < 3) {
        printf("Insufficient arguments");
        return -1;
    }

    int num1, num2;
    num1 = atoi(argv[1]);
    num2 = atoi(argv[2]);

    int product = num1 * num2;

    printf("The product is: %d", product);

    return 0;
}