#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H
#include "common.h"
#include <ncurses.h>

/**
 * @brief Retourne la taille d'un carré en fonction de la taille de la fenêtre
 * Le carre ne peut pas etre inferieur a 3 afin de pouvoir dessiner la grille
 * composée de carrés creux
 *
 * @return int
 */
int get_carre_size();

/**
 * @brief Transforme un couple de coordonnees sur une fenetre en coordonnees
 * sur la grille
 *
 * @param x
 * @param y
 * @return Coup
 */
int is_in_carre(int x, int y, Coup *coup);

/**
 * @brief Affiche un carré de taille taille dont le coin superieur gauche est à la position (x, y)
 *
 * @param x
 * @param y
 * @param taille
 */
void affiche_carre(int x, int y, int taille);

/**
 * @brief Affiche la grille de jeu. Les cases sont représentées par des carrés
 * creux connectes par leurs bords.
 *
 * @param pos
 */
void afficher_position(Position pos);

/**
 * @brief Transforme un couple de coordonnees sur une fenetre en coordonnees
 * sur la grille
 *
 * @param x
 * @param y
 * @return Coup
 */
Coup couple_to_coord(int x, int y);

/**
 * @brief Lit un coup sur la fenetre graphique et le retourne
 * sous forme de Coup
 *
 * @param pos
 * @return Coup
 */
Coup lire_coup(Position pos);

#endif