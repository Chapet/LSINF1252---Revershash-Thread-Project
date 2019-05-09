#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>


#include "sha256.h"
#include "reverse.h"


#ifndef LSINF1252_REVERSHASH_THREAD_PROJECT_CRACKER_H
#define LSINF1252_REVERSHASH_THREAD_PROJECT_CRACKER_H

#endif //LSINF1252_REVERSHASH_THREAD_PROJECT_CRACKER_H

// Variable globale utilisée dans les fonctions

//def of global variables and structures
typedef struct Candidate {
    struct Candidate *next;
    char *password;
}Candidate;

typedef struct ProdConsArg1 {
    pthread_mutex_t mutex;
    sem_t empty;
    sem_t full;
    char *fileInput[];
} PCArg1;

int nbThread; //the number of threads used to parallelize the reversal of the hashs
char consonant_or_vowel ; //v for vowel, c for consonant
char *fileOutput ; //the possible output file, also used to know if the output is specified
int nbInputFile;
FILE *fdInput ; //file descriptor used for reading the input files
int curInputFile;
uint8_t **buffer1; //the first buffer
char **buffer2; //the second buffer
int curSize1; //the current number of element in the first buffer
int curSize2; //the current number of element in the second buffer
Candidate *head ; //head of the linked list
bool readFlag = false; //a boolean flag indicating if the reading of the input files is over
pthread_mutex_t mut;
int countRevThreadOver ; //counts the number of threads that finished to reverse a hash after the reading is over and the first buffer is empty
sem_t revOver;
sem_t crackerOver;





// Fonction nécessaire ailleurs.
int countOcc(char *str);

int listSize();

void update_candidate();

void *produce(uint8_t *bufread, char *fileInput[]);

void insert_item();