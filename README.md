# Custom-Malloc
This project implements a simulation of the malloc and free functions included in `<stdlib.h>`. Please refer to the PDF for more details.
## Test Plan

### Properties Library Must Have To Be Correct

In order for the library to be correct, we concluded that the library must have the ability to initialize memory, malloc, free, and coalesce blocks. The library must also have the ability to call out errors which include: double free, segmentation fault, trying to free the wrong pointer, requesting more than the available memsize, and running out of memory.

### How to check that Code Has These Properties

In order to check that our code has these properties, we intend to use various forms of testing. In the memgrind.c file, we intend to place the three stress tests from the write up and add two more stress tests of our own. In addition, in a separate tests directory file, we intend to add multiple tests that use malloc/free normally and some tests that intentionally cause errors. Later on, we intend to use the library we implemented on these test cases to check whether or not our code has these properties. Also as we test, we are using a function that prints out our memory array so we can manually check whether or not our library is correct.

### Specific Methods to Check Each Property

is this not the same as above and below??? bc i feel like above goes into like what we have and test programs will go into specific, lmk if you want me to add something here cause 

## Test Programs

### Memgrind.c Test Cases
In this program, we should run each task 50 times, hence the for loops before each test case.
1. malloc()  and immediately  free()  a 1-byte chunk, 120 times.
```
for(int  i  =  0;  i<50;  i++){

	for  (int  j  =  0;  j<120;  j++){

	char  *c  =  malloc(1);

	free(c);

}
```
2. 
### Test Directory Test Cases

## Design Properties 

### We are Able to Prove

bruh

### Design Notes

bruh
