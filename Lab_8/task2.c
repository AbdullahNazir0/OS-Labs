#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>

void calculateAverage(int *numbers, int count) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    double average = sum / count;
    printf("Average: %.2f\n", average);
}

void findMinMax(int *numbers, int count) {
    int min = numbers[0];
    int max = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] < min) min = numbers[i];
        if (numbers[i] > max) max = numbers[i];
    }
    printf("Minimum: %d, Maximum: %d\n", min, max);
}

void sortNumbers(int *numbers, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
    printf("Sorted List: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

void setAffinity(int cpu_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu_id, &cpuset);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) == -1) {
        perror("sched_setaffinity failed");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Insufficient arguments.\n");
        exit(1);
    }

    int count = argc - 1;
    int numbers[count];
    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    pid_t pids[3];
    for (int i = 0; i < 3; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork failed");
            exit(1);
        } else if (pids[i] == 0) {
            setAffinity(i % sysconf(_SC_NPROCESSORS_ONLN)); // Assign CPU
            if (i == 0) {
                calculateAverage(numbers, count);
            } else if (i == 1) {
                findMinMax(numbers, count);
            } else if (i == 2) {
                sortNumbers(numbers, count);
            }
            exit(0);
        }
    }

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}
