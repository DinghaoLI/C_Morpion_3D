#include "seisme.h"
#include "player.h"
#include "menu.h"

/*@require: h>0
  @assigns: rien
  @ensure : calculer la probabilité du seisme et il va retour le nombre de jeton qui a tombe.
 */
int seisme(int n,int h)
{
    double a,proba,ran;

    a=0.0-((double)h/(double)(2*n));
    proba=1.0-(double)pow(2,a);
    proba=proba*10000.0;
    ran=rand()%10001;
    if(ran<=proba)
        {
            int nb=(rand()%h)+1;
            return nb;
        }
    return 0;
}

/*@require: plateau pas NULL,haut>0,0<=line<n,o<=colonne<n
  @assigns: rien
  @ensure : obtenir la hauteur d'une pile.
 */
int geth(char*** plateau,int haut,int line,int colonne)
{
    int i;
    int h=-1;

    for(i=1;i<haut;i++)
        if((plateau[line][colonne][i]!='.')&&(plateau[line][colonne][i]!=' '))
            h=h+1;

    return h;
}
/*@require: p et plateau pas NULL,haut>0,n>1
  @assigns: modifier 'p' et 'plateau' selon la resultat du seisme
  @ensure : retourner rien
 */
void faire_seisme(char*** p,char*** plateau,int n,int haut)
{
    int x,y,z;
   /*///////clear////////*/
    for(x=0;x<3*n;x++)
        for(y=0;y<3*n;y++)
            for(z=0;z<haut;z++)
                p[x][y][z]=' ';
    /*////// copy ///////*/
    for(x=0;x<n;x++)
        for(y=0;y<n;y++)
            for(z=0;z<haut;z++)
                p[2*x+1][2*y+1][z]=plateau[x][y][z];
    /*////// seisme  /////*/
    int h;
    int down;
    int rest;
    for(x=0;x<n;x++)
        for(y=0;y<n;y++)
            {
                /*/////tomper////////*/
                h=1+geth(plateau,haut,x,y);
                down=seisme(n,h);
               /* printf("\n down:%d ",down); */ /*pour test*/
                if(down>0)
                {
                    rest=h-down;
                    for(rest=h-down;rest<haut;rest++)
                        p[2*x+1][2*y+1][rest]='.';
                    /*//////mettre etoile//////*/
                    p[2*x+1][2*y+0][0]='*';
                    p[2*x+2][2*y+0][0]='*';
                    p[2*x+2][2*y+1][0]='*';
                    p[2*x+2][2*y+2][0]='*';
                    p[2*x+1][2*y+2][0]='*';
                    p[2*x+0][2*y+2][0]='*';
                    p[2*x+0][2*y+1][0]='*';
                    p[2*x+0][2*y+0][0]='*';
                }
            }
    /*//////dupliquer a petit plateau encore////*/
     for(x=0;x<n;x++)
        for(y=0;y<n;y++)
            for(z=0;z<haut;z++)
                plateau[x][y][z]=p[2*x+1][2*y+1][z];

}

/*@require: n>2 haut>0 plateau pas NULL et p pas NULL
  @assigns: modifier le 'plateau' selon la resultat du seisme
  @ensure : l'affichage du seisme..
 */
void afficheChoisirSeisme(char*** p,char*** plateau,int n,int haut,int line_p,int colonne_p)
{
   /*system("clear");*/
   int x,y,z,i,toit;
   char show;
     /*///////clear ‘+’ ////////*/
    for(x=0;x<3*n;x++)
        for(y=0;y<3*n;y++)
            if(p[x][y][1]=='+')
                p[x][y][1]=' ';
    /*////// copy ////////*/
    for(x=0;x<n;x++)
        for(y=0;y<n;y++)
            for(z=0;z<haut;z++)
                p[2*x+1][2*y+1][z]=plateau[x][y][z];
   /*////mettre '+'/////*/
   p[line_p][colonne_p+1][1]='+';
   p[line_p][colonne_p-1][1]='+';
   p[line_p+1][colonne_p][1]='+';
   p[line_p-1][colonne_p][1]='+';
   for(x=0;x<3*n;x++)
   {
     printf("\n");
     for(y=0;y<3*n;y++)
            {

                show=p[x][y][0];
                if((p[x][y][0]=='*')&&(p[x][y][1]=='+'))
                    show='+';
                if((p[x][y][0]!='*')&&(p[x][y][1]=='+'))
                    show='+';
                if((p[x][y][0]=='.')||(p[x][y][0]=='X')||(p[x][y][0]=='O'))
                {
                    show='.';
                    for(toit=0;toit<haut;toit++)
                        if(p[x][y][toit]!='.')
                            show=p[x][y][toit];
                }


                printf(" %c ",show);
            }

    }

    printf("\n");
    printf("\t\tle pile basse->haut : ");
        for(i=haut-1;i>-1;i--)
        {   printf("\n");
            printf("\t\t\t\t         %c ",p[line_p][colonne_p][i]);
        }

    printf("\n- - - - - - - - - - - - - - - - - - - - - - -\n\n\n");

}


