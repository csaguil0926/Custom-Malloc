TARGET = memgrind
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wvla -Werror -Wextra -Wundef -Wshadow -Wpointer-arith # -fsanitize=undefined # Will probably add more options as we go, but this is okay for now.

# README: Since this is just a skeleton, I've commented out the other CFLAGS... As we test, we should probably make sure our code can run with all these flags enabled.

all: $(TARGET)

run: $(TARGET)
	./$<

memgrind: mymalloc.o $(TARGET).o
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).o: $(TARGET).c
	$(CC) -c $(CFLAGS) $^

mymalloc.o: mymalloc.c
	$(CC) -c $(CFLAGS) $^

mymalloc.c: mymalloc.h
$(TARGET).c: mymalloc.h

clean:
	rm -rfv $(TARGET) *.o *.a *.dylib *.dSYM
