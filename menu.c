#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "player.h"
#include "seisme.h"
#include "keyboard.h"


/*@require: rien
  @assigns: rien
  @ensure : effacer le flux du input(stdin)
*/
void clearStdin()
{
    while ((getchar()) != '\n');
}
/*@require: rien
  @assigns: rien
  @ensure : presenter le menu du jeu
*/
void showInfo()
{
    printf("\n*=========================================================*");
    printf("\n*=================Bienvenu a Morpion 3D===================*");
    printf("\n*=========================================================*");
    printf("\n*===================(pour deux jeuer)========by-DinghaoLI=*");
    printf("\n*=========================================================*");
    printf("\n Choisir la variant: ");
    printf("\n");
    printf("\n               Taper 1 -> Vue de dessus ");
    printf("\n               Taper 2 -> Morpion 3D ");
    printf("\n               Taper 3 -> Vue de dessus SEISME !! ");
    printf("\n               Taper 4 -> Morpion SEISME !! ");
    printf("\n");

}



/*@require: rien
  @assigns: rien
  @ensure : retourner le numero de variante du jeu
*/
int start()
{
    char key;
    printf("\n Taper 1,2,3 ou 4 et puis taper 'Enter' \n");
    printf("\n Vous voulez choisir :  ");
    scanf("%c",&key);
    clearStdin();
    while((key!='1')&&(key!='2')&&(key!='3')&&(key!='4'))
    {

      printf("Encore une fois! \n");
      scanf("%c",&key);
      clearStdin();
    }

    return ((int)key-'0');
}

/*@require: rien
  @assigns: creer l'espace pour platrau etc dans la memoire
  @ensure : le processus du jeu (variante dessus)
 */
void dessus()
{

    char*** plateau;
    char taille[3];
    char *p = taille;
    char plafont[3];
    char *chaut=plafont;
    int *position;
    int haut=1;
    char** endptr=(char**)calloc(10,sizeof(char*));
    long int n;

    printf("\n*=========================================================*");
    printf("\n*===================La variante Dessus====================*");
    printf("\n*=========================================================*");
    printf("\n*Taper la taille(>2) du plateau et puis taper 'Enter'.SVP *");
    printf("\n* taille = ");
    /*/////taille de la plateau*/
    scanf("%s",p);
    clearStdin();
    n=strtol(p,endptr,10);
    while((!isnumber(p))||(n==1))
    {
        printf("Taper un chiffre > 1  \n");
        scanf("%s",p);
        clearStdin();
        n=strtol(p,endptr,10);
    }
    n=strtol(p,endptr,10);
    /*////plafont de la pile*/
    printf("\n*hauteur maximum de la pile = ");
    scanf("%s",chaut);
    clearStdin();
    while(!isnumber(chaut))
    {
        printf("Taper un chiffre\n");
        scanf("%s",chaut);
        while ((getchar()) != '\n');
    }
    haut=strtol(chaut,endptr,10);
    /*/////creer plateau*/
    printf("\n\n........preparation du plateau.....");
    plateau=init(n,haut);
    clearPlateau(plateau,n,haut);  /*// mettre les poteau ‘V’ (vide)*/
    printf("\n Il va commencer!   \n  ");
    printf("\n i:↑ k:↓ j:← l:→ pour choisir la Colonne \n    ");

    afficheDessus(plateau,n,haut);
    printf("\n\n");
    printf("        'X' va commencer ~!        \n");
    /*///premier step*/
    position=choisirColonne(plateau,n,haut);
    ajouterX(plateau,haut,position[0],position[1]);

    /*///circule///*/
    while(PlateauEstPlein(plateau,n,haut)!=1) /*/si la plateau n'est pas plein.*/
        {
           if(Otour(plateau,n,haut))
                break;
           if(PlateauEstPlein(plateau,n,haut)==1)
                 break;
           if(Xtour(plateau,n,haut))
                break;

        }
}

/*@require: rien
  @assigns: creer l'espace pour platrau etc dans la memoire
  @ensure : le processus du jeu (variante 3D)
 */
void variante3D()
{

    char*** plateau;
    char taille[3];
    char *p = taille;
    char plafont[3];
    char *chaut=plafont;
    int *position;
    int haut=1;
    char** endptr=(char**)calloc(10,sizeof(char*));
    long int n;
    printf("\n*=========================================================*");
    printf("\n*=================    La variante 3D   ===================*");
    printf("\n*=========================================================*");
    printf("\n*Taper la taille(>2) du plateau et puis taper 'Enter'.SVP *");
    printf("\n* taille = ");
    /*/////taille de la plateau  */
    scanf("%s",p);
    clearStdin();
    n=strtol(p,endptr,10);
    while((!isnumber(p))||(n==1))
    {
        printf("Taper un chiffre > 1  \n");
        scanf("%s",p);
        clearStdin();
        n=strtol(p,endptr,10);
    }
    n=strtol(p,endptr,10);
    /*////plafont de la pile*/
    printf("\n*hauteur maximum de la pile = ");
    scanf("%s",chaut);
    clearStdin();
    while(!isnumber(chaut))
    {
        printf("Taper un chiffre\n");
        scanf("%s",chaut);
        while ((getchar()) != '\n');
    }
    haut=strtol(chaut,endptr,10);
    /*/////creer plateau/*/
    printf("\n\n........preparation du plateau.....");
    plateau=init(n,haut);
    clearPlateau(plateau,n,haut);  /*// mettre les poteau ‘V’ (vide)*/
    printf("\n Il va commencer!   \n  ");
    printf("\n i:↑  k:↓  j:←  l:→ pour choisir la Colonne \n    ");

    afficheDessus(plateau,n,haut);
    printf("\n\n");
    printf("        'X' va commencer ~!        \n");
    /*///premier step*/
    position=choisirColonne(plateau,n,haut);
    ajouterX(plateau,haut,position[0],position[1]);

    /*///circule///*/
    while(PlateauEstPlein(plateau,n,haut)!=1) /*/si la plateau n'est pas plein.*/
        {
           if(Otour3D(plateau,n,haut))
                break;
           if(PlateauEstPlein(plateau,n,haut)==1)
                 break;
           if(Xtour3D(plateau,n,haut))
                break;

        }
}



