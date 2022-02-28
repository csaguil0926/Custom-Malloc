# Custom-Malloc
This project implements a simulation of the malloc and free functions included in `<stdlib.h>`. Please refer to the PDF for more details.
## Test Plan

### Properties Library Must Have To Be Correct

In order for the library to be correct, we concluded that the library must have the ability to malloc, free, and coalesce blocks. The library must also have the ability to call out errors which include: double free, segmentation fault, trying to free the wrong pointer, requesting more than the available memsize, running out of memory, and trying to malloc zero.

### How to check that Code Has These Properties

In order to check that our code has these properties, we intend to use various forms of testing. In the memgrind.c file, we intend to place the three stress tests from the write up and add two more stress tests of our own. In addition, in a separate tests directory file, we intend to add multiple tests that use malloc/free normally and some tests that intentionally cause errors. Later on, we intend to use the library we implemented on these test cases to check whether or not our code has these properties. Also as we test, we are using a function that prints out our memory array so we can manually check whether or not our library is correct.

### Specific Methods to Check Each Property

In order to test whether or not an individual property is working we have specific methods to check each one.
- Malloc and Free: There are specific test cases in memgrind.c and specific test cases in the test directory that check whether or not malloc and free are working properly. In memgrind.c, one test mallocs data and frees it immediately and the other mallocs multiple chunks at once then frees it all at once. In the test directory and memgrind, there are test cases that malloc and free a dynamic array and other test cases that malloc and free a dynamic 2d array.
- Coalesce: Technically coalesce should be working for the test cases mentioned previously, however in order to check it properly we made a specific test case in memgrind that randomly allocates memory and randomly frees it. This will allow us to check whether or not our free blocks are combining and allowing malloc to happen even after we free multiple times.
- Error-Checking: In the test directory, there are multiple tests that intentionally use malloc and free improperly in order to check whether or not our errors in the library are called when required.

## Test Programs

### Memgrind.c Test Cases
In this program, we run each stress tests 50 times.
1. malloc()  and immediately  free()  a 1-byte chunk, 120 times.

2. Use  malloc()  to get 120 1-byte chunks, storing the pointers in an array, then use  free()  to  deallocate the chunks.

3. Randomly choose between:
•Allocating a 1-byte chunk and storing the pointer in an array  
•Deallocating one of the chunks in the array (if any)  
Repeat until you have called  malloc()  120 times, then free all remaining allocated chunks.

4. Randomly generates a number, n, between 1 and 120. Use malloc() to allocate enough memory for an integer array of n size. Fill the array with elements, which will be 1 to n. Finally free the dynamic array.

5. Similar to test case 4, however, instead of freeing correctly we are freeing twice. We are expecting this to give the doubleFree error in our library. //CHANGE THIS IF THIS IS NOT THE TEST CASE YOU ENDED UP IMPLEMENTING

### Test Directory Test Cases
1. test1 will get the number of elements from input and print out the elements of the array, which will be 1 to number of elements in array.
	- Expected arguments: 
		>Integer from the command line that determines how large the array will be
	- Expected output:
		>Enter number of items:#
		>Number of elements: #
		>Array: {1,...,#}
		>e.g. if number of items entered is 4 the output would be
		>Enter number of items:4
		>Number of elements: 4
		>Array: {1, 2, 3, 4}
	
2. test2 will get size of identity matrix from user, make identity matrix, and print it out
	- Expected arguments:
		> Integer from the command line that determines how large the identity matrix will be
	- Expected output:
		> Enter size of matrix: #
		1 0 ... 0 <br />
		. . <br />
		. . <br />
		. . <br />
		0 0 ... 1 <br />
		e.g. if user inputs 5 as the size of identity matrix output will look like
		Enter size of matrix: 5 <br />
		1 0 0 0 0 <br />
		0 1 0 0 0 <br />
		0 0 1 0 0 <br />
		0 0 0 1 0 <br />
		0 0 0 0 1 <br />
	
3. Similar to test case 1, however, instead of freeing correctly we are freeing twice. We are expecting this to give the doubleFree error in our library.
	- Expected arguments: 
		>Integer from the command line that determines how large the array will be
	- Expected output:
		> doubleFree error
	
4. Similar to test case 1, however, instead of freeing correctly we are freeing before we print the array. We are expecting this to give the segFault error in our library because we are trying to access something we already freed.
	- Expected arguments: 
		>Integer from the command line that determines how large the array will be
	- Expected output:
		> segFault error
	
5. Similar to test case 1, however, instead of freeing correctly we are freeing the wrong pointer. We are expecting this to give the wrongPointer error in our library.
	- Expected arguments: 
		>Integer from the command line that determines how large the array will be
	- Expected output:
		> wrongPointer error
## Design Properties 

### We are Able to Prove

bruh

### Design Notes

bruh
