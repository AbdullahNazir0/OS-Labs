#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void showFilesAndDirectories() {
    execl("/bin/ls", "ls", "-l", NULL);
}

void renameFileOrDirectory(char *oldName, char *newName) {
    execl("/bin/mv", "mv", oldName, newName, NULL);
}

void deleteFileOrDirectory(char *name) {
    execl("/bin/rm", "rm", "-r", name, NULL);
}

int main() {

    pid_t pid;
    int choice;
    while(1) {
        pid = fork();
        if(pid < 0) {
            printf("Error\n");
            exit(1);
        }
        if(pid == 0) {
            printf("\nCurrent files and directories:\n");
            showFilesAndDirectories();
        } else {
            wait(NULL);
            printf("\nEnter 1 to rename a file or directory\n");
            printf("Enter 2 to delete a file or directory\n");
            printf("Enter 3 to exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();
            switch(choice) {
                case 1: {
                    char oldName[100], newName[100];
                    printf("Enter the old name(case sensitive): ");
                    scanf("%s", oldName);
                    printf("Enter the new name: ");
                    scanf("%s", newName);
                    pid = fork();
                    if(pid < 0) {
                        printf("Error\n");
                        exit(1);
                    }
                    if(pid == 0) {
                        renameFileOrDirectory(oldName, newName);
                    } else {
                        wait(NULL);
                        printf("File Renamed Successfully\n");
                    }
                    break;
                }
                case 2: {
                    char name[100];
                    printf("Enter the name(case sensitive): ");
                    scanf("%s", name);
                    getchar();
                    pid = fork();
                    if(pid < 0) {
                        printf("Error\n");
                        exit(1);
                    }
                    if(pid == 0) {
                        printf("Are you sure you want to delete the file or directory? (y/n): ");
                        char confirm;
                        scanf("%c", &confirm);
                        if (confirm == 'y' || confirm == 'Y') {
                            deleteFileOrDirectory(name);
                        }
                    } else {
                        wait(NULL);
                        printf("File Deleted Successfully\n");
                    }
                    break;
                }
                case 3: {
                    exit(0);
                }
                default: {
                    printf("Invalid choice\n\n");
                }
            }
        }
    }
}