#include "common.h"

int main() {
    initscr();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    struct timeval *deb = malloc(sizeof(struct timeval));
    struct timeval *fin = malloc(sizeof(struct timeval));

    int cent = 0, sec = 0, min = 0, heu = 0;

    gettimeofday(deb, NULL);
    int delai = 100000;

    long int duree_totale = 0;
    bool chrono = FALSE;

    int touche = -1;

    while (1) {
        touche = getch();

        if (touche == 32) {  // Code de la touche espace
            chrono = !chrono;
            if (chrono) {
                gettimeofday(deb, NULL);
                int sec_tmp = (int)(duree_totale / 1000);
                deb->tv_sec -= sec_tmp;
                deb->tv_usec -= (duree_totale - sec_tmp * 1000) * 1000;
            }
        } else if (touche == KEY_BACKSPACE)
            break;

        if (chrono) {
            gettimeofday(fin, NULL);
            duree_totale = intervalle_ms(*deb, *fin);
        }

        cent = nb_ms_vers_centiemes(duree_totale);
        sec = nb_ms_vers_secondes(duree_totale);
        duree_totale -= sec * 1000;
        min = nb_ms_vers_minutes(duree_totale);
        duree_totale -= min * 60000;
        heu = nb_ms_vers_heures(duree_totale);

        mvprintw(LINES / 2 - 1, COLS / 2 - (17 / 2), "%02d : %02d : %02d : %02d", heu, min, sec, cent);

        refresh();
        usleep(delai);
    }

    free(deb);
    free(fin);
    clear();
    endwin();
    return 0;
}