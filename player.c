#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "keyboard.h"
#include "menu.h"
/*@require: pointeur du type 'char' NOT NULL
  @assigns: rien
  @ensure : retour 1 si p contient seulement chiffre retour 0 sinon
*/
int isnumber(char* p)
{
    for ( ; *p ; p+=1 )
        if ( *p<'0' || '9'<*p )
            return 0;
    return 1;
    }


/*@require: Entier n pour la taille du plateau (n>0),et le plafond de la pile :haut >2
  @assigns: creer un espace pour plateau avec la taille n*n*n (type char)
  @ensure : retour la pointeur du plateau (taille n) type char***
*/
char*** init(int n,int haut)
{
    int i,j;
    char*** table=(char***)calloc(n,sizeof(char**));
    for(i=0;i<n;i++)
        table[i]=(char**)calloc(n,sizeof(char*));
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            table[i][j] =(char*)calloc(haut,sizeof(char));
    return table;
}


/*@require: pointeur de la plateau ,taille n>1 ,plafond haut > 0
  @assigns: rien
  @ensure : si la plateau est plein retourner 1, sinon retourner 0
 */
int PlateauEstPlein(char*** plateau,int n,int haut)
{
    int x,y,z;
    int count=0;
    for (x=0;x<n;x++)
        for(y=0;y<n;y++)
            for(z=0;z<haut;z++)
             {
                if(plateau[x][y][z]=='.')
                    count=count+1;
             }
    if(count==0)
        return 1;
    else
        return 0;
}

/*@require: la pointeur du plateau et la taille n>2 et le plafond de la pile:haut >1.
  @assigns: modifier la pointer du plateau avec tous les elements  'V'
  @ensure : laisser le plateau vide(represente par 'V')
*/
void clearPlateau(char*** p,int n,int haut)
{
    int x,y,z;
    for(x=0;x<n;x++)
        for(y=0;y<n;y++)
            for(z=0;z<haut;z++)
                p[x][y][z]='.';
}


/*@require: le pointeur du plateau, taille n>2,le plafond de la pile :haut>0
 @assigns: rien
  @ensure : retourner rien mais affiche le plateau dans variante <Dessus>
*/
void afficheDessus(char*** p,int n,int haut)
{
    int x,y,z;
    char show;
    for(x=0;x<n;x++)
    {
        printf("\n");
        printf("\n");
        for(y=0;y<n;y++)
        {
            show='.';
            for(z=0;z<haut;z++)
            {

                if(p[x][y][z]!='.')
                    show=p[x][y][z];
            }
            printf("  %c  ",show);
        }
    }

}



/*@require: la pointeur de la plateau et la taille n>2,haut > 0
  @assigns: creer pointeur: position[2] pour noter la position
  @ensure : retour la position[2] que la utilisateur qui veut choisir
*/
int* choisirColonne(char*** plateau,int n,int haut)
{

    int ch;
    int* position = (int*)calloc(2,sizeof(int));
    position[0]=0;
    position[1]=0;
    disable_terminal_return();

    printf("choisir la pile a modifier \n");
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
        afficheChoisir(plateau,n,haut,position[0],position[1]);
        if (ch == '\n')
        {
            printf("  choirsirColone:(%d,%d)   ",position[0],position[1]);
            restore_terminal_settings();
            return position;  /* utiliser button space pour choisir*/

        }
     }

    return 0;
}







