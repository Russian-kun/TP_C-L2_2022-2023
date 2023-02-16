#include "common.h"

int main() {
    initscr();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    noecho();

    struct timeval *deb = malloc(sizeof(struct timeval));
    struct timeval *fin = malloc(sizeof(struct timeval));

    gettimeofday(deb, NULL);
    int delai = 100000;

    long int duree_totale = 0;
    bool chrono = FALSE;

    int touche = -1;

    while (1) {
        touche = getch();

        if (touche == 32) {  // Code de la touche espace
            if (chrono == FALSE) {
                chrono = TRUE;
            } else {
                chrono = FALSE;
            }
            if (chrono) {
                gettimeofday(deb, NULL);
                int sec_tmp = (int)(duree_totale / 1000);
                deb->tv_sec -= sec_tmp;
                deb->tv_usec -= (duree_totale - sec_tmp * 1000) * 1000;
            } else {
                mvprintw(0, 0, "   ");
            }
        } else if (touche == KEY_BACKSPACE)
            break;

        if (chrono) {
            gettimeofday(fin, NULL);
            duree_totale = intervalle_ms(*deb, *fin);
        }

        mvprintw(LINES / 2, COLS / 2, "%ld", duree_totale);
        refresh();
        usleep(delai);
    }

    free(deb);
    free(fin);
    clear();
    endwin();
    return 0;
}