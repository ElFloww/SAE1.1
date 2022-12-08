// Florent Dubut, GROUPE E1

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Constantes:
#define NB_ALLUMETTES_MAX 30

//Variables:
string nom,prem;
char niv;
int nb_allumettes;

//DEBUT

void regles() // Cette procédure permet d'afficher les règles du jeu
{
    cout<<"+-------------------------------+\n|        Regles du jeu          |\n+-------------------------------+\n\nCe jeu se joue a deux. Les joueurs sont devant un certain nombre d'allumettes. A chaque tour, il faut en enlever 1, 2 ou 3. Celui qui prend la derniere allumette perd.\n";
}

void saisie(string* nom, char* niv, int* nb_allumettes, string* prem) // Cette procédure permet de faire la saisie des informations de la partie
{
    cout<<"\n+-------------------------------+\n|   Informations de la partie   |\n+-------------------------------+\n\n";
    int taille_nom;
    do
    {
        cout<<"Quel est votre nom ? (maximum de 20 caracteres) "; // Saisie du nom
        cin>>*nom;
        string nom2 = *nom;
        taille_nom = nom2.length();
    }   while ( taille_nom > 20);
    do
    {
        cout<<"Quel niveau de jeu voulez-vous jouer ? ('n' ou 'N' pour Naif ou 'e' ou 'E' pour expert) "; // Saisie du mode de difficulté
        cin>>*niv;
    }   while (*niv != 'n' && *niv != 'N' && *niv != 'e' && *niv != 'E'); 

    do
    {
        cout<<"Combien d'allumettes voulez-vous utiliser dans le jeu ? (Entre 0 et "<<NB_ALLUMETTES_MAX<<") ? "; // Saisie du nombre d'allumettes selon un intervalle
        cin>>*nb_allumettes;
    }   while (*nb_allumettes <= 0 || *nb_allumettes > NB_ALLUMETTES_MAX); 
    do
    {
        cout<<"Quel est le joueur qui commencera la partie ? ('"<<*nom<<"' pour le joueur ou 'ordi' pour l'ordinateur) : "; // Saisie du premier joueur qui commence
        cin>>*prem;
    }   while (*prem != *nom && *prem != "ordi");
    cout<<"\n+-------------------------------+\n|      Debut de la partie       |";
}

void affiche(int nb_allumettes) // Cette procédure permet de faire l'affichage du nombre d'allumettes restante
{   
    if (nb_allumettes != 0)
    {
        int i;
        cout<<"\n+-------------------------------+\n|    Il reste ";
        if (nb_allumettes < 10)
        {
            cout<<" "<<nb_allumettes;
        }
        else
        {
            cout<<nb_allumettes;
        }
        cout<<" allumettes     |\n+-------------------------------+\n";
        while (nb_allumettes != 0)
        {
            if (nb_allumettes >= 5)
            {
                cout<<"|     !    !    !    !    !     |\n";
                nb_allumettes -= 5;
            }
            else
            {
                cout<<"|     ";
                for (i=1;i<=5;i++)
                {
                    if (nb_allumettes > 0)
                    {
                        cout<<"!    ";
                        nb_allumettes -= 1;
                    }
                    else
                    {
                        cout<<"     ";
                    }
                }
                cout<<" |\n";
            }
        }
    cout<<"+-------------------------------+\n\n";
    }
}

void jeualterne(string *prem, string nom) // Cette procédure permet d'alterner de joueur
{
    if (*prem == "ordi")
    {
        *prem = nom;
    }
    else
    {
        *prem = "ordi";
    }
}

void miseAjour(int *nb_allumettes, int nb) // Cette procédure permet d'actualiser le nombre d'allumettes
{   
    *nb_allumettes -= nb;
}