/*@require:pointeur p NOT NULL,n>2,haut>1,line >=0, colonne >=0
  @assigns:rien
  @ensure :affiche le pile que tu a choisi avec '+'
*/
void afficheChoisir(char*** p,int n,int haut,int line,int colonne)
{
    int x,y,z;
    int i,j;
    char show;
    int star=0;
    if(line==0)
    {
        for(i=0;i<n;i++)
        {
            if(i==colonne)
                printf("  +  ");
            else
                printf("     ");
        }
    }

    for(x=0;x<n;x++)
    {
        if((star==1))
        {
            printf("\n");
            for(j=0;j<n;j++)
            {
                if((j==colonne))
                {
                    printf("  +  ");
                }
                else
                    printf("     ");
            }
            star=0;
        }
        else
            printf("\n");
        if(x>0)
            printf("\n");

        for(y=0;y<n;y++)
        {

            show='.';
            for(z=0;z<haut;z++)
            {

                if(p[x][y][z]!='.')
                    show=p[x][y][z];
            }

            if((x==line)&&(y==colonne))
            {
                printf(" +%c+ ",show);
                star=1;
            }
            else
                printf("  %c  ",show);

            if(x+1==line)
                star=1;
        }
    }
    printf("\n");
    if(line==n-1)
    {
        for(i=0;i<n;i++)
        {
            if(i==colonne)
                printf("  +  ");
            else
                printf("     ");
        }
    }
    printf("\n");
    printf("\t\tle pile basse->haut : ");
        for(i=haut-1;i>-1;i--)
        {   printf("\n");
            printf("\t\t\t\t         %c ",p[line][colonne][i]);
        }

    printf("\n- - - - - - - - - - - - - - - - - - - - - - -\n\n\n");

}



/*@require: pointeur de la plateau ,taille n>1 ,plafond haut > 0
  @assigns: rien
  @ensure : si la plateau est vide retourner 1, sinon retourner 0
 */
int PlateauEstVide(char*** plateau,int n,int haut)
{
    int x,y,z;
    int cnt=0;
    for (x=0;x<n;x++)
        for(y=0;y<n;y++)
            for(z=0;z<haut;z++)
             {
                if(plateau[x][y][z]!='.')
                    cnt=cnt+1;
             }
    if(cnt==0)
        return 1;
    else
        return 0;
}


/*@require: plateau pas NULL,n>2,haut>0,line>=0,colonne>=0
  @assigns: si la pile n'est pas plein, on ajoute un 'X' sur la pile par changer la valeur 'V'
  @ensure : si on l'ajoute retourner 1,sinon 0;
*/
int ajouterX(char*** plateau,int haut,int line,int colonne)
{
    int i=0;
    while((i<haut)&&(plateau[line][colonne][i]!='.'))
        i=i+1;
    if(i==haut)
        {
            printf("\n cette pile est pleine \n");
            return 0;
        }
    else
        {
            plateau[line][colonne][i]='X';
            printf(" tu as mis 'X' ici \n ");
            return 1;
        }
}


/*@require: plateau pas NULL,n>2,haut>0,line>=0,colonne>=0
  @assigns: si la pile n'est pas plein, on ajoute un 'O' sur la pile par changer la valeur 'V'
  @ensure : si on l'ajoute retourner 1,sinon 0;
*/
int ajouterO(char*** plateau,int haut,int line,int colonne)
{
    int i=0;
    while((i<haut)&&(plateau[line][colonne][i]!='.'))
        i=i+1;
    if(i==haut)
        {
            printf("\n cette pile est pleine \n");
            return 0;
        }
    else
        {
            plateau[line][colonne][i]='O';
            printf("tu as mis 'O' ici \n ");
            return 1;
        }
}


/*@require: plateau pas NULL,n>2,haut>0,line>=0,colonne>=0
  @assigns: si la pile n'est pas vide, on trier un pion sur la pile et  changer la valeur 'V'
  @ensure : si on l'tire retourner 1,sinon 0;
*/
int tirer(char*** plateau,int haut,int line,int colonne)
{
    int i=haut-1;
    while((i>=0)&&(plateau[line][colonne][i]=='.'))
        i=i-1;
    if(i<0)
        {
            printf("\n cette pile est vide \n");
            return 0;
        }
    else
        {
            plateau[line][colonne][i]='.';
            printf("  tu retires le jeton ici  \n");
            return 1;
        }

}
/*@require: plateau pas NULL,haut > 0,0<=line et colone <n
 @assigns: rien
  @ensure : retourner le toit de la pile.
*/
char pileToit(char*** plateau,int haut,int line,int colone)
{
    int i;
    char toit='.';
    for(i=0;i<haut;i++)
        if(plateau[line][colone][i]!='.')
            toit=plateau[line][colone][i];
    return toit;
}

