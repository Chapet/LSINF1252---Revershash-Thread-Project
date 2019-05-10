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

int nbThread = 1; //the number of threads used to parallelize the reversal of the hashs
char consonant_or_vowel = 'v'; //v for vowel, c for consonant
char *fileOutput = NULL; //the possible output file, also used to know if the output is specified
int nbInputFile;
FILE *fdInput = NULL; //file descriptor used for reading the input files
int curInputFile = 0;
uint8_t **buffer1; //the first buffer
char **buffer2; //the second buffer
int curSize1 = 0; //the current number of element in the first buffer
int curSize2 = 0; //the current number of element in the second buffer
Candidate *head = &(Candidate){NULL, ""}; //head of the linked list
bool readFlag = false; //a boolean flag indicating if the reading of the input files is over
pthread_mutex_t mut;
int countRevThreadOver = 0; //counts the number of threads that finished to reverse a hash after the reading is over and the first buffer is empty
sem_t revOver;
sem_t crackerOver;

/* pre: str!=NULL, str is a string containing only letters ranging a-z
 * post: returns the number of occurrences of vowel or consonant, depending on the global variable consonant_or_vowel;
 */
int countOcc(char *str) {
    char *cur = str; //a pointer to browse the string
    int vowel = 0; //to count the number of vowel's occurrences
    for (int i = 0; i < strlen(str); i++) { //browsing the string
        if (*(cur + i) == 'a' || *(cur + i) == 'e' || *(cur + i) == 'i' || *(cur + i) == 'o' || *(cur + i) == 'u' ||
            *(cur + i) == 'y') { //the current char is a vowel
            vowel++;
        }
    }

    if (consonant_or_vowel == 'v')
        return vowel;
    else
        return strlen(str) - vowel; //every char that is not a vowel is a consonant
}

/* pre: head != NULL
 * post: return the number of nodes of the linking list (including the head)
 */
int listSize() { //à remplacer avec une fonction qui calcule le nb de char
    int size = 0;
    Candidate *next = head;

    while (next != NULL) {
        size++;
        next = next->next;
    }
    return size;
}

/*pre: head != NULL, head->password != NULL, pwd != NULL
 *post: Checks if a password is the be added to the list of candidates by comparing his length to to the current candidates length.
 *
 *If the password's length is greater, the current list is replaced with a list containing only this password as candidate.
 *Else if the password's length is identical, the password is added to the list of candidates
 *Else (the password's length is shorter), the password is not added and thus the list stays unchanged.*/
void update_candidate(char *pwd) {
    if (head == NULL || head->password == NULL || pwd == NULL) {
        fprintf(stderr, "error while updating linked list (pointer or struct element NULL)\n");
    }
    int curOcc = countOcc(head->password);
    int pwdOcc = countOcc(pwd);

    if (pwdOcc > curOcc) { //then a new head is created
        head->next = NULL;
        head->password = pwd;
    } else if (pwdOcc == curOcc) { //then a new Candidate is added to the linked list
        Candidate *newCand = malloc(sizeof(Candidate));
        *newCand = (Candidate) {head->next, pwd};
        head->next = newCand;
    }
}
