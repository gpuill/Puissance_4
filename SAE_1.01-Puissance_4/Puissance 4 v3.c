/*
Programm made by Guillaume PUILL
Feel free to use it or ask me questions if you have some.
Documentation = French
This a game of Connect 4, you have to be two players in order to play

Enjoy :)
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/**
 * @def NBLIG 
 * @brief La taille verticale de la grille
 */
#define NBLIG 6
/**
 * @def NBCOL
 * @brief La taille Horizontale
 * 
 */
#define NBCOL 7
/**
 * @def Pion_A
 * @brief 
 * 
 */
const char PION_A ='X';
const char PION_B = 'O';
const char VIDE = ' ';
const char INCONNU = ' ';
const int COLONNE_DEBUT = NBCOL/2;
typedef char tab [NBLIG][NBCOL];
typedef char nom[20];
void nomJoueur (nom nomDuJoueurA, nom nomDuJoueurB);
void initgrille(tab grille);
void afficher(tab grille, char pion, int colonne);
bool grillePleine(tab grille);
void jouer(tab grille, char pion, int *ligne, int *colonne);
int choisirColonne(tab grille, char pion, int colonne);
int trouverLigne(tab grille, int colonne);
bool estVainqueur(tab grille, int ligne, int colonne);
void finDePartie(char pion, nom nomJoueur, tab grille);

int main(){
    nom nomJA, nomJB, nomJ;
    char vainqueur;
    int ligne, colonne;
    tab grille;
    ligne=0;
    colonne=0;
    vainqueur=INCONNU;
    nomJoueur(nomJA, nomJB);
    initgrille(grille);
    afficher(grille, PION_A, COLONNE_DEBUT);
    while ((vainqueur==INCONNU)&&(grillePleine(grille)==false))
    {
        jouer(grille, PION_A, &ligne, &colonne);
        afficher(grille, PION_B, COLONNE_DEBUT);
        if (estVainqueur(grille, ligne, colonne)==true)
        {
           vainqueur=PION_A;
           strcpy(nomJ,nomJA);
           

        }else if (grillePleine(grille)==false)
        {
            jouer(grille, PION_B, &ligne, &colonne);
            afficher(grille, PION_A, COLONNE_DEBUT);
            if (estVainqueur(grille, ligne, colonne)==true)
            {
                vainqueur=PION_B;
                strcpy(nomJ,nomJB);
            }
        }
    }
    finDePartie(vainqueur, nomJ, grille);
    return EXIT_SUCCESS;
}


/**
 *
 * @fn void nomJoueur(nom nomDuJoueurA, nom nomDuJoueurB)
 * 
 * @brief Fonction qui affecte le nom des Joueurs A et B a des variables.
 * 
 * @param nomDuJoueurA Chaine de caractère qui définie le nom du Joueur A (Entrée/Sortie)
 * @param nomDuJoueurB Chaine de caractère qui définie le nom du Joueur B (Entrée/Sortie)
 * 
 * Prend les variables qui lui sont assignés et demande aux joueurs de rentrer leur noms, ces noms sont alors assignés aux variables.
 *
 */

void nomJoueur(nom nomDuJoueurA, nom nomDuJoueurB){
    system("clear");
    printf("Joueur A quel est votre nom ?\n");
    scanf("%s",nomDuJoueurA);
    system("clear");
    printf("Joueur B quel est votre nom ?\n");
    scanf("%s",nomDuJoueurB);
    system("clear");    
}

/**
 * @fn void initgrille(tab grille)
 * 
 * @brief affecte une valeur par défauts au tableau de type tab qui lui est fournit
 * 
 * @param grille tableau qui va être initialisé (Entrée/Sortie)
 * La valeur par défauts est la constante VIDE(=" ").
 */

void initgrille(tab grille){
    int i,j;
    for ( i = 0; i < NBLIG; i++)
    {
        for (j = 0; j < NBCOL; j++)
        {
            grille[i][j]=VIDE;
        }
    }
}

/*affichage terminer*/
/**
 * @fn void afficher(tab grille, char pion, int colonne)
 * 
 * @brief Affiche la grille de jeu avec le pion du joueur au dessus de la colonne souhaité
 * 
 * @param grille la Grille de jeu qui contient les pions (Entrée/Sortie)
 * @param pion c'est le pion correspondant au Joueur qui joue (Entrée)
 * @param colonne Valeur de la colonne au dessus de laquelle le pion doit être affiché (Entrée)
 * 
 */