/*//////dessus///////*/

/*@require: plateau pas NULL n>1 haut>0
  @assigns: rien
  @ensure : si X gagne on retourne 1 sinon retourne 0
 */
int Xwin(char*** plateau,int n,int haut,int line,int colonne)
{
    int i;
    int nb=0;
    /*//////line////*/

    for(i=0;i<n;i++)
        {
            if(pileToit(plateau,haut,line,i)=='X')
                nb=nb+1;

        }
    printf(" line %d",nb);
    if(nb==n)
        return 1;
    /*//////colone////*/
    nb=0;
    for(i=0;i<n;i++)
        {
            if(pileToit(plateau,haut,i,colonne)=='X')
                nb=nb+1;
        }
    if(nb==n)
        return 1;
    /*////diag/////*/
    nb=0;
    for(i=0;i<n;i++)
        {
            if(pileToit(plateau,haut,i,i)=='X')
                nb=nb+1;
        }
    if(nb==n)
        return 1;
    /*/////diag2////*/
    nb=0;
    for(i=0;i<n;i++)
        {
            if(pileToit(plateau,haut,n-1-i,i)=='X')
                nb=nb+1;
        }

    if(nb==n)
        return 1;
    return 0;
}

/*@require: n>2 haut>0 plateau pas NULL
  @assigns: modifier le plateau selon le chiox de joueur
  @ensure : si X gagne on retourne 1 sinon retourne 0
 */
