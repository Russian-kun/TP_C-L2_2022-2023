#include "common.h"
#include "graphique.h"
#include <string.h>

int main() {
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    Position pos;
    pos.carre = creer_tablette();
    Coup coup;
    Joueur gagnant;

    while (pos.carre.tab[0][0]) {
        mvprintw(0, 0, "Tour du joueur %d", pos.player + 1);
        afficher_position(pos);
        // mvprintw(LINES / 2, COLS / 2, "O");
        refresh();

        coup = lire_coup(pos);
        jouer_coup(&pos, coup);
        if (est_jeu_termine(pos, &gagnant))
            break;
        clear();
    }
    clear();

    int len = strlen("Victoire du Joueur  ");
    mvprintw(LINES / 2, COLS / 2 - len / 2, "Victoire du Joueur %d", gagnant + 1);

    refresh();
    getch();
    endwin();
    return 0;
}