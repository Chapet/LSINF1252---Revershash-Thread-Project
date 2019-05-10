#include <CUnit.h>
#include <src/cracker.h>


// initialisation //

// ./prog //                        // Test sans argument, on vérifie que rien n'est changé.

// ./prog -c //                     // Test que le critère de sélection devient bien les consonnes.

// ./prog -t 4 //                   // Test que le nombre de thread est bien changé.

// ./prog -o filename //            // Test le changement de la sortie standard.

// ./prog -c -t 8 -o filename //    // Test avec tous les arguments.

// ./prog -r                        // Test avec un argument non repris pour voir le message d'erreur.

//--------------------//

// Fonction Insert item //
void test_insert_item (void){


    CU_ASSERT_DOUBLE_EQUAL(tailleactuelleavant,tailleactuelle,1); // On vérifie que tailleactuelle ne s'incrémente que de 1.

}
//---//

//--------------//

// Fonction countOcc //
void test_countOcc(void) {

    // Attention penser à include les variables globales dans le header aussi.
    char *test = aaa;
    CU_ASSERT_EQUALS(countOcc(test), 3);      //Test trois fois la même voyelle.
    CU_ASSERT_EQUALS(countOcc(test), 0);      // Test si l'absence de consonne renvoie bien 0.
    char *test2 = aeiouy;
    CU_ASSERT_EQUALS(countOcc(test2), 6);     // Test si toutes les voyelles sont bien prises en compte.
    char *testgenerale = systemeinfo;        // Test un cas general.
    CU_ASSERT_EQUALS(countOcc(testgenerale), 5);
    CU_ASSERT_EQUALS(countOcc(testgenerale), 6);
}
// -----------------//

// Fonction listSize //
void test_listSize(void) {

    Candidate test = {NULL, "abcdefgh"};                            // Test dans le cas où il n'y a que la tête.
    CU_ASSERT_EQUALS(ListSize(&test), 1);

    Candidate test = {NULL, "abcdefgh"};
    Candidate test2 = {&test, "i"};
    Candidate test3 = {&test2, "j"};
    CU_ASSERT_EQUALS(ListSize(&test3), 3);                           // Test dans un cas général avec une taille = 3.

}
// ------------------ //

// Fonction update_candidate //
void test_update_candidate(void) {

    // A Changer si on enlève l'argument head.
    Candidate test = {NULL, "abcdefg"};
    update_candidate(&test, "hijklm");
    CU_ASSERT_PTR_NULL(test.next);                                // Verifie que le candidat suivant existe.
    CU_ASSERT_EQUALS(test.next.password, "hijklm");                // Verifie que le mot de passe suivant est le bon.
    Candidate test2 = {NULL, "zrtxv"};
    update_candidate(&test2, "");                                  // Test en ajoutant un mdp vide.
    CU_ASSERT_PTR_NULL(test2.next);
    CU_ASSERT_EQUALS(test.next.password, "")

}



int main()
{

    CU_pSuite Suite1 = NULL;
    CU_pSuite Suite2 = NULL;
    CU_pSuite Suite3 = NULL;

    // On initialise le registry.

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* On ajoute les suites au registry */
    Suite1 = CU_add_suite("Suite_1", NULL, NULL);
    if (NULL == Suite1) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    Suite2 = CU_add_suite("Suite_2",NULL,NULL);
    if (NULL == Suite2) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    Suite3 = CU_add_suite("Suite_3",NULL,NULL);
    if(NULL == Suite3) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* On ajoute les tests aux suites correspondantes */
    if ((NULL == CU_add_test(Suite1, "test the initialisation", test_initialisation)) ||
        (NULL == CU_add_test(Suite1, "test of insert_item", test_insert_item))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if((NULL == CU_add_test(Suite2, "test of countOcc()", test_countOcc)) ||
       (NULL == CU_add_test(Suite2, "test of listSize()", test_listSize)) ||
       (NULL == CU_add_test(Suite2, "test of update_candidate()", test_update_candidate))){
        CU_cleanup_registry();
        return CU_get_error();
    }
    if(NULL == CU_add_test(Suite3, "",test_globale)){
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}








