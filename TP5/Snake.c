#include "logique.h"
#include "graphisme.h"
#include <time.h>
#include <unistd.h>

#define SNAKE_MAX_LENGTH 100
#define NB_LIGNES 20
#define NB_COLONNES 20
#define TAILLE_SNAKE 5
#define NB_POMMES 2

int main() {
    // Initialisation de ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    srand(time(NULL));

    // Initialisation du monde
    Monde mon = monde_initialiser(NB_LIGNES, NB_COLONNES, TAILLE_SNAKE, NB_POMMES);

    // Affichage initial
    interface_afficher_monde(mon);

    refresh();

    // Boucle principale
    while (!monde_est_mort_serpent(mon)) {
        // On attend un peu
        usleep(250000);

        // On récupère les entrées clavier
        interface_piloter(&mon);

        // On met à jour le monde
        monde_maj(&mon);

        // On affiche le monde
        interface_afficher_monde(mon);

        refresh();
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