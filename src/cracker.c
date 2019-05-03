#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "sha256.h"
#include "reverse.h"

//def of global variables and structures
typedef struct Candidate {
    struct Candidate *next;
    char *password;
}Candidate;



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

/*pre : head != NULL, head->password != NULL, pwd != NULL
  post :Checks if a password is the be added to the list of candidates by comparing his length to to the current candidates length.

  If the password's length is greater, the current list is replaced with a list containing only this password as candidate.
  Else if the password's length is identical, the password is added to the list of candidates
  Else (the password's length is shorter), the password is not added and thus the list stays unchanged.*/
void update_candidate(Candidate* head, int len, char* pwd) {
    if (head == NULL || head->password == NULL || pwd == NULL){
        return;
    }

    int pwdLen = strlen(pwd);

    if (pwdLen > len) {
        head->next = NULL;
        head->password = pwd;
    }
    else if (pwdLen == len) {
        Candidate* newCand = malloc(sizeof(Candidate));
        *newCand = (Candidate){head->next, pwd};
        head->next = newCand;
    }
}