CC = gcc
CFLAGS =-Wall -Werror

all: cracker tests #ca lance tjr cracker si on fait juste make ?

cracker: cracker.o reverse.o sha256.o
    $(CC) -o '.\src\cracker' cracker.o reverse.o sha256.o

cracker.o: cracker.c reverse.h sha256.h
    $(CC) -o '.\src\cracker.o' -c cracker.c $(CFLAGS)

reverse.o: reverse.c reverse.h sha256.h
    $(CC) -o '.\src\reverse.o' -c reverse.c $(CFLAGS)

sha256.o: sha256.c sha256.h
    $(CC) -o '.\src\sha256.o' -c sha256.c $(CFLAGS)

tests:

.PHONY: clean rmcracker

rmcracker:
    rm -rf cracker

clean: rmcracker
    rm -rf *.o