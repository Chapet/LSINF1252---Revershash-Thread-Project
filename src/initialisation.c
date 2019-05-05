
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int nombredethread = 1;                                 // Indique le Nombre de thread que l'on peut utiliser pour la parallélisation, par défaut vaut 1.
    int voyelle = 1;                                        // Si vaut 1 alors le critère de sélection est les voyelles, sinon ce sont les consonnes.
    int sortiestandard = 1;                                 // Indique si l'output est la sortie standard ou non.
    char *fichierout;                                       // Si l'output n'est pas la sortie standard alors elle devra être écrite dans fichierout.

    int opt = 0;
    while ( (opt = getopt(argc, argv, "t:co:")) != -1 ) {
        switch(opt){
            case 't' :
                nombredethread = optarg;
                break;
            case 'c' :
                voyelle = 0;
                break;
            case 'o' :
                sortiestandard = 0;
                fichierout = optarg;
                break;
            case '?' :
                fprintf(stderr,"Argument inconnu", optopt);
                break;

        }

    }
}