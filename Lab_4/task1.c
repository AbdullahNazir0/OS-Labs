#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {

    // The tree to get from fork
    //             Parent
    //      Child                   child         child
    // child        child       child
    // child child

    // parent -> child1, child2, child3
    // child1 -> child5, child6
    // child5 -> child7, child8
    // child2 -> child4

    pid_t pid;
    pid = fork();
    if(pid < 0) {
        printf("Fork failed\n");
    } else if(pid == 0) {
        // child 1
        printf("Child 1\n");
        pid = fork();
        if(pid < 0) {
            printf("Fork failed\n");
        } else if(pid == 0) {
            // child 5
            printf("Child 5 (child of child 1)\n");
            pid = fork();
            if(pid < 0) {
                printf("Fork failed\n");
            } else if(pid == 0) {
                // child 7
                printf("Child 7 (child of child 5)\n");
            } else {
                // parent
                pid = fork();
                if(pid < 0) {
                    printf("Fork failed\n");
                } else if(pid == 0) {
                    // child 8
                    printf("Child 8 (child of child 5)\n");
                } else {
                    // parent
                }
            }
        } else {
            // parent
            pid = fork();
            if(pid < 0) {
                printf("Fork failed\n");
            } else if(pid == 0) {
                // child 6
                printf("Child 6 (child of child 1)\n");
            } else {
                // parent
            }
        }
    } else {
        // parent
        pid = fork();
        if(pid < 0) {
            printf("Fork failed\n");
        } else if(pid == 0) {
            // child 2
            printf("Child 2\n");
            pid = fork();
            if(pid < 0) {
                printf("Fork failed\n");
            } else if(pid == 0) {
                // child 4
                printf("Child 4 (child of child 2)\n");
            } else {
                // parent
            }
        } else {
            // parent
            pid = fork();
            if(pid < 0) {
                printf("Fork failed\n");
            } else if(pid == 0) {
                // child 3
                printf("Child 3\n");
            } else {
                // parent
            }
        }
    }

}