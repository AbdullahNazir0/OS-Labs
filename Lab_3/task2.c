#include <stdio.h>

int main(int argc, char *argv[]){

    int side1, side2, side3;

    printf("Enter three sides of triangle: ");
    scanf("%d %d %d", &side1, &side2, &side3);

    if(side1 == side2 == side3) {
        printf("Equilateral triangle\n");
    } else if(side1 == side2 || side1 == side3 || side2 == side3) {
        printf("Isosceles triangle\n");
    } else {
        printf("Scalene triangle\n");
    }

    return 0;
}