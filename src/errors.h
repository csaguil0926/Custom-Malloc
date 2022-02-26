#ifndef _ERRORS_H
#define _ERRORS_H

//prototypes of errors from errors.c
void doubleFree(char* file, int line);
void segFault(char* file, int line);
void memoryLeak(char* file, int line);
void wrongPointer(char* file, int line);
void tooMuchMem(int MEMSIZE, char* file, int line);
void noMoreMem(char* file, int line);

#endif