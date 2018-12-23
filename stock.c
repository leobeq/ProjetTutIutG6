//
//  stock.c
//  
//
//  Created by Léo Béquin on 29/11/2018.
//

#include "stock.h"

/*Lecture du fichier flot et retourne l'adresse de type Client*/
Client lireClient(FILE *flot)
{
    Client c;
    fscanf(flot, "%s%s%*c", c.idClient, c.civi);
    fgets(c.nom, 21, flot);
    c.nom[strlen(c.nom)-1] = '\0';
    fgets(c.prenom, 21, flot);
    c.prenom[strlen(c.prenom)-1] = '\0';
    fscanf(flot,"%s%*c", c.codeP);
    fgets(c.ville, 31, flot);
    c.ville[strlen(c.ville)-1] = '\0';
    fgets(c.rue, 61, flot);
    c.rue[strlen(c.rue)-1] = '\0';
    return c;
}
Client saisieClient(void)
{
    Client c;
    printf("Veuillez saisir votre civilite: ");
    scanf("%s%*c", c.civi);
    printf("Veuillez saisir votre nom: ");
    fgets(c.nom, 21, stdin);
    c.nom[strlen(c.nom)-1] = '\0';
    printf("Veuillez saisir votre prénom: ");
    fgets(c.prenom, 21, stdin);
    c.prenom[strlen(c.prenom)-1] = '\0';
    printf("Veuillez saisir votre Code Postal: ");
    scanf("%s%*c", c.codeP);
    printf("Veuillez saisir votre ville: ");
    fgets(c.ville, 31, stdin);
    c.ville[strlen(c.ville)-1] = '\0';
    printf("Veuillez saisir votre rue: ");
    fgets(c.rue, 61, stdin);
    c.rue[strlen(c.rue)-1] = '\0';
    return c;
}
Article lireArticle (FILE *fe)
{
    Article a;
    fscanf(fe, "%s%*c", a.idArticle);
    fgets(a.denom, 31, fe);
    a.denom[strlen(a.denom)-1]='\0';
    fscanf(fe, "%f%d", &a.prixU, &a.qte);
    return a;
}

int chargementClient( Client *tCli[], int tmax)
{
    FILE *flot;
    Client c;
    int i = 0;
    
    flot = fopen("client.don", "r");
    if (flot == NULL)
        return -1;
    
    c= lireClient(flot);
    while(!feof(flot))
    {
        if (i == tmax)
        {
            fclose(flot);
            return -2;
        }
        tCli[i] = (Client*)malloc(sizeof(Client));
        if (tCli[i] == NULL)
        {
            fclose(flot);
            return -3;
        }
        *tCli[i]=c;
        i=i+1;
        c = lireClient(flot);
    }
    fclose(flot);
    return i;
}
int chargementArticle ( Article *tart[], int tmax)
{
    FILE *fe;
    Article a;
    int i = 0;
    
    fe = fopen("article.don", "r");
    if (fe == NULL)
        return -1;
    
    a= lireArticle(fe);
    while(!feof(fe))
    {
        if (i == tmax)
        {
            fclose(fe);
            return -2;
        }
        tart[i] = (Article*)malloc(sizeof(Article));
        if (tart[i] == NULL)
        {
            fclose(fe);
            return -3;
        }
        *tart[i]=a;
        i=i+1;
        a = lireArticle(fe);
    }
    fclose(fe);
    return i;
}