/*@require: la pointeur de la plateau et la taille n>2,haut > 0
  @assigns: creer pointeur: position[2] pour noter la position
  @ensure : retourner la position[2] que la utilisateur qui veut choisir
*/
int* choisirColonneSeisme(char*** p,char*** plateau,int n,int haut)
{

    int ch;
    int* position = (int*)calloc(2,sizeof(int));
    position[0]=0;
    position[1]=0;
    disable_terminal_return();

    printf(" \n choisir le tube pour modifier \n");
     printf("\n i:↑ k:↓ j:← l:→ pour deplacer le curseur et puis taper 'Enter' pour choisir \n    ");
    /* Key reading loop */
    while (1)
     {
        ch = getchar();
        if (ch== 'i' )
            {
                if(position[0]>0)
                    position[0]=position[0]-1;
            }
        else if (ch== 'k' )
            {
                if(position[0]<n-1)
                    position[0]=position[0]+1;
            }
        else if (ch== 'j' )
            {
                if(position[1]>0)
                    position[1]=position[1]-1;
            }
        else if (ch== 'l' )
            {
                if(position[1]<n-1)
                    position[1]=position[1]+1;
            }
        /*/system("clear");*/
        afficheChoisirSeisme(p,plateau,n,haut,2*position[0]+1,2*position[1]+1);
        if (ch == '\n')
        {
            printf("  choirsirColone:(%d,%d)   ",position[0],position[1]);
            restore_terminal_settings();
            return position;  /* utiliser button space pour choisir*/

        }
     }

    return 0;
}

/*//////DESSUS SEISME/////////*/

/*@require: n>2 haut>0 plateau pas NULL et p pas NULL
  @assigns: modifier le plateau selon le chio de joueur
  @ensure : si O gagne on retourne 1 sinon retourne 0
 */
int OtourSeisme(char*** p,char*** plateau,int n,int haut)
{
    faire_seisme(p,plateau,n,haut);
    int *position;
    char user[3];
    char *control=user;
    int res;
    printf("\n   O    tour !!! \n ");
    printf("\n        O tour:  p:ajouter    r:retirer   q:quitter  : ");
    scanf("%c",control);
    clearStdin();
    while((*control!='p')&&(*control!='r')&&(*control!='q'))
    {
        printf("Taper 'p' ou 'r' ou 'q'\n");
        scanf("%c",control);
        clearStdin();
    }
    if(*control=='p')
    {
        position=choisirColonneSeisme(p,plateau,n,haut);
        res=ajouterO(plateau,haut,position[0],position[1]);
        while(res==0)
            {
                position=choisirColonneSeisme(p,plateau,n,haut);
                res=ajouterO(plateau,haut,position[0],position[1]);
            }
    }
    else if(*control=='r')
    {
        if(PlateauEstVide(plateau,n,haut)==1)
        {
            printf("le plateau est vide, tu peut seulment ajouter");
            position=choisirColonneSeisme(p,plateau,n,haut);
            res=ajouterO(plateau,haut,position[0],position[1]);
        }
        else{
                position=choisirColonneSeisme(p,plateau,n,haut);
                res=tirer(plateau,haut,position[0],position[1]);
                while(res==0)
                    {
                        position=choisirColonneSeisme(p,plateau,n,haut);
                        res=tirer(plateau,haut,position[0],position[1]);
                    }
            }
    }
    else if(*control=='q')
        exit(1);

    if(Owin(plateau,n,haut,position[0],position[1])==1)
    {

       printf("\n !!!!!  O WIN  !!!!!   \n");
       return 1;
    }

    return 0;

}

/*@require: n>2 haut>0 plateau pas NULL et p pas NULL
  @assigns: modifier le plateau selon le chio de joueur
  @ensure : si X gagne on retourne 1 sinon retourne 0
 */
int XtourSeisme(char*** p,char*** plateau,int n,int haut)
{
    faire_seisme(p,plateau,n,haut);
    int *position;
    char user[3];
    char *control=user;
    int res;
    printf("\n   X    tour !!! \n ");
    printf("\n        X tour:  p:ajouter    r:retirer   q:quitter  : ");
    scanf("%c",control);
    clearStdin();
    while((*control!='p')&&(*control!='r')&&(*control!='q'))
    {
        printf("Taper 'p' ou 'r' ou 'q'\n");
        scanf("%c",control);
        clearStdin();
    }
    if(*control=='p')
    {
        position=choisirColonneSeisme(p,plateau,n,haut);
        res=ajouterX(plateau,haut,position[0],position[1]);
        while(res==0)
            {
                position=choisirColonneSeisme(p,plateau,n,haut);
                res=ajouterX(plateau,haut,position[0],position[1]);
            }
    }
    else if(*control=='r')
    {
        if(PlateauEstVide(plateau,n,haut)==1)
        {
            printf("le plateau est vide, tu peut seulment ajouter");
            position=choisirColonneSeisme(p,plateau,n,haut);
            res=ajouterX(plateau,haut,position[0],position[1]);
        }
        else{
                position=choisirColonneSeisme(p,plateau,n,haut);
                res=tirer(plateau,haut,position[0],position[1]);
                while(res==0)
                    {
                        position=choisirColonneSeisme(p,plateau,n,haut);
                        res=tirer(plateau,haut,position[0],position[1]);
                    }
            }
    }
    else if(*control=='q')
        exit(1);

    if(Xwin(plateau,n,haut,position[0],position[1])==1)
    {

       printf("\n !!!!!  X WIN  !!!!!   \n");
       return 1;
    }

    return 0;

}



