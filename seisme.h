#ifndef SEISME_H_INCLUDED
#define SEISME_H_INCLUDED
#include <math.h>
#include "player.h"
#include "keyboard.h"

int seisme(int n,int h);
int geth(char*** plateau,int haut,int line,int colonne);
void faire_seisme(char*** p,char*** plateau,int n,int haut);
void afficheChoisirSeisme(char*** p,char*** plateau,int n,int haut,int line_p,int colonne_p);
int* choisirColonneSeisme(char*** p,char*** plateau,int n,int haut);
/*//////DESSUS SEISME/////////*/
int OtourSeisme(char*** p,char*** plateau,int n,int haut);
int XtourSeisme(char*** p,char*** plateau,int n,int haut);

/*////// 3D SEISME ////////*/
int OtourSeisme3D(char*** p,char*** plateau,int n,int haut);
int XtourSeisme3D(char*** p,char*** plateau,int n,int haut);



#endif /*/ SEISME_H_INCLUDED*/
