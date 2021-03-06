#ifndef __CHAINEDESCHMITTOWITSCH_H
#define __CHAINEDESCHMITTOWITSCH_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

enum {
a,b,c,d,e,f,g,
h,i,j,k,l,m,n,
o,p,q,r,s,t,u,
v,w,x,y,z,
SPACE,BACKSPACE,
}
typedef struct {
    clock_t *debut;
    clock_t *fin;
    double tempsTotal;
} timer;

typedef struct {
    int cpt;
    double nbr;
} cellule;

typedef struct {
    cellule [28][28] marko;
} Markovien;



/*
  0 1 2 3 4 5 6 7 8 9   10 11 12 13 14 15 16 17  18 19 20 21 22 23 24 25     26         27
  a b c d e f g h i j   k  l  m  n  o  p  q  r   s  t  u  v  w  x  y  z  [espace] [backspace]
a
b
c
d
e
f
g
h
i
j
k
l
m
n
o
p
q
r
s
t
u
v
w
x
y
z
[espace]
*/

void recupDebut(timer *tim);
void recupFin(timer *tim);
double calculerTemps(timer *tim);
int comparerDeuxMarkov(Markovien *mark1, Markovien *mark2);
int egaliteNombresque(double un, double deux, double error);
void moyenneMinable(Markovien *mark, int ligne int colonne, double nbr);
void moyenneStyle(Markovien *mark, int ligne, int colonne, double nbr);
void __init(Markovien *mark);

#endif //__CHAINEDESCHMITTOWITSCH_H
