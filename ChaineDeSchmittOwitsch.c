#include "ChaineDeSchmittOwitsch.h"
#include <stdio.h>
#include <time.h>
#define CHAR_MAX 100
#define ERROR_MAX 0.2

void printM(Markovien *m){
    int i, j;
    for(i=0; i<NBLETTRE; ++i){
        printf("\n");
        for(j=0; j<NBLETTRE; ++j){
            printf("%c->%c %lf ", 'a'+i, 'a'+j, m->marko[i][j].nbr);
        }
    }
    printf("\n");
}


void recupDebut(timer *tim){
    gettimeofday(&tim->debut, NULL);
}

void recupFin(timer *tim){
    gettimeofday(&tim->fin, NULL);
}

double calculerTemps(timer *tim){
    long double ret = (double) tim->fin.tv_usec / 1000000;
    ret += tim->fin.tv_sec;
    long double debut = (double) tim->debut.tv_usec / 1000000;
    debut += tim->debut.tv_sec;
    return ret - debut;
}

int comparerDeuxMarkov(Markovien *mark1, Markovien *mark2){ //1 si tous les nombres contenus dans les markov 1 et 2 sont similaires a ERROR_MAX pres
    int i,j;
    for (i=0; i<27; i++){
        for (j=0; j<27; j++){
            if (!(egaliteNombresque(mark1->marko[i][j].nbr, mark2->marko[i][j].nbr, ERROR_MAX)))
                return 0;
        }
    }
    return 1;
}

void moyenneStyle(Markovien *mark, int ligne, int colonne, double nbr){
    if(!(ligne >= 0 && colonne >= 0 && ligne < NBLETTRE && colonne < NBLETTRE) || nbr > 3)
        return;
    int ccpt = mark->marko[ligne][colonne].cpt;
    int nnbr = mark->marko[ligne][colonne].nbr;
    if (ccpt == 0){
        mark->marko[ligne][colonne].nbr=nbr;
    }
    else{
        mark->marko[ligne][colonne].nbr=   nnbr * (double)(ccpt/ccpt+1) + nbr * (1./ccpt+1);
        //Qq exemples :
        /* 1 => Moyenne 1/1 = 1                                           JUSTE
           rajoute 2 => moyenne = 1 * 1/2 + 2 * 1/2 => 3/2               JUSTE
           rajoute 3 => moyenne = 3/2 * 2/3 + 3 * 1/3 => 1+1 = 2         JUSTE
           rajoute 4 => moyenne = 2 * 3/4 + 4 * 1/4 = 6/4 + 4/4 = 10/4   JUSTE
           On va supposer que c'est juste a tous les rangs, j'ai un peu la flemme de nous faire une petite d"émonstration a la récurrence :p
           J'ai trouver ça TOUT SEUL! JE SUIS CONTENT!
           */
    }
    mark->marko[ligne][colonne].cpt++;
}

int egaliteNombresque(double un, double deux, double error){
    if(un == 0 || deux == 0)
        return 0 == 0;
    return (un + error > deux && un - error < deux); //1 si un est compris entre 2 + error et 2 - error et deux est compris entre 1 - error et 1 + error
}

void initMarkovienZero(Markovien *m){
    int i, j;
    for(i=0; i < NBLETTRE; ++i)
        for(j=0; j < NBLETTRE; ++j){
            m->marko[i][j].cpt = 0;
            m->marko[i][j].nbr = 0.;
        }
}

int main (void){
    initscr();
    refresh();
    Markovien mark;
    Markovien mark2;
    timer timme;
    timer* timm = &timme;

    initMarkovienZero(&mark);
    initMarkovienZero(&mark2);

    char precedent=-1, actuel=-1;
    int cpt=0;
    double temps=0;
    printf("Entrez votre chaine de caracteres (caracteres specials non autorises)\n");
    refresh();

    // Pour le premier
    while (cpt < CHAR_MAX && actuel != '\n'){
        if (cpt==0){
            actuel = getch();
            if(actuel == ERR)
                continue;
            actuel = actuel >= 'A' && actuel <= 'Z' ? actuel - 'A' : actuel >= 'a' && actuel <= 'z' ? actuel - 'a' : actuel;
            recupDebut(timm);
        }
        else{
            precedent=actuel;
            actuel = getch();
            if(actuel == ERR)
                continue;
            actuel = actuel >= 'A' && actuel <= 'Z' ? actuel - 'A' : actuel >= 'a' && actuel <= 'z' ? actuel - 'a' : actuel;
            recupFin(timm);
            temps=calculerTemps(timm);
            moyenneStyle(&mark,precedent,actuel,temps); //grace au énum
            recupDebut(timm);
        }
        printf("%c" , actuel);
        cpt++;
    }
    printf("C'est fini pour vous, c'est l'heure du 2eme\n\n");

    //Le 2eme
    precedent=-1;
    actuel=-1;
    cpt=0;
    temps=0;

    while (cpt < CHAR_MAX && actuel != '\n'){
        if (cpt==0){
            actuel = getch();
            if(actuel == ERR)
                continue;
            actuel = actuel >= 'A' && actuel <= 'Z' ? actuel - 'A' : actuel >= 'a' && actuel <= 'z' ? actuel - 'a' : actuel;
            recupDebut(timm);
        }
        else{
            precedent=actuel;
            actuel = getch();
            if(actuel==ERR)
                continue;
            actuel = actuel >= 'A' && actuel <= 'Z' ? actuel - 'A' : actuel >= 'a' && actuel <= 'z' ? actuel - 'a' : actuel;
            recupFin(timm);
            temps=calculerTemps(timm);
            moyenneStyle(&mark2, precedent, actuel, temps);
            recupDebut(timm);
        }
        printf("%c" , actuel);
        cpt++;
    }


    printf("C'est fini, c'est l'heure du calcule\n");
    endwin();
    if (comparerDeuxMarkov(&mark, &mark2)==1){
        printf("Je pense que vous etes la meme personne\n");
    }
    else{
        printf("Je pense que vous n etes pas la meme personne\n");
    }
  //  printM(&mark);
  //  printM(&mark2);
    return 0;
}
