#include "graphique.h"
#include "common.h"

int main() {
    initscr();
    Chronometre chrono = initialiser_chronometre();
    afficher_interface(chrono);
    refresh();
    getch();
    endwin();
    return 0;
}