int Xtour(char*** plateau,int n,int haut)
{
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
        position=choisirColonne(plateau,n,haut);
        res=ajouterX(plateau,haut,position[0],position[1]);
        while(res==0)
            {
                position=choisirColonne(plateau,n,haut);
                res=ajouterX(plateau,haut,position[0],position[1]);
            }
    }
    else if(*control=='r')
    {
        if(PlateauEstVide(plateau,n,haut)==1)
        {
            printf("le plateau est vide, tu peut seulment ajouter");
            position=choisirColonne(plateau,n,haut);
            res=ajouterX(plateau,haut,position[0],position[1]);
        }
        else{
                position=choisirColonne(plateau,n,haut);
                res=tirer(plateau,haut,position[0],position[1]);
                while(res==0)
                    {
                        position=choisirColonne(plateau,n,haut);
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

/*@require: plateau pas NULL n>1 haut>0
  @assigns: rien
  @ensure : si O gagne on retourne 1 sinon retourne 0
 */
int Owin(char*** plateau,int n,int haut,int line,int colonne)
{
    int i;
    int nb=0;
    /*//////line////*/

    for(i=0;i<n;i++)
        {
            if(pileToit(plateau,haut,line,i)=='O')
                nb=nb+1;

        }
    if(nb==n)
        return 1;
    /*//////colone////*/
    nb=0;
    for(i=0;i<n;i++)
        {
            if(pileToit(plateau,haut,i,colonne)=='O')
                nb=nb+1;
        }
    if(nb==n)
        return 1;
    /*////diag/////*/
    nb=0;
    for(i=0;i<n;i++)
        {
            if(pileToit(plateau,haut,i,i)=='O')
                nb=nb+1;
        }
    if(nb==n)
        return 1;
    /*/////diag2////*/
    nb=0;
    for(i=0;i<n;i++)
        {
            if(pileToit(plateau,haut,n-1-i,i)=='O')
                nb=nb+1;
        }
    if(nb==n)
        return 1;
    return 0;
}

/*@require: n>2 haut>0 plateau pas NULL
  @assigns: modifier le plateau selon le chiox de joueur
  @ensure : si O gagne on retourne 1 sinon retourne 0
 */
int Otour(char*** plateau,int n,int haut)
{
    int *position;
    char user[3];
    char *control=user;
    int res;
    printf("\n   O    tour !!! \n ");
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
        position=choisirColonne(plateau,n,haut);
        res=ajouterO(plateau,haut,position[0],position[1]);
        while(res==0)
            {
                position=choisirColonne(plateau,n,haut);
                res=ajouterO(plateau,haut,position[0],position[1]);
            }
    }
    else if(*control=='r')
    {
        if(PlateauEstVide(plateau,n,haut)==1)
        {
            printf("le plateau est vide, tu peut seulment ajouter");
            position=choisirColonne(plateau,n,haut);
            res=ajouterO(plateau,haut,position[0],position[1]);
        }
        else{
                position=choisirColonne(plateau,n,haut);
                res=tirer(plateau,haut,position[0],position[1]);
                while(res==0)
                    {
                        position=choisirColonne(plateau,n,haut);
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


/*/////3D/////*/

/*@require: n>2 haut>0 plateau pas NULL
  @assigns: rien
  @ensure : retourner le niveau de la pile
 */
int getNiveau(char*** plateau,int haut,int line,int colonne)
{
    int i;
    int niveau=0;
    for(i=1;i<haut;i++)
        if(plateau[line][colonne][i]!='.')
            niveau=niveau+1;

    return niveau;
}
/*@require: plateau pas NULL n>1 haut>0
  @assigns: rien
  @ensure : si O gagne on retourne 1 sinon retourne 0
 */
int Owin3D(char*** plateau,int n,int haut,int line,int colonne)
{
    int i;
    int nb=0;
    int niveau=getNiveau(plateau,haut,line,colonne);
    printf("\n niveau:%d \n",niveau);
    /*////////sur la meme niveau///////*/
    /*///line//*/
    for(i=0;i<n;i++)
        if(plateau[line][i][niveau]=='O')
            nb=nb+1;
    if(nb==n)
      return 1;

    /*///colonne///*/
    nb=0;
    for(i=0;i<n;i++)
        if(plateau[i][colonne][niveau]=='O')
            nb=nb+1;
    if(nb==n)
        return 1;
    /*///diag////*/
    nb=0;
    for(i=0;i<n;i++)
        if(plateau[i][i][niveau]=='O')
            nb=nb+1;
    if(nb==n)
        return 1;
    /*///diag2///*/
    nb=0;
    for(i=0;i<n;i++)
        if(plateau[n-1-i][i][niveau]=='O')
            nb=nb+1;
    if(nb==n)
        return 1;
    /*///////////////sur colonne(fixe) //////////*/
    /*///// montrer ////*/
    nb=0;
    int l=line;
    int c=colonne;
    int niv=niveau;
    while((l<n)&&(niv<haut))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        l=l+1;
        niv=niv+1;
    }
    l=line-1;
    c=colonne;
    niv=niveau-1;
    while((l>=0)&&(niv>=0))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        l=l-1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
    /*///// descendre /////*/
      nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((l>=0)&&(niv<haut))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        l=l-1;
        niv=niv+1;
    }
    l=line+1;
    c=colonne;
    niv=niveau-1;
    while((l<n)&&(niv>=0))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        l=l+1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
    /*////////////////sur line(fixe) //////////*/
    /*/////////montrer////////*/
    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((c>=0)&&(niv>=0))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        c=c-1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
     /*////////////////sur diagonale 3D(fixe) //////////*/
    /*/////////1-montrer////////*/
    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((c<n)&&(niv<haut)&&(l<n))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        c=c+1;
        l=l+1;
        niv=niv+1;
    }
    l=line-1;
    c=colonne-1;
    niv=niveau-1;
    while((c>=0)&&(niv>=0)&&(l>=0))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        c=c-1;
        l=l-1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
    /*/////1-descendre /////*/
    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((c<n)&&(niv>=0)&&(l<n))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        c=c+1;
        l=l+1;
        niv=niv-1;
    }
    l=line-1;
    c=colonne-1;
    niv=niveau+1;
    while((c>=0)&&(niv<haut)&&(l>=0))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        c=c-1;
        l=l-1;
        niv=niv+1;
    }
    if(nb==n)
        return 1;
    /*/////////2-montrer////////*/
    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((c>=0)&&(niv<haut)&&(l<n))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        c=c-1;
        l=l+1;
        niv=niv+1;
    }
    l=line-1;
    c=colonne+1;
    niv=niveau-1;
    while((c<n)&&(niv>=0)&&(l>=0))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        c=c+1;
        l=l-1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
    /*/////2-descendre /////*/
    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((c>=0)&&(niv>=0)&&(l<n))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        c=c-1;
        l=l+1;
        niv=niv-1;
    }
    l=line-1;
    c=colonne+1;
    niv=niveau+1;
    while((c<n)&&(niv<haut)&&(l>=0))
    {
        if(plateau[l][c][niv]=='O')
            nb=nb+1;
        c=c+1;
        l=l-1;
        niv=niv+1;
    }
    if(nb==n)
        return 1;
    /*//////////////sur la pile/////////////////*/

    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((niv<haut)&&(niv<=(niveau+(n-1)/2)))
    {
        if(plateau[c][l][niv]=='O')
            nb=nb+1;
        niv=niv+1;
    }
    l=line;
    c=colonne;
    niv=niveau-1;
    while((niv>=0)&&(plateau[l][c][niv]=='O'))
    {
        if(plateau[c][l][niv]=='O')
            nb=nb+1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
    /*/////personne gagne////*/

    return 0;

}

