#include "common.h"

Joueur adversaire(Joueur joueur) {
    return !joueur;
}

Tablette creer_tablette() {
    Tablette tab;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            tab.tab[i][j] = 1;
        }
    }
    return tab;
}

void manger(Tablette *tab, int x, int y) {
    for (int i = x; i < NB_LIGNES; i++) {
        for (int j = y; j < NB_COLONNES; j++) {
            tab->tab[i][j] = 0;
        }
    }
}

/**
 * @brief Test si le jeu est fini. Devrai etre appele apres
 * les coups
 *
 * @param pos
 * @param joueur_gagnant
 * @return int
 */
int est_jeu_termine(Position pos, Joueur *joueur_gagnant) {
    if (pos.carre.tab[0][0]) {
        *joueur_gagnant = adversaire(pos.player);
        return 1;
    }
    return 0;
}

void jouer_coup(Position *pos, Coup coup) {
    manger(&pos->carre, coup.x, coup.y);
    pos->player = adversaire(pos->player);
}