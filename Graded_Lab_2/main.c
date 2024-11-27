#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int size = argc - 1;

	int p_to_c1_fd[2];
	int p_to_c2_fd[2];
	pipe(p_to_c1_fd);
	pipe(p_to_c2_fd);

	pid_t pid;
	pid = fork();
	if(pid < 0) {
		printf("Fork Failed\n");
		exit(-1);
	}
	if(pid == 0) {
		// child 1
		close(p_to_c2_fd[0]);
		close(p_to_c2_fd[1]);
		close(p_to_c1_fd[1]);
		int *child1Array = (int *)malloc(size * sizeof(int));
		read(p_to_c1_fd[0], child1Array, size * sizeof(int));
		close(p_to_c2_fd[0]);
		double avg = 0;
		for(int i = 0; i < size; i++) {
			avg += child1Array[i];
		}
		avg /= size;
		printf("Average: %f\n", avg);
	} else {
		// parent 
		pid = fork();
		if(pid < 0) {
			printf("Fork Failed\n");
			exit(-1);
		}
		if(pid == 0) {
			// child 2
			close(p_to_c1_fd[0]);
			close(p_to_c1_fd[1]);
			close(p_to_c2_fd[1]);
			int *child2Array = (int *)malloc(size * sizeof(int));
			read(p_to_c2_fd[0], child2Array, size * sizeof(int));
			close(p_to_c2_fd[0]);
			if(size < 2) {
				printf("Second Max: %d\n", -1);
				exit(0);
			}
			int max = child2Array[0];
			int secondMax = child2Array[1];
			if(max < secondMax) {
				int temp = max;
				max = secondMax;
				secondMax = temp;
			}
			for(int i = 2; i < size; i++) {
				if(child2Array[i] > max) {
					secondMax = max;
					max = child2Array[i];
				}
			}
			printf("Second Max: %d\n", secondMax);
		} else {
			// parent
			close(p_to_c1_fd[0]);
			close(p_to_c2_fd[0]);
			int *arr = (int *)malloc(size * sizeof(int));
	                for(int i = 0; i < size; i++) {
		                arr[i] = atoi(argv[i + 1]);
	                }
			write(p_to_c1_fd[1], arr, size * sizeof(int));
			write(p_to_c2_fd[1], arr, size * sizeof(int));
			close(p_to_c1_fd[1]);
			close(p_to_c2_fd[1]);
			wait(NULL);
		}
	}
}
