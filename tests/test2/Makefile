TARGET = test2
CC     = gcc
CFLAGS = -g -std=c99 -Wall -Wvla -Werror -Wundef -Wpointer-arith -fsanitize=address,undefined

$(TARGET): $(TARGET).o mymalloc.o errors.o
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET).o: $(TARGET).c ../../src/mymalloc.h
	$(CC) -c $(CFLAGS) $<

mymalloc.o: ../../src/mymalloc.c ../../src/mymalloc.h
	$(CC) -c $(CFLAGS) $<

errors.o: ../../src/errors.c ../../src/errors.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm -rf $(TARGET) *.o *.a *.dylib *.dSYM
