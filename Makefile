default: cracker

CC = gcc
CFLAGS =-Wall -Werror -pthread -std=c99 -g

CFiles =

src/cracker: src/cracker.o src/reverse.o src/sha256.o
	$(CC) $(CFLAGS) -o src/cracker src/cracker.o src/reverse.o src/sha256.o

src/cracker.o: src/cracker.c src/reverse.h src/sha256.h
	$(CC) $(CFLAGS) -o src/cracker.o -c src/cracker.c

src/reverse.o: src/reverse.c src/reverse.h src/sha256.h
	$(CC) $(CFLAGS) -o src/reverse.o -c src/reverse.c

src/sha256.o: src/sha256.c src/sha256.h
	$(CC) $(CFLAGS) -o src/sha256.o -c src/sha256.c

all: cracker

tests:

// code bash pour tester l'initialisation.

gcc -o progtest $CFLAGS$ CUnit.c -lcunit

// code bash pour tester le code en entier.

.PHONY: clean tests

clean:
	rm -rf src/cracker src/*.o