/*@require: n>2 haut>0 plateau pas NULL
  @assigns: modifier le plateau selon le chiox de joueur
  @ensure : si O gagne on retourne 1 sinon retourne 0
 */
int Otour3D(char*** plateau,int n,int haut)
{
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
        position=choisirColonne(plateau,n,haut);
        res=ajouterO(plateau,haut,position[0],position[1]);
        while(res==0)
            {
                position=choisirColonne(plateau,n,haut);
                res=ajouterO(plateau,haut,position[0],position[1]);
            }
    }
    else if(*control=='r')
    {
        if(PlateauEstVide(plateau,n,haut)==1)
        {
            printf("le plateau est vide, tu peut seulment ajouter");
            position=choisirColonne(plateau,n,haut);
            res=ajouterO(plateau,haut,position[0],position[1]);
        }
        else{
                position=choisirColonne(plateau,n,haut);
                res=tirer(plateau,haut,position[0],position[1]);
                while(res==0)
                    {
                        position=choisirColonne(plateau,n,haut);
                        res=tirer(plateau,haut,position[0],position[1]);
                    }
            }
    }
    else if(*control=='q')
        exit(1);

    if(Owin3D(plateau,n,haut,position[0],position[1])==1)
    {

       printf("\n !!!!!  O WIN  !!!!!   \n");
       return 1;
    }
    return 0;

}

/*@require: plateau pas NULL n>1 haut>0
  @assigns: rien
  @ensure : si X gagne on retourne 1 sinon retourne 0
 */
