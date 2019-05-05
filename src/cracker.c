#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "sha256.h"
#include "reverse.h"

//def of global variables and structures

int nbThread = 1; //the number of threads used to parallelize the reversal of the hashs
char consonant_or_vowel = 'v'; //v for vowel, c for consonant
int stdOutput = 1; //1 for the std output, else the output is a specified file
char* fileOutput = NULL; //the possible output file
int listSize = 1; //size of the linked list

int curOcc = 0; //number of occurrences of vowel/consonant in the actual members of the linked list


typedef struct Candidate {
    struct Candidate *next;
    char *password;
}Candidate;


/* pre : str!=NULL, str is a string containing only letters ranging a-z
 * post : returns the number of occurrences of vowel or consonant, depending on the global variable consonant_or_vowel;
 */
int countOcc (char* str) {
    if (str == NULL) {
        return 0;
    }
    char* cur = str; //a pointer to browse the string
    int vowel = 0; //to count the number of vowel's occurrences
    int i;
// ou alors c'est plus propre de faire while (*cur != %0) ?
    for (i = 0; i < strlen(str); i++) { //browsing the string
        if (*(cur+i) == 'a' || *(cur+i) == 'e' || *(cur+i) == 'i' || *(cur+i) == 'o' || *(cur+i) == 'u' || *(cur+i) == 'y') { //the current char is a vowel
            vowel ++;
        }
    }

    if(consonant_or_vowel == 'v')
        return vowel;
    else
        return strlen(str)-vowel; //every char that is not a vowel is a consonant
}

/*pre : head != NULL, head->password != NULL, pwd != NULL
 *post : Checks if a password is the be added to the list of candidates by comparing his length to to the current candidates length.
 *
 *If the password's length is greater, the current list is replaced with a list containing only this password as candidate.
 *Else if the password's length is identical, the password is added to the list of candidates
 *Else (the password's length is shorter), the password is not added and thus the list stays unchanged.*/
void update_candidate(Candidate* head, char* pwd) { //len a remplacer par nbOcc (pr clarte)
    if (head == NULL || head->password == NULL || pwd == NULL){
        return;
    }

    int pwdOcc = countOcc(pwd);

    if (pwdOcc > curOcc) { //then a new head is created
        head->next = NULL;
        head->password = pwd;

        curOcc = pwdOcc; //update of the global variables
        listSize = 1;
    }
    else if (pwdOcc == curOcc) { //then a new Candidate is added to the linked list
        Candidate* newCand = malloc(sizeof(Candidate));
        *newCand = (Candidate){head->next, pwd};
        head->next = newCand;
        listSize++; //update of the global variable
    }
}

//add pre/post + change to manage other possible output
char* writeOutput(Candidate* head) { //no need to free the element of the linked list : when the program stops, all the associated memory is freed
    char* strOut = malloc(listSize*10*sizeof(char));
    Candidate* nextCand = head;

    while (nextCand != NULL) {
        strcat(strOut, nextCand->password);
        strcat(strOut, "\n");

        nextCand = nextCand->next;
    }
    return strOut;
}


int main(int argc, char *argv[]) {

    // we first initialise the global variables with the getopt() function
    int opt = 0;
    while ((opt = getopt(argc, argv, "t:co:")) != -1) {
        switch (opt) {
            case 't' :
                nbThread = atoi(optarg); //if we do a cast, we get values from the ASCII table, which is not what we want
                break;
            case 'c' :
                consonant_or_vowel = 'c';
                break;
            case 'o' :
                stdOutput = 0;
                fileOutput = optarg;
                break;
            case '?' :
                fprintf(stderr, "Unknown argument : %d\n", optopt);
                break;

        }

    }


    //thread de lecture

    //producteur-consommateur #1

    //producteur-consommateur #2

    Candidate a = {NULL, "pwd"};
    Candidate* head = &a;
    //interaction LL

    //tests pdt le dvpment
    printf("Test starto !\n");

    printf("nbThread : %d\n", nbThread);
    printf("consonant_or_vowel : %c\n", consonant_or_vowel);
    printf("sdtOutput : %d\n", stdOutput);
    if (fileOutput != NULL) {
        printf("fileOutput : %s\n", fileOutput);
    }

    printf("Test complete !\n");

    char* stringOut = writeOutput(head);
    //output
    if (stdOutput)
        printf("%s", stringOut);
    else {
        int fdOut = creat(fileOutput, S_IWUSR);
        if(fdOut == 1) {
            fprintf(stderr, "could not open/create output file");
            return EXIT_FAILURE;
        }

    }

    return EXIT_SUCCESS;
}