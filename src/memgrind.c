#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(int argc, char *argv[]) {
    int *p1 = malloc(4);
    int *p2 = malloc(25);

    *p1 = 25;
    *p2 = 32;

    printMemory(4096);

	 // I think this is going to be used as a driver file? I am not sure. 
    return 0;
}