int Xwin3D(char*** plateau,int n,int haut,int line,int colonne)
{
    int i;
    int nb=0;
    int niveau=getNiveau(plateau,haut,line,colonne);
    printf("\n niveau:%d \n",niveau);
    /*////////sur la meme niveau///////*/
    /*///line//*/
    for(i=0;i<n;i++)
        if(plateau[line][i][niveau]=='X')
            nb=nb+1;
    if(nb==n)
      return 1;

    /*///colonne///*/
    nb=0;
    for(i=0;i<n;i++)
        if(plateau[i][colonne][niveau]=='X')
            nb=nb+1;
    if(nb==n)
        return 1;
    /*///diag////*/
    nb=0;
    for(i=0;i<n;i++)
        if(plateau[i][i][niveau]=='X')
            nb=nb+1;
    if(nb==n)
        return 1;
    /*///diag2///*/
    nb=0;
    for(i=0;i<n;i++)
        if(plateau[n-1-i][i][niveau]=='X')
            nb=nb+1;
    if(nb==n)
        return 1;
    /*///////////////sur colonne(fixe) //////////*/
    /*///// montrer ////*/
    nb=0;
    int l=line;
    int c=colonne;
    int niv=niveau;
    while((l<n)&&(niv<haut))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        l=l+1;
        niv=niv+1;
    }
    l=line-1;
    c=colonne;
    niv=niveau-1;
    while((l>=0)&&(niv>=0))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        l=l-1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
    /*///// descendre /////*/
      nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((l>=0)&&(niv<haut))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        l=l-1;
        niv=niv+1;
    }
    l=line+1;
    c=colonne;
    niv=niveau-1;
    while((l<n)&&(niv>=0))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        l=l+1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
    /*////////////////sur line(fixe) //////////*/
    /*/////////montrer////////*/
    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((c<n)&&(niv<haut))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c+1;
        niv=niv+1;
    }
    l=line;
    c=colonne-1;
    niv=niveau-1;
    while((c>=0)&&(niv>=0))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c-1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
    /*///// descendre /////*/
    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((c>=0)&&(niv<haut))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c-1;
        niv=niv+1;
    }
    l=line;
    c=colonne+1;
    niv=niveau-1;
    while((c<n)&&(niv>=0))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c+1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;

     /*////////////////sur diagonale 3D(fixe) //////////*/
    /*/////////1-montrer////////*/
    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((c<n)&&(niv<haut)&&(l<n))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c+1;
        l=l+1;
        niv=niv+1;
    }
    l=line-1;
    c=colonne-1;
    niv=niveau-1;
    while((c>=0)&&(niv>=0)&&(l>=0))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c-1;
        l=l-1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
    /*/////1-descendre /////*/
    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((c<n)&&(niv>=0)&&(l<n))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c+1;
        l=l+1;
        niv=niv-1;
    }
    l=line-1;
    c=colonne-1;
    niv=niveau+1;
    while((c>=0)&&(niv<haut)&&(l>=0))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c-1;
        l=l-1;
        niv=niv+1;
    }
    if(nb==n)
        return 1;
    /*/////////2-montrer////////*/
    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((c>=0)&&(niv<haut)&&(l<n))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c-1;
        l=l+1;
        niv=niv+1;
    }
    l=line-1;
    c=colonne+1;
    niv=niveau-1;
    while((c<n)&&(niv>=0)&&(l>=0))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c+1;
        l=l-1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
    /*/////2-descendre /////*/
    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((c>=0)&&(niv>=0)&&(l<n))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c-1;
        l=l+1;
        niv=niv-1;
    }
    l=line-1;
    c=colonne+1;
    niv=niveau+1;
    while((c<n)&&(niv<haut)&&(l>=0))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        c=c+1;
        l=l-1;
        niv=niv+1;
    }
    if(nb==n)
        return 1;
    /*//////////////sur la pile/////////////////*/

    nb=0;
    l=line;
    c=colonne;
    niv=niveau;
    while((niv>=0)&&(plateau[l][c][niv]=='X'))
    {
        if(plateau[l][c][niv]=='X')
            nb=nb+1;
        niv=niv-1;
    }
    if(nb==n)
        return 1;
    /*/////personne gagne////*/
    return 0;
}

/*@require: n>2 haut>0 plateau pas NULL
  @assigns: modifier le plateau selon le chiox de joueur
  @ensure : si X gagne on retourne 1 sinon retourne 0
 */
int Xtour3D(char*** plateau,int n,int haut)
{
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
        position=choisirColonne(plateau,n,haut);
        res=ajouterX(plateau,haut,position[0],position[1]);
        while(res==0)
            {
                position=choisirColonne(plateau,n,haut);
                res=ajouterX(plateau,haut,position[0],position[1]);
            }
    }
    else if(*control=='r')
    {
        if(PlateauEstVide(plateau,n,haut)==1)
        {
            printf("le plateau est vide, tu peut seulment ajouter");
            position=choisirColonne(plateau,n,haut);
            res=ajouterX(plateau,haut,position[0],position[1]);
        }
        else{
                position=choisirColonne(plateau,n,haut);
                res=tirer(plateau,haut,position[0],position[1]);
                while(res==0)
                    {
                        position=choisirColonne(plateau,n,haut);
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
