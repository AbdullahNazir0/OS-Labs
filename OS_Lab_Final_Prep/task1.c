// Define a 2D Array of size 4 by , name it A , take input from user , define 4 seperate 1D arrays of size 4 , name them B,C,D,E , using threads , mutex concept , write a C program , where there should be 5 threads , first thread will read first row and all columns of A , and multiply them with row B , second thread will read second row and all coulmns values of A , and multiply them with C , and so on , 5th thread will print the resultant array.
// Sample
/*

A: 
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16

B: 7 8 9 11
C: 11 13 19 18
D: 9 12 14 16
E: 16 17 18 19

D

7 16 27 44

55 78 133 144

and so on

*/

#include <stdio.h>
#include <pthread.h>

#define N 4
#define M 4

int A[N][M];
int B[N];
int C[N];
int D[N];
int E[N];

void *threadTask(void *args) {
    
}

int main(int argc, char *argv[]) {



    return 0;
}