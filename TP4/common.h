#ifndef COMMON_H
#define COMMON_H
#define NB_LIGNES 3
#define NB_COLONNES 5

/// @brief Une tablette est un tableau NB_LIGNES * NB_COLONNES
typedef struct _tablette {
    int tab[NB_LIGNES][NB_COLONNES];
} Tablette;

typedef enum _joueur { JOUEUR_1,
                       JOUEUR_2 } Joueur;

/// @brief Une position est une tablette et un joueur
typedef struct _position {
    Tablette carre;
    Joueur player;
} Position;

/// @brief Un coup est une position (x, y) sur la tablette
typedef struct _coup {
    int x, y;
} Coup;

/**
 * @brief Renvoie l’adversaire du joueur
 *
 * @param joueur
 * @return Joueur
 */
Joueur adversaire(Joueur joueur);

/**
 * @brief Renvoie une variable de Tablette de dimension
 * NB_LIGNES * NB_COLONNES. La tablette renvoyée
 * possède tous ses carrés de chocolat.
 *
 * @return Tablette
 */
Tablette creer_tablette();

/**
 * @brief modifie la tablette tab de sorte à manger le carré de
 * chocolat en position (x, y) ainsi que tous ceux qui sont en
 * dessous de lui et à sa droite.
 *
 * @param tab
 * @param x
 * @param y
 */
void manger(Tablette *tab, int x, int y);

/**
 * @brief Test si le coup est legal
 *
 * @param pos
 * @param coup
 * @return int
 */
int est_legal(Position pos, Coup coup);

/**
 * @brief Test si le jeu est fini. Devrai etre appele apres
 * les coups
 *
 * @param pos
 * @param joueur_gagnant
 * @return int
 */
int est_jeu_termine(Position pos, Joueur *joueur_gagnant);

/**
 * @brief Joue le coup coup dans la position pos si il est
 * legal.
 *
 * @param pos
 * @param coup
 */
void jouer_coup(Position *pos, Coup coup);

#endif