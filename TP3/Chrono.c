#include "graphique.h"
#include "common.h"

int main() {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    int touche = -1;
    int quit = 0;

    Chronometre chrono = initialiser_chronometre();
    afficher_interface(chrono);
    refresh();
    while (1) {
        switch (touche) {
            case 'q':
                quit = 1;
            case ' ':
                ajouter_tour(&chrono);
                afficher_interface(chrono);
                refresh();
                break;
            default:
                break;
        }
        if (quit) {
            break;
        }
    }

    getch();
    endwin();
    return 0;
}