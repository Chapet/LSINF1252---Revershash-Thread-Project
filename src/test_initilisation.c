#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int nombredethread = 1;                                 // Indique le Nombre de thread que l'on peut utiliser pour la parallélisation, par défaut vaut 1.
    int voyelle = 1;                                        // Si vaut 1 alors le critère de sélection est les voyelles, sinon ce sont les consonnes.
    int sortiestandard = 1;                                 // Indique si l'output est la sortie standard ou non.
    char *fichierout = NULL;                                       // Si l'output n'est pas la sortie standard alors elle devra être écrite dans fichierout.

    int opt = 0;
    while ( (opt = getopt(argc, argv, "t:co:")) != -1 ) {
        switch(opt){
            case 't' :
                nombredethread = atoi(optarg);
                break;
            case 'c' :
                voyelle = 0;
                break;
            case 'o' :
                sortiestandard = 0;
                fichierout = optarg;
                break;
            case '?' :
                fprintf(stderr,"Argument inconnu : %d\n", optopt);
                break;

        }

    }
	printf("nombre de thread %d\n",nombredethread); 
	printf("voyelle %d\n", voyelle);
	printf("sortie standard %d\n", sortiestandard);
	if(fichierout != NULL){
	printf("fichier out : %s \n", fichierout);
	}
	printf("Argc %d\n",argc);
}
