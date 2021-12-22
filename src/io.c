#include "io.h"


void affiche_trait(int c)
{
	for (int i = 0; i < c; ++i) printf("|---");
	printf("|\n");
}

void affiche_ligne(int c, int* ligne, int vieillissement)
{
	for (int i = 0; i < c; ++i)
	{
		if (ligne[i] == 0) printf("|   ");
		else if (ligne[i] == -1) printf("| X "); // Non-viable
		else if (vieillissement) printf("| %d ", ligne[i]);
		else printf("| 0 ");
	}

	printf("|\n");
}

void affiche_grille(grille g, int tempsEvolution, int voisinageCyclique, int vieillissement, int tempsOscillation)
{
	const int l = g.nbl;
	const int c = g.nbc;
	const int h = g.nbh;
	char* cycliqueStr = voisinageCyclique ? "Activé" : "Désactivé";
	char* vieillissementStr = vieillissement ? "Activé" : "Désactivé";
	printf("\n");
	printf("\e[K");
	printf("Temps d'évolution: %d", tempsEvolution);
	printf(" | ");
	printf("Voisinage cyclique: %s", cycliqueStr);
	printf(" | ");
	printf("Vieillissement: %s", vieillissementStr);
	printf(" | ");
	printf("Oscillation: ");

	switch (tempsOscillation)
	{
	case -1:
		printf("Non testée");
		break;

	case 0:
		printf("Non oscillante");
		break;

	default:
		printf("%d pas de temps par oscillation.", tempsOscillation);
		break;
	}

	printf("\n\n");
	affiche_trait(c);
	for (int i = 0; i < l; ++i)
	{
		affiche_ligne(c, g.cellules[i], vieillissement);
		affiche_trait(c);
	}
	printf("\n");
}

void efface_grille(grille g)
{
	printf("\n\e[%dA", g.nbl * 2 + 7);
}

void debut_jeu(grille* g, grille* gc)
{
	// variables
	char c = (char)getchar();
	int skip = 0;
	int tempsEvolution = 1;
	int voisinageCyclique = 1;
	int vieillissement = 0;
	int tempsOscillation = -1; // -1 = non testée
	int (*compte_voisins_vivants)(int, int, int, grille) = compte_voisins_vivants_cyclique;

	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c)
		{
		case '\n':
			{
				if (skip)
				{
					skip = !skip;
					break;
				}
				// touche "entree" pour évoluer
				evolue(g, gc, compte_voisins_vivants, vieillissement, &tempsEvolution);
				efface_grille(*g);
				affiche_grille(*g, tempsEvolution, voisinageCyclique, vieillissement, tempsOscillation);
				break;
			}
		case 'n':
			{

				char nom_fichier_grille[256];
				
				do
				{
					printf("Veuillez entrer un nouveau fichier grille:\n");
					scanf("%s", nom_fichier_grille);
					FILE* fichier = fopen(nom_fichier_grille, "r");

					if (fichier == NULL)
					{
						printf("Erreur: le fichier n'existe pas.\n");
						continue;
					}

					fclose(fichier);
					break;

				} while (1);

				printf("Chargement du fichier %s...\n\n", nom_fichier_grille);
				// reset le temps
				tempsEvolution = 1;
				tempsOscillation = -1;
				
				// liberer la grille
				libere_grille(g);
				libere_grille(gc);

				// charger & démarrer le jeu
				init_grille_from_file(nom_fichier_grille, g);
				alloue_grille(g->nbl, g->nbc, g->nbh, gc);
				affiche_grille(*g, 1, voisinageCyclique, vieillissement, tempsOscillation);
				//debut_jeu(g, gc);
				skip = 1; // eviter d'evoluer a la prochaine action
				printf("\n\e[2A");
				printf("\n"); // nouvelle ligne pour eviter que la ligne du bas soit plus petite que les autres
				break;
			}
		case 'c':
			{
				voisinageCyclique = !voisinageCyclique;
				compte_voisins_vivants = voisinageCyclique
					                         ? &(compte_voisins_vivants_cyclique)
					                         : &(compte_voisins_vivants_non_cyclique);

				efface_grille(*g);
				affiche_grille(*g, tempsEvolution, voisinageCyclique, vieillissement, tempsOscillation);
				printf("\e[K");
				printf("\n");

				break;
			}
		case 'o':
			{
				tempsOscillation = testOscillation(g, compte_voisins_vivants, vieillissement);
				efface_grille(*g);
				affiche_grille(*g, tempsEvolution, voisinageCyclique, vieillissement, tempsOscillation);
				printf("\e[K");
				printf("\n");
				break;
			}
		case 'v':
			vieillissement = !vieillissement;
			//printf("\n\e[1A");
			efface_grille(*g);
			affiche_grille(*g, tempsEvolution, voisinageCyclique, vieillissement, tempsOscillation);
			//printf("\e[A");
			printf("\e[K");
			printf("\n");
			break;
		default:
			{
				// touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = (char)getchar();
	}
}
