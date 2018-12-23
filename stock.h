//
//  stock.h
//  
//
//  Created by Léo Béquin on 29/11/2018.
//

#ifndef bibliotheque_h
#define bibliotheque_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#endif /* bibliotheque_h */

/*Structure de Client*/
typedef struct
{
    char idClient[5];
    char civi[3];
    char nom[20];
    char prenom[20];
    char codeP[6];
    char ville[30];
    char rue[60];
}Client;

/*structure de article*/
typedef struct
{
    char idArticle[5];
    char denom[30];
    float prixU;
    int qte;
}Article;

/*Structure de ligne Commande en Cours*/
typedef struct{
    char idCommande[10];
    char idArticle[5];
    char idClient[5];
    int qteNL;
}CommEnCours;

Client lireClient(FILE *flot);
Article lireArticle(FILE *fe);
Client saisieClient(void);
int chargementClient( Client *tCli[], int tmax);
int chargementArticle( Article *tart[], int tmax);
void affichClient( Client c);
void affichArticle( Article a);
void affichTabClient( Client *tCli[], int nb);
void affichTabArticle( Article *tart[], int nb);
void copier (Client *tCli[], int i, int j, Client *R[]);
void fusion(Client *R[], int nb, Client *S[],int m, Client *T[]);
void triDicho(Client *tCli[], int nb);
int rechDicho(Client *tCli[], int nb, char idClient[], int *trouve);
void decalerADroite(Client *tCli[], int i, int nb);
int insererClient(Client *tCli[], int *nb, int tmax);
void decalerAGauche(Client *tCli[], int i, int nb);
int supprimerClient(Client *tCli[], int *nb, int tmax);
void GestionErreur(int err);
int choixMenu (void);
int choixMenuClient (void);
int choixMenuArticle (void);
void menuC (void);
void menuA (void);
void menu (void);