void afficher(tab grille, char pion, int colonne){
    int i, ilig, icol;
    char pionColonne[7]="       ";
    pionColonne[colonne] = pion;
    system("clear");
    for (i = 0; i < NBCOL; i++)
    {
        printf("    %c   ",pionColonne[i]);// Première ligne
    }
    printf("\n");
    for ( ilig = 0; ilig < NBLIG; ilig++)
    {
        printf("+ - - - + - - - + - - - + - - - + - - - + - - - + - - - +\n");
        for ( icol = 0; icol < NBCOL; icol++)
        {
            printf("|   %c   ",grille[ilig][icol]);
        }
        printf("|\n");
    }   
    printf("+ - - - + - - - + - - - + - - - + - - - + - - - + - - - +\n");

}


/**
 * @fn bool grillePleine(tab grille)
 * 
 * @brief Vérifie si la ligne la plus haute du tableau contient encore des valeurs "VIDE"(constante).
 * 
 * @param grille La grille de jeu (Entrée)
 * @return true Lorsqu'il ne reste plus de valeurs vide.
 * @return false Lorsqu'il reste encore des valeurs vide.
 * 
 * 
 */
bool grillePleine(tab grille){
    int i;
    bool res;
    i=0;
    res=true;
    while ((i<NBCOL)&&(res==true))
    {
        if (grille[0][i]==VIDE)
        {
            res=false;
        }
        else 
        {
            i++;
        }
    }
    return res;
}

/*Faits*/
/**
 * @fn void jouer(tab grille, char pion, int *ligne,int *colonne)
 * 
 * @brief Fonction qui sert a modifié la grille de jeu, donc jouer
 * 
 * @param grille la grille de jeu qui sera modifié dans la fonction (Entrée/Sortie)
 * @param pion Pion du Joueur qui doit jouer (Entrée)
 * @param ligne Ligne a laquelle le pion viens se placer
 * @param colonne colonne dans laquelle le pion viens se placer
 * 
 */
void jouer(tab grille, char pion, int *ligne,int *colonne){
    *colonne=choisirColonne(grille,pion,*colonne);
    *ligne=trouverLigne(grille,*colonne);
    while(*ligne==-1)
    {
        *colonne=choisirColonne(grille,pion,*colonne);
        *ligne=trouverLigne(grille,*colonne);
    }
    grille[*ligne][*colonne]=pion;
}

/*Faits */
/**
 * @fn int choisirColonne(tab grille, char pion, int colonne)
 * @brief Fonction qui permet au Joueur de choisir la colonne dans laquelle il souhaite mettre son pion.
 * 
 * @param grille la grille de jeu (Entrée)
 * @param pion Pion du joueur qui joue sur ce tour (Entrée)
 * @param colonne Valeur d'une colonne, sers uniquement de point de départ pour le choix du Joueur(Entrée)
 * @return int La valeur de la colonne choisi par le Joueur
 */
int choisirColonne(tab grille, char pion, int colonne){
    const char GAUCHE = 'q';
    const char DROITE = 'd';
    const char VALIDE = ' ';
    int valcolonne;
    char input;
    valcolonne = colonne;
    afficher(grille, pion, valcolonne);
    scanf("%c",&input);
    while (input!=VALIDE)
    {
        if ((input==GAUCHE)&&(valcolonne>0))
        {
            valcolonne--;
            afficher(grille, pion, valcolonne);
        } 
        else if ((input==DROITE)&&(valcolonne<6))
        {
            valcolonne++;
            afficher(grille, pion, valcolonne);
        }
        scanf("%c",&input);
    }
    return valcolonne;
}

/*faits*/
/**
 * @fn int trouverLigne(tab grille, int colonne)
 * @brief Fonction qui trouve la ligne vide la plus basse dans une colonne.
 * 
 * @param grille la Grille de jeu
 * @param colonne Valeurs de la colonne dans laquelle le pion doit être placé
 * @return int La valeur de la ligne vide la plus basse dans la colonne choisi au préalable. 
 * Si la colonne choisi est pleine alors la fonction retourne -1.
 */
