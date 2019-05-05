//
// Created by Arnaud on 12/04/2019.
//

// Ce producer va simplement lire 32 bytes dans le fichier (on pourrait rajouter le ferme se c'est la fin)
// et l'ajoute dans la liste du buffer principal.
*void producer (void* arg){
    int * bufread = malloc (32);                // On malloc les 32 bytes nécéssaires.
    while(true)
    {
        produce(*arg , bufread);
        sem_wait(&empty);                        // attente d'un slot libre
        pthread_mutex_lock(&mutex);

        insert_item(tailleactuelle);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);                         // il y a un slot rempli en plus
    }
    free (bufread);
}

void insert_item(int tailleactuelle){
buf[tailleactuelle] = *bufread;
tailleactuelle++;

}
void produce (int opened,int * bufread){
    if(read(opened,bufread, 32) == -1)   {            // Denouveau on lis 32 bytes du fichiers
        printf("erreur de lecture");
        return ;
    }
}