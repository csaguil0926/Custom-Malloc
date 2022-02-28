#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "mymalloc.h"

int main(int argc, char *argv[]) {
    time_t t;
    srand((unsigned) time(&t));
    
    struct timeval start, end;

    gettimeofday(&start, NULL);

    //test case 1 where we malloc 1 byte then immediately free it 120 times
    //we do this task 50 times

    for(int i = 0; i<50; i++){ 
        for (int j = 0; j<120; j++){
            char *c = malloc(1);
            free(c);
        }
    }

    gettimeofday(&end, NULL);

    double time_taken = end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6; // in seconds
    printf("time program took %f seconds to execute\n", time_taken);

    gettimeofday(&start, NULL);

    //test case 2 where we use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() to deallocate the chunks.
    //make hasnain check this lmao
    
    for(int i = 0; i<50; i++){
        char *test1 = malloc(120);
        char *test2[120];

        for (int j = 0; j<120; j++){
            test2[j] = &test1[j];
        }

        free(test1);
    }

    gettimeofday(&end, NULL);

    time_taken = end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6; // in seconds
    printf("time program took %f seconds to execute\n", time_taken);

    gettimeofday(&start, NULL);


*//*
    test case 3
    Randomly choose between
        •Allocating a 1-byte chunk and storing the pointer in an array
        •Deallocating one of the chunks in the array (if any)
    Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.
    *//*


    srand(time(0));

    int malloc_called = 0;
    void *pointerArr[120];


    while (malloc_called < 120) {
        int randomNum = rand() % 2;

        if (randomNum == 0) {
            char *chunk = malloc(1);
            pointerArr[malloc_called] = chunk;
            malloc_called++;
            continue;
        } else {
            for (int x = 0; x < malloc_called && pointerArr[x] != NULL; x++) {
                free(pointerArr[x]);
                pointerArr[x] = NULL;
            }
        }
    }

    for (int x = 0; x < malloc_called; x++) {
        if (pointerArr[x] != NULL) {
            free(pointerArr[x]);
        }
    }



    gettimeofday(&end, NULL);

    time_taken = end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6; // in seconds
    printf("time program took %f seconds to execute\n", time_taken);

    gettimeofday(&start, NULL);

    //test case 4

    for (int i = 0; i < 50; i++){
        int n = (rand() % 120) + 1;

        int *array = (int *) malloc (n * sizeof(int)); //make dynamic array

        for (int j = 0; j < n; j++){ //fill array with items
            array[j] = n;
        }

        free(array);
    }

    gettimeofday(&end, NULL);

    time_taken = end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6; // in seconds
    printf("time program took %f seconds to execute\n", time_taken);
    

    return 0;
}