int trouverLigne(tab grille, int colonne){
    int i;
    bool arret;
    i=0;
    arret = false;
    while ((i<NBLIG)&&(arret==false))
    {
        if (grille[i][colonne]!=VIDE)
        {
            arret=true;
        }else
        {
            i++;
        }  
    }
    return i-1;
}

/*Faits*/
/**
 * @fn bool estVainqueur(tab grille, int ligne, int colonne)
 * @brief Cette fonction permet de vérifier si le dernier pion posé fait gagner le Joueur.
 * 
 * @param grille la Grille de jeu qui doit être vérifiée.
 * @param ligne La ligne a laquelle se trouve le dernier pion jouer.
 * @param colonne la colonne a laquelle se trouve le dernier pion jouer.
 * @return true lorsque le pion est dans un alignement avec 3 autres pion du meme Joueur.
 * @return false lorsque les conditions de victoire ne sont pas remplies.
 * Cette fonction contient une vérification horizontale, verticale, diagonales (Nord-Ouest vers Sud-Est, ET , Nord-Est vers Sud-Ouest), si aucune de ces vérifications n'est vrai alors la fonction renvoie false sinon elle renvoie true.
 */
bool estVainqueur(tab grille, int ligne, int colonne){
    bool rsl;
    int i,compteurHorizon;
    char jetonType;
    jetonType=grille[ligne][colonne];
    rsl = false;
    if (rsl==false)//Vérification horizontal
    {
        compteurHorizon=0;
        i=0;
        while ((i<NBCOL)&&(rsl==false))
        {
            if (grille[ligne][i]==jetonType)
            {
                compteurHorizon++;
            }else
            {
                compteurHorizon=0;
            }
            if (compteurHorizon==4)
            {
                rsl=true;
            }
            i++;
        }
    }
    if (rsl==false)//vérification vertical
    {
        i=ligne;
        rsl=true;
        while ((i<ligne+4)&&(rsl==true))// On initialise un compteur(i) 
        {
            if (grille[i][colonne]==jetonType)
            {
                i++;
            }
            else
            {
                rsl=false;
            }   
        }
    }
    if (rsl==false)//vérification diagonales partant de la droit vers la gauche, puis si il n'y a toujours pas de vainqueur de la gauche vers la droite.
    {
        int j, k,compteurDiag;//j=vertical,k=horizontal
        j=ligne;
        k=colonne;
        compteurDiag=0;
        while ((j>0)&&(k<NBCOL))// on amene les valeurs en haut a droite du tableau j tent vers 0 et k tent vers 6
        {
            j--;
            k++;
        }
        while ((j<NBLIG)&&(k>=0))
        {
            if (grille[j][k]==jetonType)
            {
                compteurDiag++;
            }else
            {
                compteurDiag=0;
            }
            if (compteurDiag==4)
            {
                rsl=true;
            }
            j++;
            k--;
        }
        if (rsl==false)//vérification diagonales partant de la gauche vers la droite.
        {
            //j=vertical,k=horizontal
            j=ligne;
            k=colonne;
            compteurDiag=0;
            while ((j>0)&&(k>0))// on amene les valeurs en haut a droite du tableau j tent vers 0 et k tent vers 6
            {
                j--;
                k--;
            }
            while ((j<NBLIG)&&(k<NBCOL))
            {
                if (grille[j][k]==jetonType)
                {
                    compteurDiag++;
                }else
                {
                    compteurDiag=0;
                }
                if (compteurDiag==4)
                {
                    rsl=true;
                }
                j++;
                k++;
            }
        }
    }
    return rsl;

}

/*faits*/
/**
 * @fn void finDePartie(char pion, nom nomJoueur, tab grille)
 * 
 * @brief Affiche la victoire d'un joueur ou alors l'égalité.
 * 
 * @param pion : Pion du Joueur Vainqueur
 * @param nomJoueur : le nom du Joueur vainqueur
 * @param grille : la grille de jeu qui sera affiché
 * 
 * Si pion est égal a un pion de joueur c'est une victoire d'un des Joueurs, sinon si pion égal a la valeur VIDE c'est une égalité.
 */
void finDePartie(char pion, nom nomJoueur, tab grille){
    system("clear");
    afficher(grille, VIDE, COLONNE_DEBUT);
    if (pion==VIDE)
    {
        printf("Match nul aucun Joueur n'a gagné !\n");
    }else 
    {
        printf("[%c]Bravo %s gagne !\n",pion, nomJoueur);
    }
}
