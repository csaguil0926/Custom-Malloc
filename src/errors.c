#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

void doubleFree(){//trying to free something you already freed
    printf("You cannot free something twice");
    return NULL;
}

void segFault(){ //freed memory but tried to access it again, trying to access something you can't access, trying to free something not initialized
    printf("You cannot access something that is not there or can't be accessed");
    return NULL;
}

void heapBufferOverflow(){ //malloc too much and don't free any of it
    printf("You cannot malloc more than the available memory space");
    return NULL;
}

void memoryLeak(){ //forget to free allocated memory
    printf("You are getting an error because you did not free all the allocated memory");
    return NULL;
}