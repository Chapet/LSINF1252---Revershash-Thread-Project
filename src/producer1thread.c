//
// Created by Arnaud on 29/04/2019.
//

// Ce producer va simplement lire 32 bytes dans le fichier (on pourrait rajouter le ferme se c'est la fin)
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
        if (Nbre_fichier >= Nombredefichier) {
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
// Ce qu'il reste à faire pour produce :
//- Gerer la variable Nbre_fichier qui correspond à quelle fichier on se trouve maintenant.
//- Definir opened et le mettre = 0 au début comme ça on passe direct au premier fichier.
//- Gerer la liste filename[].