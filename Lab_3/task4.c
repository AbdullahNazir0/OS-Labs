#include <stdio.h>

void checkPrimeNumber() {
    int number;
    printf("Enter the number: = ");
    scanf("%d", &number);

    for(int i = 2; i < number; i++) {
        if(number % i == 0) {
            printf("Not Prime\n");
            return;
        }
    }

    printf("Prime\n");
}

int main(int argc, char *argv[]) {
    
    checkPrimeNumber();

    return 0;
}