void affichClient(Client c)
{
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", c.idClient,c.civi, c.nom, c.prenom,c.codeP, c.ville, c.rue);
}
void affichArticle(Article a)
{
    printf("%s\n%s\n%.2f\n%d\n", a.idArticle,a.denom, a.prixU, a.qte);
}
void affichTabClient( Client *tCli[], int nb)
{
    int i;
    system("clear");
    printf("\n\n\n\t\t---Client---\n");
    for (i=0;i<nb;i++)
    {
        affichClient(*tCli[i]);
        printf("-------\n");
    }
}
void affichTabArticle( Article *tart[], int nb)
{
    int i;
    system("clear");
    printf("\n\n\n\t\t---Article---\n");
    for (i=0;i<nb;i++)
    {
        affichArticle(*tart[i]);
        printf("-------\n");
    }
}
/* TRI par dichotomie*/
void copier (Client *tCli[], int i, int j, Client *R[])
{
    int k=0;
    while (i<j)
    {
        R[k]=tCli[i];
        i=i+1;
        k=k+1;
    }
}
void fusion(Client *R[], int nb, Client *S[],int m, Client *T[] )
{
    int k=0,i=0,j=0;
    
    while(i<nb && j<m)
    {
        if (strcmp(R[i]->idClient,S[j]->idClient)<0)
        {
            T[k]=R[i];
            k=k+1;
            i=i+1;
        }
        else
        {
            T[k]=S[j];
            k=k+1;
            j=j+1;
        }
    }
    while (i<nb) {
        T[k]=R[i];
        k=k+1;
        i=i+1;
    }
    while (j<m) {
        T[k]=S[j];
        k=k+1;
        j=j+1;
    }
}
void triDicho(Client *tCli[], int nb)
{
    Client **R, **S;
    if (nb == 1)
        return;
    R=(Client**)malloc((nb/2)*sizeof(Client*));
    S=(Client**)malloc((nb-(nb/2))*sizeof(Client*));
    if (R == NULL || S == NULL)
        return;
    copier(tCli,0,nb/2,R);
    copier(tCli,nb/2,nb,S);
    triDicho(R,nb/2);
    triDicho(S,nb-nb/2);
    fusion(R,nb/2,S,nb-nb/2,tCli);
    free(R);
    free(S);
    affichTabClient(tCli, nb);
}
/*------- FIN TRI par dichotomie--------*/
int rechDicho(Client *tCli[], int nb, char idClient[], int *trouve)
{
    int inf=0, m, sup=nb-1;
    
    while (inf<=sup)
    {
        m=(inf+sup)/2;
        if(strcmp(idClient, tCli[m]->idClient)==0)
        {
            *trouve=1;
            return m;
        }
        if(strcmp(idClient, tCli[m]->idClient)<0)
            sup=m-1;
        else inf=m+1;
    }
    *trouve=0;
    return inf;
}
/* ---- Insertion d'un client ----*/
void decalerADroite(Client *tCli[], int i, int nb)
{
    int j;
    for(j=nb-1;j>=i;j--)
        *tCli[j+1]=*tCli[j];
}
int insererClient(Client *tCli[], int *nb, int tmax)
{
    int trouve, i;
    char idClient[4];
    printf("Veuillez saisir l'id client : ");
    scanf("%s%*c",idClient);
    
    i = rechDicho(tCli, *nb, idClient, &trouve);
    
    if(trouve == 1)
        return -4;
    if(*nb == tmax)
        return -2;
    tCli[i]=(Client*)malloc(sizeof(Client));
    if(tCli[i] == NULL)
        return-3;
    decalerADroite(tCli, i, *nb);
    *nb= *nb+1;
    strcpy(tCli[i]->idClient, idClient);
    *tCli[i]=saisieClient();
    return 1;
}

/* ---- FIN insertion Client ----*/
/* ---- Suppression d'un Client ----*/
void decalerAGauche(Client *tCli[], int i, int nb )
{
    int j;
    for(j=i;j<=nb-2;j++)
        *tCli[j]=*tCli[j+1];
}
int supprimerClient(Client *tCli[], int *nb, int tmax)
{
    int i, trouve;
    char idClient[4];
    printf("choisir l'id client': ");
    scanf("%s%*c", idClient);
    i = rechDicho(tCli, *nb, idClient, &trouve);
    if (trouve==0)
        return -5;
    decalerAGauche(tCli, i, *nb);
    *nb = *nb-1;
    return 1;
}

/* ---- FIN suppression d'un Client ----*/

