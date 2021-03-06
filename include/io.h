/** \file io.h
 *	\brief Fonctions pour gérer les entrées et sorties
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"


 /**
  * \fn void affiche_trait(int c)
  * \brief Affichage d'un trait horizontal
  *
  * \param c Entier représentant le nombre de colonnes de longueur qu'aura le trait horizontal
  */
void affiche_trait(int c);

/**
 * \fn void affiche_ligne(int c, int* ligne)
 * \brief Affichage d'une ligne de la grille
 *
 * \param c Entier représentant le nombre de colonnes de longueur qu'aura la ligne
 * \param ligne Poiteur sur un tableau d'entier contenant l'état des cellules de la ligne
 * \param vieillissement Affiche ou non l'age des cellules
 */
void affiche_ligne(int c, int* ligne, int vieillissement);

/**
 * \fn void affiche_grille(grille g)
 * \brief Affichage d'une grille
 *
 * \param g Objet grille que l'on souhaite afficher
 * \param tempsEvolution Le temps d'évolution de la grille
 * \param voisinageCyclique Activer ou désactiver le voisinage cyclique
 * \param vieillissement Affiche ou non l'age des cellules
 * \param tempsOscillation Pas de temps par oscillation
 */
void affiche_grille(grille g, int tempsEvolution, int voisinageCyclique, int vieillissement, int tempsOscillation);

#endif

/**
 * \fn void efface_grille(grille g)
 * \brief Effacement d'une grille
 *
 * \param g Objet grille que l'on souhaite effacer
 */
void efface_grille(grille g);

/**
 * \fn void debut_jeu(grille* g, grille* gc)
 * \brief Démarrer le jeu
 *
 * \param g Pointeur sur la grille principale
 * \param gc Pointeur sur une seconde grill qui contient l'évolution de la première grille
 */
void debut_jeu(grille* g, grille* gc);
