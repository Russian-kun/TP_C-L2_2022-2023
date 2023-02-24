#include "common.h"

/**
 * @brief Renvoie l’adversaire du joueur
 *
 * @param joueur
 * @return Joueur
 */
Joueur adversaire(Joueur joueur) {
    return !joueur;
}

/**
 * @brief Renvoie une variable de Tablette de dimension
 * NB_LIGNES * NB_COLONNES. La tablette renvoyée
 * possède tous ses carrés de chocolat.
 *
 * @return Tablette
 */
Tablette creer_tablette() {
    Tablette tab;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            tab.tab[i][j] = 1;
        }
    }
    return tab;
}

/**
 * @brief modifie la tablette tab de sorte à manger le carré de
 * chocolat en position (x, y) ainsi que tous ceux qui sont en
 * dessous de lui et à sa droite.
 *
 * @param tab
 * @param x
 * @param y
 */
void manger(Tablette *tab, int x, int y) {
    for (int j = x; j < NB_COLONNES; j++) {
        for (int i = y; i < NB_LIGNES; i++) {
            tab->tab[i][j] = 0;
        }
    }
}

/**
 * @brief Test si le coup est legal
 *
 * @param pos
 * @param coup
 * @return int
 */
int est_legal(Position pos, Coup coup) {
    return pos.carre.tab[coup.y][coup.x];
}

/**
 * @brief Test si le jeu est fini. Devrai etre appele apres
 * les coups. Puisque jouer_coup change le joueur, on
 * considere que le joueur actuel est celui qui a gagne.
 *
 * @param pos
 * @param joueur_gagnant
 * @return int
 */
int est_jeu_termine(Position pos, Joueur *joueur_gagnant) {
    if (!pos.carre.tab[0][0]) {
        *joueur_gagnant = pos.player;
        return 1;
    }
    return 0;
}

/**
 * @brief Joue le coup coup dans la position pos si il est
 * legal.
 *
 * @param pos
 * @param coup
 */
void jouer_coup(Position *pos, Coup coup) {
    if (!est_legal(*pos, coup))
        return;
    manger(&pos->carre, coup.x, coup.y);
    pos->player = adversaire(pos->player);
}