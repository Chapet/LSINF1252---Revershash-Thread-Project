#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>


#include "sha256.h"
#include "reverse.h"

//def of global variables and structures
typedef struct Candidate {
    struct Candidate *next;
    char *password;
}Candidate;

char consonant_or_vowel = 'v';
int curOcc = 0;

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

        curOcc = pwdOcc; //update the global variable
    }
    else if (pwdOcc == curOcc) { //then a new Candidate is added to the linked list
        Candidate* newCand = malloc(sizeof(Candidate));
        *newCand = (Candidate){head->next, pwd};
        head->next = newCand;
    }
}


void writeOutput(Candidate* head) {
    Candidate* nextCand = head;

    while (nextCand != NULL) {
        printf("%s\n", nextCand->password);

        nextCand = nextCand->next;
    }
}

int main(int argc, char *argv[]) {

    //initialisation

    //thread de lecture

    //producteur-consommateur #1

    //producteur-consommateur #2

    //interaction LL

    //ecriture

    printf("Test starto !\n");

    printf("Test complete !\n");
    return EXIT_SUCCESS;
}