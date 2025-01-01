// ************************************************************************************************
// OS Lab #7 Task 3
//
// Programmer: Abdullah Nazir
// Date: 01-01-2025
// ************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>

volatile int found = 0;

struct FileData {
    char *filename;
    char *string;
    int startLine;
    int endLine;
    pthread_t threadId;
};

void *findString(void *args) {
    struct FileData *data = (struct FileData *)args;
    FILE *file = fopen(data->filename, "r");
    if(file == NULL) {
        printf("File not found\n");
        return NULL;
    }

    char line[1024];
    int lineNum = 1;
    while (lineNum < data->startLine && fgets(line, 1024, file)) {
        lineNum++;
    }
    while (lineNum <= data->endLine && fgets(line, 1024, file)) {
        if (found) {
            fclose(file);
            return NULL;
        }

        char* pos = strstr(line, data->string);
        if (pos != NULL) {
            found = 1;
            int column = (int)(pos - line + 1);
            printf(
                "Thread %lu: Found string '%s' at line %d, column %d\n", // %lu is for unsigned long
                data->threadId,
                data->string,
                lineNum,
                column
            );
            fclose(file);
            return NULL;
        }
        lineNum++;
    }
    fclose(file);
    return NULL;
}

int main(int argc, char *argv[]) {
    int size = argc - 1;
    if(size < 3) {
        printf("Please provide valid file name, number and string\n");
        return -1;
    }

    char *filename = argv[1];
    int number = atoi(argv[2]);
    if(number < 1) {
        printf("Please provide a valid number\n");
        return -1;
    }

   FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("File not found\n");
        return -1;
    }

    int lines = 0;
    char line[1024];
    while (fgets(line, 1024, file)) {
        lines++;
    }
    fclose(file);

    int linesPerThread = lines / number;
    int remainingLines = lines % number;

    pthread_t threads[number];
    struct FileData data[number];
    int startLine = 1;
    for(int i = 0; i < number; i++) {
        int endLine = startLine + linesPerThread - 1;
        if(remainingLines > 0) {
            endLine++;
            remainingLines--;
        }

        data[i].filename = filename;
        data[i].string = argv[3];
        data[i].startLine = startLine;
        data[i].endLine = endLine;
        data[i].threadId = i + 1;
        pthread_create(&threads[i], NULL, findString, &data[i]);
        startLine = endLine + 1;
    }

    for(int i = 0; i < number; i++) {
        pthread_join(threads[i], NULL);
    }

    if (!found) {
        printf("String '%s' not found in the file.\n", argv[3]);
    }

    return 0;
}
