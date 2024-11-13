#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

int main() {

    char *phrase = "This is a phrase";
    int fd[2], bytes_read;
    pid_t pid;
    char message[100];

    pipe(fd);
    pid = fork();
    if(pid == 0) {
        close(fd[READ]);
        write(fd[WRITE], phrase, strlen(phrase) + 1);
        close(fd[WRITE]);
    } else {
        close(fd[WRITE]);
        bytes_read = read(fd[READ], message, 100);
        printf("Read %d bytes: %s\n", bytes_read, message);
        close(fd[READ]);
    }

    return 0;
}