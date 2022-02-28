TARGET = memgrind
CC = gcc-9
CFLAGS = -g -std=c99 -Wall -Wvla -Wextra -Wundef -Wshadow -Wpointer-arith -O2 -D_FORTIFY_SOURCE=2 # -fsanitize=address # Will probably add more options as we go, but this is okay for now.
OBJ = mymalloc.o $(TARGET).o errors.o



all: $(TARGET)

run: $(TARGET)
	./$<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET).o: $(TARGET).c mymalloc.h
	$(CC) -c $(CFLAGS) $<

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) -c $(CFLAGS) $<

errors.o: errors.c errors.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm -rfv $(TARGET) *.o *.a *.dylib *.dSYM

clean_ht:
	rm -rfv hass_test *.o *.a *.dylib *.dSYM