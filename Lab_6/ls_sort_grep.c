#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    int ls_sort_fd[2];
    int sort_grep_fd[2];
    pipe(ls_sort_fd);
    pipe(sort_grep_fd);

    pid_t pid1 = fork();
    if(pid1 < 0) {
        exit(-1);
    }
    if(pid1 == 0) {
        close(ls_sort_fd[0]);
        dup2(ls_sort_fd[1], 1);
        close(ls_sort_fd[1]);
        execlp("ls", "ls", NULL);
        return 0;
    }

    pid_t pid2 = fork();
    if(pid2 < 0) {
        exit(-1);
    }
    if(pid2 == 0) {
        close(ls_sort_fd[1]);
        close(sort_grep_fd[0]);
        dup2(ls_sort_fd[0], 0);
        close(ls_sort_fd[0]);
        dup2(sort_grep_fd[1], 1);
        close(sort_grep_fd[1]);
        execlp("sort", "sort", "-r", NULL);
        return 0;
    }

    pid_t pid3 = fork();
    if(pid3 < 0) {
        exit(-1);
    }
    if(pid3 == 0) {
        close(sort_grep_fd[1]);
        dup2(sort_grep_fd[0], 0);
        close(sort_grep_fd[0]);
        execlp("grep", "grep", "b", NULL);
        return 0;
    }

    close(ls_sort_fd[0]);
    close(ls_sort_fd[1]);
    close(sort_grep_fd[0]);
    close(sort_grep_fd[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
