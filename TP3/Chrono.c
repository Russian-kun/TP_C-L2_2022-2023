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
        touche = getch();
        switch (touche) {
            case 'q':
                quit = 1;
            case ' ':
                ajouter_tour(&chrono);
                afficher_interface(chrono);
                refresh = 1;
                break;

            case KEY_F(0):
                chrono.avertissement = 25000;
                afficher_interface(chrono);
                refresh = 1;
                break;

            case KEY_F(1):
                chrono.avertissement += 1000 * 60 * 60;
                chrono.avertissement = chrono.avertissement > 360060990 ? 360060990 : chrono.avertissement;
                afficher_interface(chrono);
                refresh = 1;
                break;

            case KEY_F(2):
                chrono.avertissement -= 1000 * 60 * 60;
                chrono.avertissement = chrono.avertissement < 0 ? 0 : chrono.avertissement;
                afficher_interface(chrono);
                refresh = 1;
                break;

            case KEY_F(3):
                chrono.avertissement += 1000 * 60;
                chrono.avertissement = chrono.avertissement > 360060990 ? 360060990 : chrono.avertissement;
                afficher_interface(chrono);
                refresh = 1;
                break;

            case KEY_F(4):
                chrono.avertissement -= 1000 * 60;
                chrono.avertissement = chrono.avertissement < 0 ? 0 : chrono.avertissement;
                afficher_interface(chrono);
                refresh = 1;
                break;

            case KEY_F(5):
                chrono.avertissement += 1000;
                chrono.avertissement = chrono.avertissement > 360060990 ? 360060990 : chrono.avertissement;
                afficher_interface(chrono);
                refresh = 1;
                break;

            case KEY_F(6):
                chrono.avertissement -= 1000;
                chrono.avertissement = chrono.avertissement < 0 ? 0 : chrono.avertissement;
                afficher_interface(chrono);
                refresh = 1;
                break;

            case KEY_RESIZE:
                while (LINES <= MINY || COLS <= MINX || touche == 'q') {
                    clear();
                    afficher_interface(chrono);
                    attron(COLOR_PAIR(1));
                    mvprintw(LINES / 2, COLS / 2 - 33 / 2, "Taille de la fenetre trop petite");
                    attroff(COLOR_PAIR(1));
                    nodelay(stdscr, FALSE);
                    touche = getch();
                refresh();
                break;
            default:
                break;
        }
        if (quit) {
            break;
        }

        if (avertissement(chrono)) {
            afficher_flash();
            pause = 1;
        }

        if (!pause) {
            gettimeofday(&last_time, NULL);
            chrono.duree_totale = intervalle_ms(first_time, last_time);
            afficher_interface(chrono);
            refresh = 1;
        }

        if (refresh) {
            refresh();
            refresh = 0;
        }
    }

    getch();
    endwin();
    return 0;
}