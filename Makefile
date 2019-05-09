default: cracker

CC = gcc
CFLAGS =-Wall -Werror -pthread -std=c99 -g

CFiles =

src/cracker: src/cracker.o src/reverse.o src/sha256.o
	$(CC) $(CFLAGS) -o src/cracker src/cracker.o src/reverse.o src/sha256.o

src/cracker.o: src/cracker.c src/reverse.h src/sha256.h src/cracker.h
	$(CC) $(CFLAGS) -o src/cracker.o -c src/cracker.c

src/reverse.o: src/reverse.c src/reverse.h src/sha256.h
	$(CC) $(CFLAGS) -o src/reverse.o -c src/reverse.c

src/sha256.o: src/sha256.c src/sha256.h
	$(CC) $(CFLAGS) -o src/sha256.o -c src/sha256.c

all:
    cracker

tests:

    # code bash pour tester l'initialisation.
    gcc -o prog $(CFLAGS)$ test_initialisation.c

    echo Maintenant testons sans argument, puis avec.

    ./prog

    ./prog -c

    ./prog -t 4

    ./prog -o filename

    ./prog -c -t 8 -o filename

    ./prog -r

    /////////

    echo Maintenant les tests CUnit.

    gcc -o progtest $(CFLAGS)$ cracker.o CUnit.c -lcunit

    ./progtest

    /////////

    # code bash pour tester le code en entier (peut-être mettre des echos pour dire quoi test quoi).

    echo Maintenant passons au test du code en entier.

    ./cracker  bin160o.bin

    ./cracker -c bin16o.bin

    ./cracker bin32ko.bin

    ./cracker -t 50 bin32ko.bin

    ./cracker -c -t 50 -o fichiersortie.txt bin32ko.bin
    cat fichiersortie.txt

    ./cracker -t 50 -o fichiersortie2.txt bin160o.bin bin32ko.bin
    cat fichiersortie2.txt

    ///////////

.PHONY: clean tests

clean:
	rm -rf src/cracker src/*.o



