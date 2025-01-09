#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int numOfCPUs;
    numOfCPUs = sysconf(_SC_NPROCESSORS_ONLN);
    if (numOfCPUs == -1) {
        printf("Error retrieving the number of CPUs");
        return 1;
    }

    printf("Number of CPUs: %d\n", numOfCPUs);
    int selectedCPU;
    printf("Select a CPU (0 to %d): ", numOfCPUs - 1);
    scanf("%d", &selectedCPU);
    if (selectedCPU < 0 || selectedCPU >= numOfCPUs) {
        printf("Invalid CPU selection!\n");
        return 1;
    }

    char tasksetCommand[100];
    snprintf(tasksetCommand, sizeof(tasksetCommand), "taskset -c %d", selectedCPU);

    while (1) {
        char command[256];
        printf("Enter a command to run on CPU %d (or type 'exit' to quit): ", selectedCPU);
        getchar();
        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            printf("Exiting the program.\n");
            break;
        }

        char final_command[512];
        snprintf(final_command, sizeof(final_command), "%s %s", tasksetCommand, command);

        printf("Running: %s\n", final_command);
        system(final_command);
    }

    return 0;
}
