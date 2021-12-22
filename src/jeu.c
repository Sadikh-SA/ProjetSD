#include "jeu.h"

int compte_voisins_vivants_cyclique(int i, int j, int k, grille g)
{
	int v = 0, l = g.nbl, c = g.nbc, h = g.nbh;
	v += est_vivante(modulo(i - 1, l), modulo(j - 1, c), modulo(k - 1, h), g);
	v += est_vivante(modulo(i - 1, l), modulo(j, c), modulo(k - 1, h), g);
	v += est_vivante(modulo(i - 1, l), modulo(j + 1, c), modulo(k - 1, h), g);
	v += est_vivante(modulo(i, l), modulo(j - 1, c), modulo(k, h), g);
	v += est_vivante(modulo(i, l), modulo(j + 1, c), modulo(k, h), g);
	v += est_vivante(modulo(i + 1, l), modulo(j - 1, c), modulo(k + 1, h), g);
	v += est_vivante(modulo(i + 1, l), modulo(j, c), modulo(k + 1, h), g);
	v += est_vivante(modulo(i + 1, l), modulo(j + 1, c), modulo(k + 1, h), g);

	return v;
}

int compte_voisins_vivants_non_cyclique(int i, int j, int k, grille g)
{
	int v = 0, l = g.nbl, c = g.nbc, h = g.nbh;

	v += (i - 1 >= 0 && j - 1 >= 0 && k - 1 >= 0) ? est_vivante(i - 1, j - 1, k - 1, g) : 0;
	v += (i - 1 >= 0 && k - 1 >= 0) ? est_vivante(i - 1, j, k - 1, g) : 0;
	v += (i - 1 >= 0 && j + 1 < c && k - 1 >= 0) ? est_vivante(i - 1, j + 1, k + 1, g) : 0;
	v += (j - 1 >= 0) ? est_vivante(i, j - 1, k, g) : 0;
	v += (j + 1 < c) ? est_vivante(i, j + 1, k, g) : 0;
	v += (i + 1 < l && j - 1 >= 0 && k + 1 < h) ? est_vivante(i + 1, j - 1, k - 1, g) : 0;
	v += (i + 1 < l && k + 1 < h) ? est_vivante(i + 1, j, k, g) : 0;
	v += (i + 1 < l && j + 1 < c && k + 1 < h) ? est_vivante(i + 1, j + 1, k + 1, g) : 0;

	return v;
}

void evolue(grille* g, grille* gc, int (*compte_voisins_vivants)(int, int, int, grille), int vieillissement, int* tempsEvolution)
{
	copie_grille(*g, *gc); // copie temporaire de la grille
	int i, j, k, l = g->nbl, c = g->nbc, h = g->nbh, v;
	(*tempsEvolution)++;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < c; ++j)
		{
			for (k = 0; k < h; ++j)
			{

				if (est_non_viable(i, j, k, *g))
					continue;
				
				v = compte_voisins_vivants(i, j, k, *gc);
				if (est_vivante(i, j, k, *g))
				{
					// evolution d'une cellule vivante
					if (v != 2 && v != 3)
					{
						set_morte(i, j, *g);
					}
					// si cellule non morte et vieillissement activé, alors augmenter l'âge de la cellule
					else if(vieillissement)
					{
						g->cellules[i][j]++;

						//Une cellule meurt de viellesse quand son âge dépasse 8 pas de temps.
						if(g->cellules[i][j] > 8) set_morte(i, j, *g);

					} else {
						// si vieillissement désactivé remettre à 1 (vivante)
						g->cellules[i][j] = 1;
					}
					
					continue;
				}
			}

			// evolution d'une cellule morte
			if (v == 3) set_vivante(i, j, k, *g);
			
		}
	}
	return;
}
