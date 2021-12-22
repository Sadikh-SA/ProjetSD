#include <stdio.h>
#include <stdlib.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}

	FILE* grilleFile = fopen(argv[1], "r");

	// je demande le chemin complet car j'ai envie de plus de liberté au niveau des fichiers
	// si je veux tester d'autres fichiers de grille qui ne sont pas dans le dossier par exemple.

	if (grilleFile == NULL)
	{
		fclose(grilleFile);
		printf("Erreur: le fichier n'existe pas.\n");
		return 1;
	}

	grille g, gc;

	// charger & démarrer le jeu
	if(init_grille_from_file(argv[1], &g))
	{
		printf("Erreur: le fichier n'existe pas.\n");
		return 1;
	}
	
	alloue_grille(g.nbl, g.nbc, g.nbh, &gc);

	affiche_grille(g, 1, 1, 0, -1);
	
	debut_jeu(&g, &gc);

	// libérer la mémoire
	libere_grille(&g);
	libere_grille(&gc);

	return 0;
}
