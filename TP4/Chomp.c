#include "common.h"
#include "graphique.h"
#include <string.h>

int main() {
    initscr();
    curs_set(0);

    Position pos;
    pos.carre = creer_tablette();
    Coup coup;
    Joueur gagnant;

    while (pos.carre.tab[0][0]) {
        afficher_position(pos);
        refresh();

        coup = lire_coup(pos);
        jouer_coup(&pos, coup);
        if (est_jeu_termine(pos, &gagnant))
            break;
    }
    clear();

    int len = strlen("Victoire du Joueur  ");
    mvprintw(LINES / 2, COLS / 2 - len / 2, "Victoire du Joueur %d", gagnant);

    refresh();
    getch();
    endwin();
    return 0;
}