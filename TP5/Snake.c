#include "logique.h"
#include "graphisme.h"
#include <time.h>
#include <unistd.h>

#define SNAKE_MAX_LENGTH 100
// #define NB_LIGNES 20
// #define NB_COLONNES 20
#define TAILLE_SNAKE 3
#define NB_POMMES 3

int main() {
    // Initialisation de ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    srand(time(NULL));
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    int cmpt_boost = 0;

    time_t t1, t2;

    // Initialisation du monde
    Monde mon = monde_initialiser(LINES, COLS, TAILLE_SNAKE, NB_POMMES);

    // Affichage initial
    interface_afficher_monde(mon);

    refresh();

    // Boucle principale
    while (!monde_est_mort_serpent(mon)) {
        // On attend un peu
        if (cmpt_boost > 0) {
            time(&t2);
            if (t2 - t1 >= cmpt_boost) {
                mon.vitesse = 250000;
                cmpt_boost = 0;
            }
        }
        if (mon.boost) {
            cmpt_boost = 10;
            time(&t1);
            mon.boost = 0;
        }
        usleep(mon.vitesse);

        // On récupère les entrées clavier
        interface_piloter(&mon);

        // On met à jour le monde
        if (!mon.pause)
            monde_maj(&mon);

        // On affiche le monde
        interface_afficher_monde(mon);

        if (mon.score < 0) {
            mon.score *= -1;
            break;
        }

        refresh();

        effacer_serpent(mon.snake);
    }
    clear();
    afficher_score(mon);
    refresh();

    // On attend que l'utilisateur appuie sur une touche
    nodelay(stdscr, FALSE);
    getch();

    // On quitte ncurses
    endwin();

    // On libère la mémoire
    free_monde(mon);

    return 0;
}