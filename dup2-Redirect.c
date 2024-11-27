#include <stdio.h>     //printf, scanf
#include <stdlib.h>    //atoi, malloc
#include <unistd.h>    //dup2, fork(), pipe
#include <sys/types.h> // data types for system calls such as pid_t which we used in class
// new header file we will be using in next class used to solve lab 6
#include <sys/file.h> //contains the O_CREAT, O_TRUNC, O_RDWR

// O_CREAT: Create the file if it does not exist.
// O_TRUNC: If the file exists, truncate (empty) its contents.
// O_RDWR: Open the file for both reading and writing.

// Lab 6 Task
// ls / -l > input.txt

int main()
{
    int fd; // File descriptor which we will use to store the open function value.

    // 0777: File permissions (read, write, execute for owner, group, and others).
    fd = open("input.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);
    // So in line 20 we are opening the input.txt file with permission parameters.
    // 0777 is read write execute.

    dup2(fd, 1);
    // in line 25 we have used dup2 to redirect the output of terminal to be stored in input.txt instead of terminal.

    execlp("ls", "ls", "-l", NULL);
}