/*@require: rien
  @assigns: creer l'espace pour platrau etc dans la memoire
  @ensure : le processus du jeu (variante 3D seisme)
 */
void Morpion3D_seisme()
{

    char*** plateau;
    char*** p;
    char taille[3];
    char *t = taille;
    char plafont[3];
    char *chaut=plafont;
    int *position;
    int haut=1;
    char** endptr=(char**)calloc(10,sizeof(char*));
    long int n;

    printf("\n*=========================================================*");
    printf("\n*================== La variante 3D =======================*");
    printf("\n*========================= seisme ========================*");
    printf("\n*Taper la taille(>2) du plateau et puis taper 'Enter'.SVP *");
    printf("\n* taille = ");
    /*/////taille de la plateau*/
    scanf("%s",t);
    clearStdin();
    n=strtol(t,endptr,10);
    while((!isnumber(t))||(n==1))
    {
        printf("Taper un chiffre > 1  \n");
        scanf("%s",t);
        clearStdin();
        n=strtol(t,endptr,10);
    }
    n=strtol(t,endptr,10);
    /*////plafont de la pile*/
    printf("\n*hauteur maximum de la pile = ");
    scanf("%s",chaut);
    clearStdin();
    while(!isnumber(chaut))
    {
        printf("Taper un chiffre\n");
        scanf("%s",chaut);
        while ((getchar()) != '\n');
    }
    haut=strtol(chaut,endptr,10);
    /*/////creer deux plateau//*/
    printf("\n\n........preparation du plateau.....");
    plateau=init(n,haut);
    p=init(3*n,haut);
    clearPlateau(plateau,n,haut);  /*// mettre les poteau ‘.’ (vide)*/
    printf("\n Il va commencer!   \n  ");
    printf("\n i:↑ k:↓ j:← l:→ pour choisir la Colonne \n    ");


    afficheDessus(plateau,n,haut);
    printf("\n\n");
    printf("        'X' va commencer ~!        \n");
    /*///premier step*/
    position=choisirColonne(plateau,n,haut);
    ajouterX(plateau,haut,position[0],position[1]);
    /*/////premier seisme////*/
    faire_seisme(p,plateau,n,haut);
    /*///circule///*/
    while(PlateauEstPlein(plateau,n,haut)!=1) /*/si la plateau n'est pas plein.*/
        {
           if(OtourSeisme3D(p,plateau,n,haut))
                break;
           if(PlateauEstPlein(plateau,n,haut)==1)
                 break;
           if(XtourSeisme3D(p,plateau,n,haut))
                break;

        }
}

/*@require: rien
  @assigns: creer l'espace pour platrau etc dans la memoire
  @ensure : le processus du jeu (variante dessus seisme)
 */
void dessus_seisme()
{

    char*** plateau;
    char*** p;
    char taille[3];
    char *t = taille;
    char plafont[3];
    char *chaut=plafont;
    int *position;
    int haut=1;
    char** endptr=(char**)calloc(10,sizeof(char*));
    long int n;
    printf("\n*=========================================================*");
    printf("\n*===================La variante Dessus====================*");
    printf("\n*==========================seisme=========================*");
    printf("\n*Taper la taille(>2) du plateau et puis taper 'Enter'.SVP *");
    printf("\n* taille = ");
    /*/////taille de la plateau*/
    scanf("%s",t);
    clearStdin();
    n=strtol(t,endptr,10);
    while((!isnumber(t))||(n==1))
    {
        printf("Taper un chiffre > 1  \n");
        scanf("%s",t);
        clearStdin();
        n=strtol(t,endptr,10);
    }
    n=strtol(t,endptr,10);
    /*////plafont de la pile*/
    printf("\n*hauteur maximum de la pile = ");
    scanf("%s",chaut);
    clearStdin();
    while(!isnumber(chaut))
    {
        printf("Taper un chiffre\n");
        scanf("%s",chaut);
        while ((getchar()) != '\n');
    }
    haut=strtol(chaut,endptr,10);
    /*/////creer deux plateau//*/
    printf("\n\n........preparation du plateau.....");
    plateau=init(n,haut);
    p=init(3*n,haut);
    clearPlateau(plateau,n,haut);  /*// mettre les poteau ‘.’ (vide)*/
    printf("\n Il va commencer!   \n  ");
    printf("\n i:↑ k:↓ j:← l:→ pour choisir la Colonne \n    ");


    afficheDessus(plateau,n,haut);
    printf("\n\n");
    printf("        'X' va commencer ~!        \n");
    /*///premier step*/
    position=choisirColonne(plateau,n,haut);
    ajouterX(plateau,haut,position[0],position[1]);
    /*/////premier seisme////*/
    faire_seisme(p,plateau,n,haut);
    /*///circule///*/
    while(PlateauEstPlein(plateau,n,haut)!=1) /*/si la plateau n'est pas plein.*/
        {
           if(OtourSeisme(p,plateau,n,haut))
                break;
           if(PlateauEstPlein(plateau,n,haut)==1)
                 break;
           if(XtourSeisme(p,plateau,n,haut))
                break;

        }
}

