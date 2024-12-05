#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char *argv[]) {
    int size = argc - 1;

    int p_to_c1[2];
    int p_to_c2[2];
    int c1_to_p[2];
    int c2_to_p[2];

    pipe(p_to_c1);
    pipe(p_to_c2);
    pipe(c1_to_p);
    pipe(c2_to_p);

    pid_t pid;
    pid = fork();
    if(pid < 0) {
        printf("Fork failed\n");
        exit(-1);
    }
    if(pid == 0) {
        // child1

        // close unused pipe ends.
        close(p_to_c1[1]);
        close(p_to_c2[0]);
        close(p_to_c2[1]);
        close(c1_to_p[0]);
        close(c2_to_p[0]);
        close(c2_to_p[1]);

        // read from parent
        int *child1arr = (int *)malloc(size * sizeof(int));
        read(p_to_c1[0], child1arr, size * sizeof(int));
        close(p_to_c1[0]);

        // calculate sum and average
        int sum = 0;
        for(int i = 0; i < size; i++) {
            sum += child1arr[i];
        }
        double average = (double)sum / size;

        // display and write to parent
        printf("Child 1: \n");
        printf("Sum: %d\n", sum);
        printf("Average: %f\n", average);
        write(c1_to_p[1], &average, sizeof(double));
        close(c1_to_p[1]);

        free(child1arr);
    } else {
        pid = fork();
        if(pid < 0) {
            printf("Fork failed\n");
            exit(-1);
        }
        if(pid == 0) {
            // child2

            // close unused pipe ends.
            close(p_to_c1[0]);
            close(p_to_c1[1]);
            close(p_to_c2[1]);
            close(c1_to_p[0]);
            close(c1_to_p[1]);
            close(c2_to_p[0]);

            // read from parent
            int *child2arr = (int *)malloc(size * sizeof(int));
            read(p_to_c2[0], child2arr, size * sizeof(int));
            close(p_to_c2[0]);

            // calculate second minimum
            int min, secondMin;
            if(size <= 1) {
                min = -1, secondMin = -1;
            } else {
                min = child2arr[0], secondMin = child2arr[1];
                if(secondMin < min) {
                    swap(&min, &secondMin);
                }
            }
            for(int i = 2; i < size; i++) {
                if(child2arr[i] < min) {
                    secondMin = min;
                    min = child2arr[i];
                } else if(child2arr[i] < secondMin) {
                    secondMin = child2arr[i];
                }
            }

            // display and write to parent
            printf("Child 2: \n");
            printf("Second minimum: %d\n", secondMin);
            write(c2_to_p[1], &secondMin, sizeof(int));
            close(c2_to_p[1]);

            free(child2arr);
        } else {
            // parent

            // close unused pipe ends.
            close(p_to_c1[0]);
            close(p_to_c2[0]);
            close(c1_to_p[1]);
            close(c2_to_p[1]);

            // extract values from terminal
            int *arr = (int *)malloc(size * sizeof(int));
            for(int i = 0; i < size; i++) {
                arr[i] = atoi(argv[i + 1]);
            }

            // write extracted values array to pipes
            write(p_to_c1[1], arr, size * sizeof(int));
            write(p_to_c2[1], arr, size * sizeof(int));
            close(p_to_c1[1]);
            close(p_to_c2[1]);

            // wait for childs to complete
            wait(NULL);
            wait(NULL);

            // read from childs
            double average;
            int secondMin;
            read(c1_to_p[0], &average, sizeof(double));
            read(c2_to_p[0], &secondMin, sizeof(int));
            close(c1_to_p[0]);
            close(c2_to_p[0]);

            // print data
            printf("Parent:\n");
            printf("Average recieved from child1: %f\n", average);
            printf("Second minimum recieved from child2: %d\n", secondMin);

            free(arr);
        }
    }

}
