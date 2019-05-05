
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define NBRE_PROD = 1 ;                         // Du coup j'ai mis 1 mais voilà.
#define NBRE_CONSO = 1 ;                        // En attente des conso.

char filename [][] ;                            // Liste de string contenant les noms des fichiers
int Nombredefichier = 3;                        // Dépend de l'input.
int Slotsbuffer = Nombredefichier * 3;          // Défini la taille du buffer (facteur 3 arbitraire).

// int * buf = malloc(32 * Slotsbuffer);        // 32 * la taille car on sait que les hash font 32bytes.
char buf[Slotsbuffer][32];                      // Un tableau avec les hashs qui font 32bytes.



int tailleactuelle ;                            // Indique la taille actuelle du buffer.
int Nbre_fichier = -1;                          // Indique le fichier actuel que l'on traite.
int opened = 0;                                 // File descriptor, initialisé à 0 pour indiquer que le fichier actuel est vide.




// mutex et sémaphore pour le schéma prod/conso.

pthread_mutex_t mutex ;
sem_t empty;
sem_t full;
















// Ce producer va simplement lire 32 bytes dans le fichier
// et l'ajoute dans la liste du buffer principal.
*void producer (void* arg){
    while(true)
    {
        int * bufread = malloc (32);                // On malloc les 32 bytes nécéssaires.

        produce(*arg , bufread);                   // Ici doit voir quels fichiers lire et lire et nouveau si besoin
        // ATTENTION voir si il faut pas mettre également le producer dans le mutex(ou dans un autre mutex) car il ne faut pas qu'il y ait de conflit sur quelle partie des fichiers lire.
        sem_wait(&empty);                          // attente d'un slot libre
        pthread_mutex_lock(&mutex);

        insert_item(tailleactuelle);               // Ecrire dans la liste

        pthread_mutex_unlock(&mutex);
        sem_post(&full);                           // il y a un slot rempli en plus

        free (bufread);
    }

}


// Rempli la case numéro : tailleactuelle de la liste par le bufread rempli par produce et incrémente tailleactuelle.
void insert_item(int tailleactuelle){
    buf[tailleactuelle] = *bufread;
    tailleactuelle++;

}


// Va décider quel fichier lire
// ATTENTION : "Doit-on fermer le fichier après chaque lecture du thread car on ne connait le temps que le fichier restera ouvert sans être utiliser"
// - parait inutile + chiant car le filedescriptor devra à chaque fois être mis à la bonne place pour la lecture du fichier + parait un peu overkill..
void produce (int * bufread){
    // Tant qu'on est en fin de fichier on passe au fichier suivant (sert juste si il y a un fichier vide qui est donné en argument)
    while (opened == 0) {
        Nbre_fichier++;

        // Rien à faire si on a fini de lire le dernier fichier.
        if (Nbre_fichier >= NBRE_FICHIER) {
            return;                                                 // Ca produira peut-être des problèmes de ne rien renvoyer mais normalement ne devrait pas arriver ici.
        }
        // Sinon on ouvre le nouveau fichier.
        opened = open(filename[Nbre_fichier], O_RDONLY)
    }
    if (read(opened, bufread, 32) == -1) {            // On lit 32 bytes du fichier, on considère tjs que le nbre de bytes total est proportionnel à 32.
        printf("erreur de lecture");
        return;
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

    // Lançons les threads consommateurs et producteurs.
    pthread_t consumer[NBRE_CONSO];
    pthread_t producer[NBRE_PROD];

    for (int i = 0 ; i < NBRE_CONSO ; i++){
        if(pthread_create (&consumer[i], NULL , consume , NULL)){
            printf("erreur de création");           // Changer ça en mieux mais c'est pour voir.
            return -1;
        }
    }
    // On ne crée qu'un seul thread producteur.
    for (int i = 0 ; i < NBRE_PROD ; i++){
        if (pthread_create(&producer[i]), NULL, produce, NULL) {
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

    return 0;
}