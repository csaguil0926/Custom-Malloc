#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
//#include "mymalloc.h"

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

    /*
    test case 3
    Randomly choose between
        •Allocating a 1-byte chunk and storing the pointer in an array
        •Deallocating one of the chunks in the array (if any)
    Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.
    */

        char *test4[120];
        int mallocCalled = 0; //counter on how many times malloc is called

        while(mallocCalled<120){//until we call malloc 120 times
            
            int n = rand() % 2; //generates random number between 0 and 1

            if (n == 0){
                char *test = malloc(1); //malloc 1 byte chunk
                test4[mallocCalled] = test; //store chunk in array
                mallocCalled++; //increase count of how many times malloc is called
            } else if (n == 1){
                if (mallocCalled > 0 && test4[mallocCalled-1]!=NULL){ //if malloc has happen at least once and test[mallocCalled-1] has not already been freed
                    free(test4[mallocCalled - 1]); //free
                    test4[mallocCalled-1]=NULL; //make pointer null
                }
            }
        }

        //free the remaining chunks in the array
        for (int x = 0; x < 120; x++) {
            if(test4[x]!=NULL){ //if remaining chunks have not been freed and set to null
                free(test4[x]); //free chunk
                test4[x]=NULL;//set pointer to null
            }
        }

    gettimeofday(&end, NULL);

    time_taken = end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6; // in seconds
    printf("time program took %f seconds to execute\n", time_taken);

    gettimeofday(&start, NULL);

    //test case 4

    for (int i = 0; i<50; i++){
        int n = rand() % 120;

        int* array = (int*)malloc(n*sizeof(int)); //make dynamic array
    
        for (int j = 0; j<n; j++){ //fill array with items
            array[j]=j+1;
        }

        free(array);
    }

    gettimeofday(&end, NULL);

    time_taken = end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6; // in seconds
    printf("time program took %f seconds to execute\n", time_taken);

    //test case 5

    return 0;
    
}