/*////// 3D SEISME ////////*/
/*@require: n>2 haut>0 plateau pas NULL et p pas NULL
  @assigns: modifier le plateau selon le chio de joueur
  @ensure : si O gagne on retourne 1 sinon retourne 0
 */
int OtourSeisme3D(char*** p,char*** plateau,int n,int haut)
{
    faire_seisme(p,plateau,n,haut);
    int *position;
    char user[3];
    char *control=user;
    int res;
    printf("\n   O    tour !!! \n ");
    printf("\n        O tour:  p:ajouter    r:retirer   q:quitter  : ");
    scanf("%c",control);
    clearStdin();
    while((*control!='p')&&(*control!='r')&&(*control!='q'))
    {
        printf("Taper 'p' ou 'r' ou 'q'\n");
        scanf("%c",control);
        clearStdin();
    }
    if(*control=='p')
    {
        position=choisirColonneSeisme(p,plateau,n,haut);
        res=ajouterO(plateau,haut,position[0],position[1]);
        while(res==0)
            {
                position=choisirColonneSeisme(p,plateau,n,haut);
                res=ajouterO(plateau,haut,position[0],position[1]);
            }
    }
    else if(*control=='r')
    {
        if(PlateauEstVide(plateau,n,haut)==1)
        {
            printf("le plateau est vide, tu peut seulment ajouter");
            position=choisirColonneSeisme(p,plateau,n,haut);
            res=ajouterO(plateau,haut,position[0],position[1]);
        }
        else{
                position=choisirColonneSeisme(p,plateau,n,haut);
                res=tirer(plateau,haut,position[0],position[1]);
                while(res==0)
                    {
                        position=choisirColonneSeisme(p,plateau,n,haut);
                        res=tirer(plateau,haut,position[0],position[1]);
                    }
            }
    }
    else if(*control=='q')
        exit(1);

    if(Owin3D(plateau,n,haut,position[0],position[1])==1)
    {

       printf("\n !!!!!  O  WIN  !!!!!   \n");
       return 1;
    }

    return 0;

}
/*@require: n>2 haut>0 plateau pas NULL et p pas NULL
  @assigns: modifier le plateau selon le chio de joueur
  @ensure : si X gagne on retourne 1 sinon retourne 0
 */
int XtourSeisme3D(char*** p,char*** plateau,int n,int haut)
{
    faire_seisme(p,plateau,n,haut);
    int *position;
    char user[3];
    char *control=user;
    int res;
    printf("\n   X    tour !!! \n ");
    printf("\n        X tour:  p:ajouter    r:retirer   q:quitter  : ");
    scanf("%c",control);
    clearStdin();
    while((*control!='p')&&(*control!='r')&&(*control!='q'))
    {
        printf("Taper 'p' ou 'r' ou 'q'\n");
        scanf("%c",control);
        clearStdin();
    }
    if(*control=='p')
    {
        position=choisirColonneSeisme(p,plateau,n,haut);
        res=ajouterX(plateau,haut,position[0],position[1]);
        while(res==0)
            {
                position=choisirColonneSeisme(p,plateau,n,haut);
                res=ajouterX(plateau,haut,position[0],position[1]);
            }
    }
    else if(*control=='r')
    {
        if(PlateauEstVide(plateau,n,haut)==1)
        {
            printf("le plateau est vide, tu peut seulment ajouter");
            position=choisirColonneSeisme(p,plateau,n,haut);
            res=ajouterX(plateau,haut,position[0],position[1]);
        }
        else{
                position=choisirColonneSeisme(p,plateau,n,haut);
                res=tirer(plateau,haut,position[0],position[1]);
                while(res==0)
                    {
                        position=choisirColonneSeisme(p,plateau,n,haut);
                        res=tirer(plateau,haut,position[0],position[1]);
                    }
            }
    }
    else if(*control=='q')
        exit(1);
    if(Xwin3D(plateau,n,haut,position[0],position[1])==1)
    {

       printf("\n !!!!!  X WIN  !!!!!   \n");
       return 1;
    }

    return 0;

}



