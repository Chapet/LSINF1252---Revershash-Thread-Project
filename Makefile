CC = gcc
CFLAGS =-Wall -Werror

src/cracker: src/cracker.o src/reverse.o src/sha256.o
	$(CC) -o src/cracker src/cracker.o src/reverse.o src/sha256.o $(CFLAGS)

src/cracker.o: src/cracker.c src/reverse.h src/sha256.h
	$(CC) -o src/cracker.o -c src/cracker.c $(CFLAGS)

src/reverse.o: src/reverse.c src/reverse.h src/sha256.h
	$(CC) -o src/reverse.o -c src/reverse.c $(CFLAGS)

src/sha256.o: src/sha256.c src/sha256.h
	$(CC) -o src/sha256.o -c src/sha256.c $(CFLAGS)

all: cracker

tests:

.PHONY: clean tests

clean:
	rm -rf src/cracker src/*.o