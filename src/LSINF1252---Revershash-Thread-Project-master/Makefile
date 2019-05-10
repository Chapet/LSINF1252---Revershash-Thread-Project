CC = gcc
CFLAGS =-Wall -Werror -pthread -std=c99 -g

src/cracker: src/cracker.o src/reverse.o src/sha256.o
	$(CC) $(CFLAGS) -o src/cracker src/cracker.o src/reverse.o src/sha256.o

src/cracker.o: src/cracker.c src/reverse.h src/sha256.h src/cracker.h
	$(CC) $(CFLAGS) -o src/cracker.o -c src/cracker.c

src/reverse.o: src/reverse.c src/reverse.h src/sha256.h
	$(CC) $(CFLAGS) -o src/reverse.o -c src/reverse.c

src/sha256.o: src/sha256.c src/sha256.h
	$(CC) $(CFLAGS) -o src/sha256.o -c src/sha256.c

all:
	make
	make tests

tests:
	# code bash pour tester l'initialisation.

	$(CC) $(CFLAGS) -o tests/prog tests/test_initialisation.c

	echo Maintenant testons sans argument, puis avec.

	./tests/prog

	./tests/prog -c

	./tests/prog -t 4

	./tests/prog -o filename

	./tests/prog -c -t 8 -o filename

	./tests/prog -r

	echo Maintenant les tests CUnit.

	$(CC) $(CFLAGS) -o tests/progtest src/cracker.o tests/CUnit.c -lcunit

	./tests/progtest

	# code bash pour tester le code en entier (peut-être mettre des echos pour dire quoi test quoi).

	echo Maintenant passons au test du code en entier.

	./src/cracker  bin160o.bin

	./src/cracker -c bin16o.bin

	./src/cracker bin32ko.bin

	./src/cracker -t 50 bin32ko.bin

	./src/cracker -c -t 50 -o fichiersortie.txt bin32ko.bin

	cat fichiersortie.txt

	./src/cracker -t 50 -o fichiersortie2.txt bin160o.bin bin32ko.bin

	cat fichiersortie2.txt

.PHONY: clean tests

clean:
	rm -rf src/cracker src/*.o



