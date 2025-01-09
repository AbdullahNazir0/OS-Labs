#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <sys/sysinfo.h>

void computePiChunk(long int start, long int end, double dx, int processIndex, int totalProcesses, int writeFd) {
    cpu_set_t cpuSet;
    CPU_ZERO(&cpuSet);
    CPU_SET(processIndex % totalProcesses, &cpuSet);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuSet) == -1) {
        perror("sched_setaffinity failed");
        exit(1);
    }

    double localSum = 0.0;
    for (long int i = start; i < end; i++) {
        double x = (i + 0.5) * dx;
        localSum += 4.0 / (1.0 + x * x);
    }

    if (write(writeFd, &localSum, sizeof(double)) == -1) {
        perror("write to pipe failed");
        exit(1);
    }

    close(writeFd);
    exit(0);
}

int main() {
    long int numSteps = 10000000;
    double dx = 1.0 / numSteps;
    int numCpus = get_nprocs();

    printf("Number of CPUs available: %d\n", numCpus);

    long int stepsPerCpu = numSteps / numCpus;
    int pipes[numCpus][2];

    for (int i = 0; i < numCpus; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe failed");
            exit(1);
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process
            close(pipes[i][0]);
            long int start = i * stepsPerCpu;
            long int end = (i == numCpus - 1) ? numSteps : start + stepsPerCpu;
            computePiChunk(start, end, dx, i, numCpus, pipes[i][1]);
        }

        close(pipes[i][1]);
    }

    double pi = 0.0;
    for (int i = 0; i < numCpus; i++) {
        double localSum = 0.0;
        if (read(pipes[i][0], &localSum, sizeof(double)) == -1) {
            perror("read from pipe failed");
            exit(1);
        }
        pi += localSum;
        close(pipes[i][0]);
    }

    pi *= dx;

    printf("Computed value of π: %.15lf\n", pi);

    return 0;
}
