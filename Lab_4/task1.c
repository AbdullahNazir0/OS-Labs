#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {

    // The tree to get from fork
    //             Parent
    //      Child                   child         child
    // child        child       child
    // child child

    printf("I am before fork\n");
    
}