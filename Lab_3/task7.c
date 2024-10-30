#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int id;
    char name[20];
    int age;
    float pay;
};

int main(int argc, char *argv[]) {
    struct Employee e1 = {1, "John", 25, 5000.0};

    printf("ID: %d\n", e1.id);
    printf("Name: %s\n", e1.name);
    printf("Age: %d\n", e1.age);
    printf("Pay: %.2f\n", e1.pay);

    return 0;
}