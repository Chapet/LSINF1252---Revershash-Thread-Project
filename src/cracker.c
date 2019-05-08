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
int nbThread = 1; //the number of threads used to parallelize the reversal of the hashs
char consonant_or_vowel = 'v'; //v for vowel, c for consonant
char *fileOutput = NULL; //the possible output file, also used to know if the output is specified
int nbInputFile;
FILE *fdInput = NULL; //file descriptor used for reading the input files
int curInputFile = 0;

typedef struct Candidate {
    struct Candidate *next;
    char *password;
}Candidate;

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
int listSize(Candidate *head) { //à remplacer avec une fonction qui calcule le nb de char
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
void update_candidate(Candidate *head, char *pwd) {
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

/* pre: head != NULL, head->password =! NULL
 * post : returns a char* containing all the password, with a newline after each one
 */
char *writeOutput(Candidate *head) { //no need to free the element of the linked list : when the program stops, all the associated memory is freed
    if (head == NULL || head->password == NULL) {
        fprintf(stderr, "error while extracting passwords out of linked list (pointer or struct value NULL)\n");
        return NULL;
    }
    char *strOut = malloc(listSize(head) * 18 * sizeof(char)); //the password has a maximum length of 16 letters + the line feed (2 bytes)
    Candidate *next = head;

    while (next != NULL) {
        strcat(strOut, next->password);
        strcat(strOut, "\n");

        next = next->next;
    }
    return strOut;
}

/* pre: bufread, an uint8 array, fileInput, an array of string containing the names of the input names
 * post: browse trough all the input file(s) and saves all of the data read
 */
void *produce(uint8_t *bufread, char *fileInput[]) { //not thread-safe
    //if not no file descriptor is set, either the first or the next input file is opened and read
    while (fdInput == NULL) { //the while is used instead of an if to handle the empty files issue
        curInputFile++;

        if (curInputFile > nbInputFile) { //all the input files have been read
            int c = fclose(fdInput);
            if (c != 0) {
                fprintf(stderr, "error while closing input file : %d\n", errno);
            }
            return NULL;
        } else { //the new input file is opened
            fdInput = fopen(fileInput[curInputFile-1], "r");
            printf("file opened\n");
        }
    }

    if (fread(bufread, 32, 1, fdInput) != 1) {
        fprintf(stderr, "error while reading input file\n");
    }
    return NULL;
}


int main(int argc, char *argv[]) {
    int notInputFiles = 1; //used to know the number of input files

    // we first initialise the global variables with the getopt() function
    int opt = 0;
    while ((opt = getopt(argc, argv, "t:co:")) != -1) {
        switch (opt) {
            case 't' :
                notInputFiles += 2;
                nbThread = atoi(optarg); //if we do a cast, we get values from the ASCII table, which is not what we want
                break;
            case 'c' :
                notInputFiles++;
                consonant_or_vowel = 'c';
                break;
            case 'o' :
                notInputFiles += 2;
                fileOutput = optarg;
                break;
            case '?' :
                fprintf(stderr, "Unknown argument : %d\n", optopt);
                break;
        }
    }

    //stocking the input files in a string array
    nbInputFile = argc - notInputFiles;
    char *fileInput[nbInputFile];
    for (int i = 0; i < nbInputFile; i++) {
        fileInput[i] = argv[i + notInputFiles];
    }

    //thread de lecture

    //producteur-consommateur #1

    //producteur-consommateur #2

    //interaction LL
    Candidate *head = &(Candidate){NULL, ""};

    //tests pdt le dvpment
    printf("Test starto !\n");
    printf("%s\n", fileInput[0]);

    char *result = malloc(16);
    uint8_t buf[32];
    produce(buf, fileInput);
    bool success = reversehash(buf, result, 16);
    printf("%d : %s\n", success, result);

    printf("Test complete !\n");



    //output : the string containing all the password (one on each line) is obtained, then it is printed on the correct output stream
    char *stringOut = writeOutput(head);
    if (fileOutput == NULL) //standard output
        printf("%s", stringOut);
    else { //specified output file
        FILE *fp;
        fp = fopen(fileOutput, "w");
        if (fp == NULL) {
            fprintf(stderr, "error while opening output file: %d\n", errno);
            free(stringOut);
            return EXIT_FAILURE;
        }
        fprintf(fp, "%s", stringOut);
        int c = fclose(fp);
        if (c != 0) {
            fprintf(stderr, "error while closing output file : %d\n", errno);
            free(stringOut);
            return EXIT_FAILURE;
        }
    }
    free(stringOut); // not really necessary since the process is about to be stopped anyway (and thus the memory cleaned)
    return EXIT_SUCCESS;
}