void GestionErreur(int err)
{
    switch (err) {
        case -1:
            printf("Erreur Ouverture du fichier\n");
            break;
        case -2:
            printf("Erreur la table est pleine\n");
            break;
        case -3:
            printf("Erreur lors de l'allocation dynamique\n");
            break;
        case -4:
            printf("déjà existant\n");
            break;
        case -5:
            printf("non trouvé\n");
            break;
        default: printf("Erreur inconnue");
            break;
    }
}

int choixMenuClient (void)
{
    int choixC;
    system("clear");
    printf("\n\n\n\t\tGestion d'un Stock\n\n");
    printf("\t1 - Afficher le client\n");
    printf("\t2 - Afficher les clients triés\n");
    printf("\t3 - Inserer un Client\n");
    printf("\t4 - Supprimer un Client\n");
    printf("\t5 - Sauvegarder \n");
    printf("\t9 - Quitter\n");
    printf("\n\n");
    printf("Option choisie : ");
    scanf("%d%*c", &choixC);
    return choixC;
}
int choixMenuArticle (void)
{
    int choixA;
    system("clear");
    printf("\n\n\n\t\tGestion d'un Stock\n\n");
    printf("\t1 - Afficher les articles\n");
    printf("\t2 - Afficher les articles triés\n");
    printf("\t3 - Inserer un Article\n");
    printf("\t4 - Supprimer un Article\n");
    printf("\t5 - Sauvegarder \n");
    printf("\t9 - Quitter\n");
    printf("\n\n");
    printf("Option choisie : ");
    scanf("%d%*c", &choixA);
    return choixA;
}

int choixMenu (void)
{
    int choix;
    system("clear");
    printf("\n\n\n\t\tGestion d'un Stock\n\n");
    printf("\t1 - Gestion des Client\n");
    printf("\t2 - Gestion des Articles\n");
    printf("\t3 - Gestion des Commandes en cours\n");
    printf("\t9 - Quitter\n");
    printf("\n\n");
    printf("Option choisie : ");
    scanf("%d%*c", &choix);
    return choix;
}

void menuC (void)
{
    Client *tCli[100];
    int choixC,tmax=100, nb=0, c, res;
    
    nb=chargementClient(tCli,100);
    if (nb == -1 || nb == -2 || nb == -3)
        GestionErreur(nb);
    
    choixC = choixMenuClient();
    while (choixC !=9 ) {
        
        switch (choixC) {
            case 1:
                affichTabClient(tCli, nb);
                break;
            case 2:
                triDicho(tCli, nb);
                break;
            case 3:
                res=insererClient(tCli, &nb, 100);
                if(res==1)
                    printf("\n\ninsertion réussi\n");
                break;
            case 4:// ne fonctionne pas
                res=supprimerClient(tCli, &nb, 100);
                if(res==1)
                    printf("\n\nsuppression réussi\n");
                break;
            default:
                return;
        }
        printf("\nAppuyer sur entrer ...");
        c= getchar();
        choixC=choixMenuClient();
    }
}
void menuA (void)
{
    Article *tart[100];
    int choixA,tmax=100, nb=0, c, res;
    
    nb=chargementArticle(tart,100);
    if (nb == -1 || nb == -2 || nb == -3)
        GestionErreur(nb);
    
    choixA = choixMenuArticle();
    while (choixA !=9 ) {
        
        switch (choixA) {
            case 1:
                affichTabArticle(tart, nb);
                break;
            case 2:
               
                break;
            case 3:
               
                break;
            case 4:
                
                break;
            default:
                return;
        }
        printf("\nAppuyer sur entrer ...");
        c= getchar();
        choixA=choixMenuArticle();
    }
}

void menu (void)
{
    int choix, c;
    choix = choixMenu();
    while (choix !=9 ) {
        
        switch (choix) {
            case 1:
                menuC();
                break;
            case 2:
                menuA();
                break;
            case 3:
                //menuCommEnCours();
                break;
            default:
                break;
        }
        printf("\nAppuyer sur entrer ...");
        c= getchar();
        choix=choixMenu();
    }
}
