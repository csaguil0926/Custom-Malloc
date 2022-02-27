#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include "mymalloc.h"

/*
 * These represent the ASCII values of 'T' and 'F' respectively. These are used to represent true and false respectively.
 */

#define TRUE 84
#define FALSE 70

static char memory[MEMSIZE]; // Assuming that everything in the char array is 0.

/*
 * For metaData, available is set to type char to represent boolean values of true or false. These will ALWAYS be either
 * set to upper case ASCII 'T' (84 decimal value) or upper case ASCII 'F' (70 decimal value). These values will represent
 * true and false respectively. The reason char is used because the memory array by default has all the values set to 0.
 * If we were to use `stdbool`, if we set "available" to false, it would be very half to know if the zero read in the array
 * is "false" or if the zero means that this part of the array has not been read yet. It is just to prevent confusion.
 * `stdbool` values are one byte by default on x86 and x86_64 architecture. So are chars. It is safe to assume "available" will
 * not be set to anything else.
 *
 * Furthermore, the use of "char" here is also risky and may be confusing because chars are typically associated with "characters",
 * however, in this case, to use the simplest and easiest to understand solution, the `available` variable in metaData is to be
 * viewed only as a boolean value represented by the 'T' and 'F' ASCII characters. This is only done to prevent confusion with the
 * default char value in the memory array.
 */
/*
 * Type def??
 */
struct metaData {
    char available; // In this case, available will either be set as T or F for true or false.
    unsigned int dataSize; // We did not use size_t here to save space in the long run. Rather than having a 16 byte alignment, doing unsigned int makes it 8 byte aligned which will save space. I think it is safe to assume that the user will not be allocating more than 4.2 GB of memory all at once.
};

void printMemory(int bytes) {
    for (int x = 0; x < bytes; x++) {
        printf("Address %d: %p\n", x, memory + x);
        printf("Value: %x\n", memory[x]);
    }
}

void *initializeMemory(size_t size) {
    struct metaData *md = (struct metaData *) memory; // md's actual contents gets written to the same place where memory is stored. It starts writing at the address of memory[0]

    md->available = FALSE;
    md->dataSize = size;

    md = (struct metaData *) &memory[sizeof(struct metaData) + md->dataSize]; // Have md point to basically after the metadata and allocated memory given to the user.

    md->available = TRUE;
    md->dataSize = MEMSIZE - (sizeof(struct metaData) * 2) - size; // How much memory there is left to allocate

    return memory + sizeof(struct metaData); // Return pointer to first allocated memory.
}

void *mymalloc(size_t size, char *file, int line) {
    if (size > MEMSIZE) {
        perror("You are requesting too much memory!"); // Should be replaced with a function call in errors.c
        return NULL;
    }

    if (memory[0] == 0) { // Initialize the memory.
        return initializeMemory(size);
    }

    int x = 0;

    while (x < MEMSIZE) {
        struct metaData *md = (struct metaData *) &memory[x];

        if (md->available == FALSE) {
            x += sizeof(struct metaData) + md->dataSize;
            continue;
        } else if (md->available == TRUE) {
            if (md->dataSize >= size) { // What if there is no space for new metaData after allocating space?
                md->available = FALSE;
                md->dataSize = size;

                md = (struct metaData *) &memory[x + sizeof(struct metaData) + md->dataSize];

                md->available = TRUE;
                md->dataSize = MEMSIZE - (x + (2 * sizeof(struct metaData)) + size);

                return &memory[x] + sizeof(struct metaData);
            } else {
                return NULL;
            }
        }
    }
    return NULL;
}
void myfree(void *ptr, char *file, int line) {
    // As of right now, this code assumes that ptr will point to the right thing. There is no error checking!

    struct metaData *md = ptr - 8;
    md->available = TRUE;

    // It's at this point, we need to figure out how to coalesce blocks... =/
}
