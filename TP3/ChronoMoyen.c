#include "common.h"

int main() {
    initscr();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    struct timeval *deb = malloc(sizeof(struct timeval));
    struct timeval *fin = malloc(sizeof(struct timeval));

    gettimeofday(deb, NULL);

    long int duree_totale = 0;
    bool chrono = 0;

    int touche = -1;

    while (1) {
        gettimeofday(fin, NULL);
        touche = getch();

        if (touche == 32) {  // Code de la touche espace
            chrono = 0 ? 1 : 0;
            if (chrono) {
                gettimeofday(deb, NULL);
                int tmp = (int)(duree_totale / 1000);
                deb->tv_sec -= tmp;
                deb->tv_usec -= (int)(duree_totale - tmp);
            }
        }
        if (chrono) {
            duree_totale = intervalle_ms(*deb, *fin);
        }

        mvprintw(0, 0, "%ld", duree_totale);
    }

    return 0;
}