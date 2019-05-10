#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/Main2.c"

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

//--------------//

// Fonction countOcc //
void test_countOcc(void) {

    char *test = "aaa";
    consonant_or_vowel = 'v';
    CU_ASSERT_EQUAL(countOcc(test), 3);      //Test trois fois la même voyelle.
    consonant_or_vowel = 'c';
    CU_ASSERT_EQUAL(countOcc(test), 0);      // Test si l'absence de consonne renvoie bien 0.
    char *test2 = "aeiouy";
    consonant_or_vowel = 'v';
    CU_ASSERT_EQUAL(countOcc(test2), 6);     // Test si toutes les voyelles sont bien prises en compte.
    char *testgenerale = "systemeinfo";        // Test un cas general.
    consonant_or_vowel = 'v';
    CU_ASSERT_EQUAL(countOcc(testgenerale), 5);
    consonant_or_vowel = 'c';
    CU_ASSERT_EQUAL(countOcc(testgenerale), 6);
}
// -----------------//

// Fonction listSize //
void test_listSize(void) {
    Candidate testlist = {NULL, "abcdefgh"};                            // Test dans le cas où il n'y a que la tête.
    head = &testlist;
    CU_ASSERT_EQUAL(listSize(), 1);

    Candidate listtest = {NULL, "abcdefgh"};
    Candidate listtest2 = {&listtest, "i"};
    Candidate listtest3 = {&listtest2, "j"};
    head = &listtest3;
    CU_ASSERT_EQUAL(listSize(), 3);                           // Test dans un cas général avec une taille = 3.

}
// ------------------ //

// Fonction update_candidate //
void test_update_candidate(void) {

     //A Changer si on enlève l'argument head.
    Candidate test = {NULL,"fgt"};
    head = &test;
    update_candidate("plm");
    CU_ASSERT_EQUAL(test.next->password, "plm");               // Verifie que le mot de passe suivant est le bon.
    Candidate test2 = {NULL, "zrt"};
    head= &test2 ;
    update_candidate("ae");                                        // Test en ajoutant un mdp avec un nombre de voyele différent.
    CU_ASSERT_EQUAL(head->password, "zrt");

}



int main()
{

    CU_pSuite Suite1 = NULL;

    // On initialise le registry.

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* On ajoute les suites au registry */
    Suite1 = CU_add_suite("Suite_1", NULL, NULL);
    if (NULL == Suite1) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // On ajoute les fonctions aux suites.
    if((NULL == CU_add_test(Suite1, "test of countOcc()", test_countOcc)) ||
       (NULL == CU_add_test(Suite1, "test of listSize()", test_listSize)) ||
       (NULL == CU_add_test(Suite1, "test of update_candidate()", test_update_candidate))){
        CU_cleanup_registry();
        return CU_get_error();
    }

    // On run les tests.

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}








