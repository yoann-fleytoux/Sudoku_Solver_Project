#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include "Niveau1sudoku.h"

typedef struct
{
  	int val;
  	int n_candidats;
	int candidats[9];
}T_case;

typedef struct
{	
	T_case grille[81];
}T_sudoku;

int main ()
{
	T_sudoku p;
	int cpt=0;
	int d=0;
	int o;
	bool veri;
	initialise(p);/*met la grille et les candidats a zero*/
	saisie(p);/*permet d'entrer une grille de depart*/
	affiche(p);/*affiche la grille des candidats s'il n'y a pas de valeur a cette case sinon affiche la valeur*/
	while (veri==false && cpt<163)/*boucle jusqu'a avoir toutes les valeurs ou qu'il a fait 163 fois le boucle(maximum necessaire pour remplir le tableau avec a chaque tour de boucle un seule des fonctions change quelque chose)*/
	{
		if (d==3)
		{
			printf("Entrez le numero de case");
			scanf("%d",&o);
			R1(p,o);/*applique la regle R1 a la grille*/
			affiche(p);
			R2(p,o);/*applique la regle R2 a la grille*/
			affiche(p);
			veri=verif(p);/*verifie si il reste des cases sans valeurs*/
			cpt=cpt+1;
			printf("Voulez vous continuez d'appliquer les regles 1 et 2 si oui taper 3");
			scanf("%d",&d);
		}
		else
		{
			printf("Voulez vous continuez d'appliquer les regles 1 et 2 si oui taper 3");
			scanf("%d",&d);
		}
	}
	return 0;
}