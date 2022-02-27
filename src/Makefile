TARGET = memgrind
CC = gcc-9
CFLAGS = -g -std=c99 -Wall -Wvla -Wextra -Wundef -Wshadow -Wpointer-arith -O2 -D_FORTIFY_SOURCE=2 #-fsanitize=undefined # Will probably add more options as we go, but this is okay for now.

# README: Since this is just a skeleton, I've commented out the other CFLAGS... As we test, we should probably make sure our code can run with all these flags enabled.

all: $(TARGET)

run: $(TARGET)
	./$<

hass_test: hass_test.c mymalloc.o errors.o
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET): mymalloc.o $(TARGET).o errors.o
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).o: $(TARGET).c
	$(CC) -c $(CFLAGS) $^

mymalloc.o: mymalloc.c
	$(CC) -c $(CFLAGS) $^

errors.o: errors.c
	$(CC) -c $(CFLAGS) $^

mymalloc.c: mymalloc.h
$(TARGET).c: mymalloc.h

clean:
	rm -rfv $(TARGET) *.o *.a *.dylib *.dSYM

clean_HT:
	rm -rfv hass_test *.o *.a *.dylib *.dSYM
