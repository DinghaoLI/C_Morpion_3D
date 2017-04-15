#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

extern char*** init(int n,int haut);
extern void clearPlateau(char*** p,int n,int haut);
extern int isnumber(char* p);
extern void afficheDessus(char*** p,int n,int haut);
extern int* choisirColonne(char*** plateau,int n,int haut);
extern int PlateauEstPlein(char*** plateau,int n,int haut);
extern void afficheChoisir(char*** p,int n,int haut,int line,int colonne);
extern int PlateauEstVide(char*** plateau,int n,int haut);
extern int ajouterX(char*** plateau,int haut,int line,int colonne);
extern int ajouterO(char*** plateau,int haut,int line,int colonne);
extern int tirer(char*** plateau,int haut,int line,int colonne);
extern int Xwin(char*** plateau,int n,int haut,int line,int colonne);
extern int Xtour(char*** plateau,int n,int haut);
extern int Owin(char*** plateau,int n,int haut,int line,int colonne);
extern int Otour(char*** plateau,int n,int haut);
extern int getNiveau(char*** plateau,int haut,int line,int colonne);
extern char pileToit(char*** plateau,int haut,int line,int colone);
extern int Owin3D(char*** plateau,int n,int haut,int line,int colonne);
extern int Otour3D(char*** plateau,int n,int haut);
extern int Xwin3D(char*** plateau,int n,int haut,int line,int colonne);
extern int Xtour3D(char*** plateau,int n,int haut);

#endif /*/ PLAYER_H_INCLUDED*/
