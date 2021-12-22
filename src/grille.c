#include "grille.h"

int init_grille_from_file(char* filename, grille* g)
{
	FILE* pfile = NULL;
	pfile = fopen(filename, "r");

	int i, j, k, n, l, c, h, vivantes = 0, non_viables = 0;

	if (pfile == NULL) return 1; // le fichier n'existe pas

	fscanf(pfile, "%d", &l);
	fscanf(pfile, "%d", &c);
	fscanf(pfile, "%d", &h);

	alloue_grille(l, c, h, g);

	fscanf(pfile, "%d", &vivantes);
	for (n = 0; n < vivantes; ++n)
	{
		fscanf(pfile, "%d", &i);
		fscanf(pfile, "%d", &j);
		fscanf(pfile, "%d", &k);
		set_vivante(i, j, k, *g);
	}

	fscanf(pfile, "%d", &non_viables);
	for (n = 0; n < non_viables; ++n)
	{
		fscanf(pfile, "%d", &i);
		fscanf(pfile, "%d", &j);
		fscanf(pfile, "%d", &k);
		set_non_viable(i, j, k, *g);
	}

	fclose(pfile);
	return 0;
}


void copie_grille(grille gs, grille gd)
{
	int i, j;
	for (i = 0; i < gs.nbl; ++i) for (j = 0; j < gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;
}

// alloue une grille de taille l*c, et initialise toutes les cellules � mortes
void alloue_grille(int l, int c, int h, grille* g)
{
	g->nbc = c;
	g->nbl = l;
	g->nbh = h;
	g->cellules = (int**)malloc(sizeof(int*) * l);
	for (int i = 0; i < l; ++i)
	{
		g->cellules[i] = (int*)malloc(sizeof(int*) * c);
		for (int j = 0; j < c; ++j) set_morte(i, j, *g);
	}
}

// lib�re une grille
void libere_grille(grille* g)
{
	for (int i = 0; i < g->nbl; ++i)
		free(g->cellules[i]);
	free(g->cellules);
}

int grillesEquals(grille* g1, grille* g2) {
	for (int i = 0; i < g1->nbl; i++)
		for (int j = 0; j < g1->nbc; j++)
			if (g1->cellules[i][j] != g2->cellules[i][j])
				return 0;
	return 1;
}

int grillesEmpty(grille* g) {
	for (int i = 0; i < g->nbl; i++)
		for (int j = 0; j < g->nbc; j++)
			if (g->cellules[i][j] > 0)
				return 0;
	return 1;
}

int testOscillation(grille* g, int (*compte_voisins_vivants) (int, int, int, grille), int vieillissement) {
	int tempsEvolutionOscillation = 0;
	grille copieGrille;
	grille grilleEvoluee;
	grille temp;
	alloue_grille(g->nbl, g->nbc, g->nbh, &copieGrille);
	copie_grille(*g, copieGrille);

	alloue_grille(g->nbl, g->nbc, g->nbh, &grilleEvoluee);
	copie_grille(*g, grilleEvoluee);

	alloue_grille(g->nbl, g->nbc, g->nbh, &temp);
	copie_grille(*g, temp);

	int i = 0;
	
	do {
		// on cherche une similitude
		while (tempsEvolutionOscillation < 1000) { 	// > 1000 �volutions de cellules, la grille ne peut pas etre oscillante

			#pragma GCC diagnostic push
			#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
			evolue(&grilleEvoluee, &temp, compte_voisins_vivants, vieillissement, &tempsEvolutionOscillation);
			#pragma GCC diagnostic pop

			if (grillesEmpty(&copieGrille))
			{
				libere_grille(&copieGrille);
				libere_grille(&grilleEvoluee);
				libere_grille(&temp);
				// plus d'�volution donc on retourne 0
				return 0;
			}
			
			if (grillesEquals(&copieGrille, &grilleEvoluee)) {
				// si les grilles  sont �gales c'est qu'on a r�ussi � trouver une oscillation
				libere_grille(&copieGrille);
				libere_grille(&grilleEvoluee);
				libere_grille(&temp);
				return tempsEvolutionOscillation;
			}
			
		}

		evolue(&copieGrille, &temp, compte_voisins_vivants, vieillissement, &tempsEvolutionOscillation);
		copie_grille(copieGrille, grilleEvoluee);

		// on recommence � 0 car on a pas trouv� de similitudes
		tempsEvolutionOscillation = 0;
		i++;
	} while (i < 100); // > 100 �volutions de cellules, il n'y a plus de comportement oscillatoire

	// liberer les grilles

	libere_grille(&copieGrille);
	libere_grille(&grilleEvoluee);
	libere_grille(&temp);
	return 0;
}
