#include "graphique.h"
#include "common.h"

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);

    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);

    int pause = 1, quit = 0, refresh = 1, touche = -1;

    struct timeval first_time;
    struct timeval last_time;

    gettimeofday(&first_time, NULL);
    last_time = first_time;

    Chronometre chrono = initialiser_chronometre();
    afficher_interface(chrono);
    refresh();
    while (1) {
        touche = getch();
        switch (touche) {
            case 32:
                pause = !pause;
                if (pause) {
                    mvprintw(0, 0, "P");
                    refresh = 1;
                } else {
                    mvprintw(0, 0, " ");
                    gettimeofday(&first_time, NULL);
                    int sec_tmp = (int)(chrono.duree_totale / 1000);
                    first_time.tv_sec -= sec_tmp;
                    first_time.tv_usec -= (chrono.duree_totale - sec_tmp * 1000) * 1000;
                }
                break;

            case 'q':
                quit = 1;
                break;

            case 'r':
                pause = 1;
                reinitialiser_chronometre(&chrono);
                gettimeofday(&first_time, NULL);
                last_time = first_time;

                clear();
                afficher_interface(chrono);
                refresh = 1;
                break;

            case 't':
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
                }
                clear();
                afficher_interface(chrono);
                nodelay(stdscr, TRUE);
                refresh = 1;
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

    // getch();
    endwin();
    return 0;
}