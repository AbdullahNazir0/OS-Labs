#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define READ 0
#define WRITE 1

int find_sum(int[], int);
int find_min(int[], int);

int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		printf("Insufficient command-line arguments\n");
		exit(EXIT_FAILURE);
	}

	int *arr;
	int size = argc - 1;
	arr = malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
	{
		arr[i] = atoi(argv[i + 1]);
	}

	int p_to_c1_fd[2];
	int p_to_c2_fd[2];
	int c1_to_p_fd[2];
	int c2_to_p_fd[2];

	if (pipe(p_to_c1_fd) == -1)
	{
		printf("Pipe failed\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(p_to_c2_fd) == -1)
	{
		printf("Pipe failed\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(c1_to_p_fd) == -1)
	{
		printf("Pipe failed\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(c2_to_p_fd) == -1)
	{
		printf("Pipe failed\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid;
	pid = fork();
	if (pid < 0)
	{
		printf("Fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// child1
		close(c1_to_p_fd[READ]);
		close(c2_to_p_fd[WRITE]);
		close(c2_to_p_fd[READ]);
		close(p_to_c1_fd[WRITE]);
		int received_array_size;
		read(p_to_c1_fd[READ], &received_array_size, sizeof(int));
		int received_array[received_array_size];
		read(p_to_c1_fd[READ], received_array, received_array_size * sizeof(int));
		int sum = find_sum(received_array, received_array_size);
		close(p_to_c1_fd[READ]);
		close(p_to_c2_fd[WRITE]);
		close(p_to_c2_fd[READ]);
		write(c1_to_p_fd[WRITE], &sum, sizeof(int));
		close(c1_to_p_fd[WRITE]);
	}
	else
	{
		pid = fork();
		if (pid < 0)
		{
			printf("Fork failed\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// child2

			close(c2_to_p_fd[READ]);
			close(c1_to_p_fd[WRITE]);
			close(c1_to_p_fd[READ]);
			close(p_to_c1_fd[WRITE]);
			close(p_to_c1_fd[READ]);
			close(p_to_c2_fd[WRITE]);
			int received_array_size;
			read(p_to_c2_fd[READ], &received_array_size, sizeof(int));
			int received_array[received_array_size];
			read(p_to_c2_fd[READ], received_array, received_array_size * sizeof(int));
			int min = find_min(received_array, received_array_size);
			close(p_to_c2_fd[READ]);
			write(c2_to_p_fd[WRITE], &min, sizeof(int));
			close(c2_to_p_fd[WRITE]);
		}
		else
		{
			// parent
			close(c1_to_p_fd[WRITE]);
			close(c2_to_p_fd[WRITE]);
			close(p_to_c1_fd[READ]);
			write(p_to_c1_fd[WRITE], &size, sizeof(int));
			write(p_to_c1_fd[WRITE], arr, size * sizeof(int));
			close(p_to_c1_fd[WRITE]);
			close(p_to_c2_fd[READ]);
			write(p_to_c2_fd[WRITE], &size, sizeof(int));
			write(p_to_c2_fd[WRITE], arr, size * sizeof(int));
			close(p_to_c2_fd[WRITE]);
			int sum, min;
			read(c1_to_p_fd[READ], &sum, sizeof(int));
			close(c1_to_p_fd[READ]);
			read(c2_to_p_fd[READ], &min, sizeof(int));
			close(c2_to_p_fd[READ]);
			printf("The sum of array is: %d\n", sum);
			printf("The min of array is: %d\n", min);
			free(arr);
			wait(NULL);
			wait(NULL);
		}
	}

	return 0;
}

int find_sum(int arr[], int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += arr[i];
	}
	return sum;
}

int find_min(int arr[], int size)
{
	if (size == 0)
	{
		return -1;
	}

	int min = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	return min;
}
