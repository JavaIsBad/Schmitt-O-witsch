#include "ChaineDeSchmittOwitsch.h"
#include <stdio.h>
#include <time.h>
#define CHAR_MAX 100
#define ERROR_MAX 1e-2

void recupDebut(timer *tim){
    tim->debut=clock();
}

void recupFin(timer *tim){
    tim->fin=clock();
}

double calculerTemps(timer *tim){
    if (tim->debut != -1 && tim->fin != -1)
        tim->tempsTotal= (double)tim->fin - tim->debut;
}

int comparerDeuxMarkov(Markovien *mark1, Markovien *mark2){ //1 si tous les nombres contenus dans les markov 1 et 2 sont similaires a ERROR_MAX pres
    int i,j;
    for (i=0; i<27; i++){
        for (j=0; j<27; j++){
            if (!(egaliteNombresque(mark1->marko[i][j].nbr, mark2->marko[i][j].nbr, ERROR_MAX))
            return 0;
        }
    }
    return 1;
}

void moyenneMinable(Markovien *mark, int ligne, int colonne, double nbr){
    mark->marko[ligne][colonne].nbr = (mark->marko[ligne][colonne].nbr + nbr)/2.;
}

void moyenneStyle(Markovien *mark, int ligne, int colonne, double nbr){
    int ccpt = mark->marko[ligne][colonne]->cpt;
    int nnbr = mark->marko[ligne][colonne]->nbr;
    if (ccpt == 0){
        mark->marko[ligne][colonne]->nbr=nbr;
    }
    else{
        mark->marko[ligne][colonne]->nbr=   nnbr * (double)(ccpt/ccpt+1) + nbr * (1./ccpt+1)
        //Qq exemples :
        /* 1 => Moyenne 1/1 = 1                                           JUSTE
            rajoute 2 => moyenne = 1 * 1/2 + 2 * 1/2 => 3/2               JUSTE
            rajoute 3 => moyenne = 3/2 * 2/3 + 3 * 1/3 => 1+1 = 2         JUSTE
            rajoute 4 => moyenne = 2 * 3/4 + 4 * 1/4 = 6/4 + 4/4 = 10/4   JUSTE
            On va supposer que c'est juste a tous les rangs, j'ai un peu la flemme de nous faire une petite d"émonstration a la récurrence :p
            J'ai trouver ça TOUT SEUL! JE SUIS CONTENT!
            */
    }
    mark->marko[ligne][colonne]->cpt++;
}

int egaliteNombresque(double un, double deux, double error){
    return (un + error > deux && un - error < deux && deux + error > un && deux - error < un); //1 si un est compris entre 2 + error et 2 - error et deux est compris entre 1 - error et 1 + error
}

int main (void){
    Markovien mark;
    Markovien mark2;
    timer *timm = malloc(sizeof(timer));

    int precedent=-1, actuel=-1;
    int cpt=0;
    double temps=0;
    printf("Entrez votre chaine de caracteres (caracteres spécials non autorisés)\n\n");

    // Pour le premier
    while (cpt < CHAR_MAX){
        if (cpt==0){
            actuel=getchar();
            recupDebut(timm);
        }
        else{
            precedent=actuel;
            actuel=getchar();
            recupFin(timm);
            temps=calculerTemps(timm);
            moyenneStyle(&mark,precedent,actuel,temps); //grace au énum
            recupDebut(timm);
        }
        cpt++;
    }
    printf("C'est fini pour vous, c'est l'heure du 2eme\n\n");

    //Le 2eme
    precedent=-1;
    actuel=-1;
    cpt=0;
    temps=0;
    timm->debut=0;
    timm->fin=0;

    while (cpt < CHAR_MAX){
        if (cpt==0){
            actuel=getchar();
            recupDebut(timm);
        }
        else{
            precedent=actuel;
            actuel=getchar();
            recupFin(timm);
            temps=calculerTemps(timm);
            moyenneMinable(&mark2,precedent,actuel,temps);
            recupDebut(timm);
        }
        cpt++;
    }

    printf("C'est fini, c'est l'heure du calcule\n");
    if (comparerDeuxMarkov()==1){
        printf("Je pense que vous êtes la même personne\n");
        return 1;
    }
    else{
        printf("Je pense que vous n'êtes pas la même personne\n");
        return 0;
    }
}
