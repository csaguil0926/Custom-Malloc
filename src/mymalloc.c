#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
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

struct metaData {
    char available; // In this case, available will either be set as T or F for true or false.
    unsigned int dataSize; // We did not use size_t here to save space in the long run. Rather than having a 16 byte alignment, doing unsigned int makes it 8 byte aligned which will save space. I think it is safe to assume that the user will not be allocating more than 4.2 GB of memory all at once.
};

void printMemory(int bytes) {
    printf("%d ", MEMSIZE);
    for (int x = 0; x < bytes; x++) {
        printf("Address %d: %p\n", x, memory + x);
        printf("Value: %d\n", memory[x]);
    }
}

void *initializeMemory(size_t size) {
    struct metaData *md = (struct metaData *) memory; // md's actual contents gets written to the same place where memory is stored. It starts writing at the address of memory[0]

    md->available = FALSE;
    md->dataSize = size;

    md = (struct metaData *) &memory[sizeof(struct metaData) + md->dataSize]; // Have md point to basically after the metadata and allocated memory given to the user.

    md->available = TRUE;
    md->dataSize = MEMSIZE - (sizeof(struct metaData) * 3) - size; // How much memory there is left to allocate

    return memory + sizeof(struct metaData); // Return pointer to first allocated memory.
}

void coalesceBlocks() {
    int x = 0;
    while (x < MEMSIZE) {
        struct metaData *firstMetaData = (struct metaData *) &memory[x];

        int nextMDLocation = x + sizeof(struct metaData) + firstMetaData->dataSize;

        if (nextMDLocation + 8 > MEMSIZE) {
            return;
        }

        struct metaData *secondMetaData = (struct metaData *) &memory[nextMDLocation];

        if (firstMetaData->available == TRUE && secondMetaData->available == TRUE) {
            firstMetaData->dataSize += (secondMetaData->dataSize + sizeof(struct metaData));
        }

        x += sizeof(struct metaData) + firstMetaData->dataSize;
    }
}

void *mymalloc(size_t size, char *file, int line) {
    if (size + (2 * sizeof(struct metaData)) > MEMSIZE) {
        tooMuchMem(MEMSIZE, file, line);
        return NULL;
    }

    if (memory[0] == 0) { // Initialize the memory.
        return initializeMemory(size);
    }

    if (size <= 0) {
        mallocZeroError(file, line);
        return NULL;
    }

    int x = 0;

    while (x < MEMSIZE) {
        struct metaData *md = (struct metaData *) &memory[x];

        if (md->available == TRUE && md->dataSize >= size) {

            md->available = FALSE;
            md->dataSize = size;

            unsigned int nextMDIndex = x + sizeof(struct metaData) + md->dataSize;
            md = (struct metaData *) &memory[nextMDIndex];

            if (md->available != TRUE && md->available != FALSE) { // Then, there is no metaData to the right...
                if (nextMDIndex + 8 <= MEMSIZE) {
                    md->available = TRUE;
                    md->dataSize = MEMSIZE - (x + (3 * sizeof(struct metaData)) + size);
                } else {
                    noMoreMem(file, line);
                    return NULL;
                }
            }

            return &memory[x] + sizeof(struct metaData);
        } else {
            x += sizeof(struct metaData) + md->dataSize;
            continue;
        }
    }

    noMoreMem(file, line);
    return NULL;
}


void myfree(void *ptr, char *file, int line) {
    // As of right now, this code assumes that ptr will point to the right thing. There is no error checking!

    if (ptr == NULL) {
        printf("%s:%d", file, line);
        exit(1);
    }

    struct metaData *md = ((struct metaData *) ptr) - 1;

    if (md->available == TRUE) {
        doubleFree(file, line);
        return;
    } else if ((md->available != FALSE && md->available != TRUE) || md->dataSize <= 0) { // The user could malloc the exact contents of the metaData, basically emulating it and then try to free it, but even actual malloc and free has this vulnerability.
        wrongPointer(file, line);
        return;
    } else {
        md->available = TRUE; // Data Size?
        coalesceBlocks();
    }
}

void freeAll() {
    struct metaData *md;
    for (int x = 0; x < MEMSIZE; x += sizeof(struct metaData *) + md->dataSize) {
        md = (struct metaData *) &memory[x];
        if (md->available == FALSE) {
            free(&memory[x + sizeof(struct metaData)]);
        }
    }

    coalesceBlocks();

    return;
}