int joueOrdi(char niv, int nb_allumettes) // Cette procédure permet de faire jouer l'ordinateur de manière aléatoire ou de manière stratégique
{   
    int generation_aleatoire();
    int nb;
    cout<<"+-------------------------------+\n|        Ordinateur joue        |";
    if (niv == 'n' || niv == 'N')
    {
        switch (nb_allumettes)
        {
        case 1:
            cout<<"\n| L'ordi a enleve 1 alumette(s) |";
            return 1;
        case 2:
            cout<<"\n| L'ordi a enleve 2 alumette(s) |";
            return 2;
        case 3:
            cout<<"\n| L'ordi a enleve 3 alumette(s) |";
            return 3;
        default:
            int nombre = generation_aleatoire();
            cout<<"\n| L'ordi a enleve "<<nombre<<" alumette(s) |";
            return nombre;
        }
    }
    else
    {   
        switch (nb_allumettes)
        {
        case 1:
            cout<<"\n| L'ordi a enleve 1 alumette(s) |";
            return 1;
        case 2:
            cout<<"\n| L'ordi a enleve 1 alumette(s) |";
            return 1;
        case 3:
            cout<<"\n| L'ordi a enleve 2 alumette(s) |";
            return 2;
        default:
            break;
        }
        nb = (nb_allumettes-1)%4;
        if (nb == 0)
        {
            int nombre = generation_aleatoire();
            cout<<"\n| L'ordi a enleve "<<nombre<<" alumette(s) |";
            return nombre;
        }
        else
        {
            cout<<"\n| L'ordi a enleve "<<nb<<" alumette(s) |";
            return nb;
        }
    }
}
int joueJoueur(string nom) // Cette fonction permet de faire fonctionner le joueur et de faire retourner un nombre entre 1 et 3, s'il saisie 0, il a la possibilité d'abandonner la partie
{
    int nb;
    cout<<"\n+-------------------------------+\n|";
    int taille_affich = nom.length() + 5;
    int taille_gauche, taille_droite,i;
    taille_gauche = (31-taille_affich) / 2;
    taille_droite = 31-taille_affich-taille_gauche;
    for (i=1;i<=taille_gauche;i++)
    {
        cout<<" ";
    }
    cout<<nom<<" joue";
    for (i=1;i<=taille_droite;i++)
    {
        cout<<" ";
    }
    cout<<"|";
    cout<<"\n+-------------------------------+\n";
    cout<<"\nCombien d'allumettes voulez-vous enlevez ? ";
    cin>>nb;
    while (nb<0 || nb > 3 || nb > nb_allumettes || nb == 0)
    {
        cout<<"\nerreur";
        if (nb == 0)
        {
            string confirmation;
            cout<<"\nConfirmer l'abandon ? 'oui' ou 'non' ";
            cin>>confirmation;
            if (confirmation == "oui")
            {
                return 0;
            }
        }
        cout<<"\nCombien d'allumettes voulez-vous enlevez ? ";
        cin>>nb;
    }
    return nb;    
}

int generation_aleatoire() //Cette fonction permet de générer des nombres aléatoires qui permet à l'ordinateur de jouer nativement ou lorsque aucun choix stratégique s'offre à lui
{
    int i = 0;
    int nombre_aleatoire = 0;
    srand(time(0));

    nombre_aleatoire = rand()%3 +1 ;
    return nombre_aleatoire;
}

int main() // Fonction principale qui fait tourner la partie
{   
    cout<<"+-------------------------------+\n|	Jeu des allumettes	|\n+-------------------------------+\n";
    int nb = 1,abandon;
    cout<<"\nBienvenue dans le jeu des allumettes !! \n\n";
    regles();
    saisie(&nom,&niv,&nb_allumettes,&prem);
    affiche(nb_allumettes);
    while (nb_allumettes > 0 && nb != 0) // Tant que la partie n'est pas fini
    {
        if (prem == nom)
        {
            nb = joueJoueur(nom);
        }
        else
        {
            nb = joueOrdi(niv,nb_allumettes);
        }
        miseAjour(&nb_allumettes,nb);
        affiche(nb_allumettes);
        jeualterne(&prem,nom);
    }
    jeualterne(&prem,nom);
    cout<<"\n+-------------------------------+\n|";
    int taille_affich = prem.length() + 10;
    int taille_gauche, taille_droite,i;
    taille_gauche = (31-taille_affich) / 2;
    taille_droite = 31-taille_affich-taille_gauche;
    for (i=1;i<=taille_gauche;i++)
    {
        cout<<" ";
    }
    cout<<prem<<" a perdu !";
    for (i=1;i<=taille_droite;i++)
    {
        cout<<" ";
    }
    cout<<"|";
    cout<<"\n+-------------------------------+\n\n";
    return 0;
}
//FIN