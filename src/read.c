//
// Created by Arnaud on 11/04/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define NBRE_PROD = 1 ;                         // Du coup j'ai mis 1 mais voilà.
#define NBRE_CONSO = 1 ;                        // En attente des conso.


char filename [][] ;
int Nombredefichier = 3;                        // dépendra de l'argument de la fonction.
int Slotsbuffer = Nombredefichier * 3;          // Défini la taille du (facteur 3 arbitraire).

// int * buf = malloc(32 * Slotsbuffer);        // 32 * la taille car on sait que les hash font 32bytes.
char buf[Slotsbuffer][32];                      // Un tableau avec les hashs qui font 32bytes.
int tailleactuelle ;                            // int qui va nous servir dans le schéma producteur consommateur.


// mutex et sémaphore pour le schéma prod/conso.

pthread_mutex_t mutex ;
sem_t empty;
sem_t full;

// Producteur
void producer (void){                           // Voir autre fichier testthreadconso.
    int item;
    while(true)
    {
        item=produce(item);
        sem_wait(&empty);                        // attente d'un slot libre
        pthread_mutex_lock(&mutex);
        // section critique
        insert_item();
        pthread_mutex_unlock(&mutex);
        sem_post(&full);                         // il y a un slot rempli en plus
    }
}


// Consommateur                Pas encore traité : schéma standard du cours en attendant.
void consumer (void){
    int item;
    while(true)
    {
        sem_wait(&full); // attente d'un slot rempli
        pthread_mutex_lock(&mutex);
        // section critique
        item=remove(item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // il y a un slot libre en plus
    }
}

int main () {
                                                    // initialisation mutex/ sémaphores pour les schéma prod/cons.
    pthread_mutex_init (&mutex , NULL);
    sem_init (&empty , 0 , Slotsbuffer);
    sem_init (&full , 0 , 0);

    int opened[Nombredefichier];
    for (int i = 0 ; i<Nombredefichier ; i++){
        opened[i] = open(filename[i] , O_RDONLY);   // on veut ouvrir tous les fichiers s'il y a plusieurs threads prod.
        if(opened[i] == -1)
            return -1 ;                             // problème d'ouverture fichier i.

    }
                                                    // Lançons les threads consommateurs et producteurs.
    pthread_t consumer[NBRE_CONSO];
    pthread_t producer[NBRE_PROD];

    for (int i = 0 ; i < NBRE_CONSO ; i++){
        if(pthread_create (&consumer[i], NULL , consume , NULL)){
            printf("erreur de création");           // Changer ça en mieux mais c'est pour voir.
            return -1;
        }
    }
                                                    // Pour les prod on leur donne comme argument le bon filename.
                                                    // Ici c'est le cas où on a un thread par fichier.
    for (int i = 0 ; i < NBRE_PROD ; i++){
        if(pthread_create (&producer[i]), NULL , produce ,(void *) &(opened[i]) ){
            printf("erreur de création");
            return -1;
        }
    }

    // Maintenant il faut join les différents thread.

    for (int i = 0 ; i < NBRE_CONSO ; i++){
        if(pthread_join (consumer[i], NULL)){
            printf("erreur dans join ");
            return -1;
        }
    }

    for (int i = 0 ; i< NBRE_PROD ; i++){
        if(pthread_join (producer[i] , NULL)){
            printf("erreur dans join");
            return -1;
        }
    }
    // Puis on destroy les sémaphores.
    err = sem_destroy(&empty);
    if(err != 0){
        return -1;
    }
    err = sem_destroy (&full);
    if(err != 0){
        return -1;
    }

    // On libère la mémoire allouée par malloc

    free (buf);

    // Puis on close tous les fichiers (on peut penser à les fermer avant si on utilise pas un schéma avec un thread par fichier)

    for(int i = 0 ; i < Nombredefichier ; i++){
        if(close (opened[i]) == -1 ){
            printf("erreur de fermeture");
            return -1;
        }
    }
    return 0;
}