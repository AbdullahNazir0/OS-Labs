#include <stdio.h>

int main(int argc, char *argv[])
{

    int length, width;
    printf("What is the length of rectangle? ");
    scanf("%d", &length);
    printf("What is the width of rectangle? ");
    scanf("%d", &width);

    int area = length * width;
    printf("The area of rectangle is %d", area);

    return 0;
}