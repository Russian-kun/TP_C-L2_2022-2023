#include "common.h"
#include "graphique.h"
#define string char*

void afficher_duree(int y, int x, int nb_ms) {
    string text = calloc(sizeof(char), 100);

    int cent = nb_ms_vers_centiemes(nb_ms);
    int sec = nb_ms_vers_secondes(nb_ms);
    nb_ms -= sec * 1000;
    int min = nb_ms_vers_minutes(nb_ms);
    nb_ms -= min * 60000;
    int heu = nb_ms_vers_heures(nb_ms);
    // nb_ms -= heu * 360000;

    sprintf(text, "%02d : %02d : %02d : %02d", heu, min, sec, cent);

    mvprintw(y, x, "%s", text);
}

void afficher_interface(Chronometre chrono) {
    int nb_ms = chrono.duree_totale;

    char *commandes[] = {
        "Espace : lancer / mettre en pause",
        "r : reinitialiser",
        "t : marquer tour",
        "F1/F2 : incrementer / decrementer heure avertissement",
        "F3/F4 : incrementer / decrementer minute avertissement",
        "F5/F6 : incrementer / decrementer seconde avertissement",
        "q : quitter"};

    for (int i = 0; i < 7; i++) {
        int ind_inv = LINES - 7 + i;
        mvprintw(ind_inv, 0, "%s", commandes[i]);
    }
    move(LINES - 8, 0);
    for (int i = 0; i < COLS; i++) {
        addch('-');
    }
    int x = COLS / 2 - 10;
    int y = LINES / 2;
    if (y < 9) {
        y = 9;
    }
    if (x < 0 || y < 0) {
        return;
    }
    mvprintw(LINES - 9, COLS / 2 - 10 - strlen("Avertissement : "), "Avertissement : ");
    afficher_duree(LINES - 9, COLS / 2 - 10, chrono.avertissement);
    afficher_duree(LINES - 10, COLS / 2 - 10, nb_ms);

    mvprintw(0, COLS / 2 - 10, "Chronometre");
}

void afficher_flash() {
    move(LINES - 8, 0);
    for (int i = 0; i < COLS; i++) {
        attron(1);  // + i % 2
        addch('*');
        attroff(1);  // + i % 2
    }
    refresh();
    usleep(100000);
    move(LINES - 8, 0);
    for (int i = 0; i < COLS; i++) {
        attron(2);  // - i % 2
        addch('*');
        attroff(2);  // - i % 2
    }
    refresh();
    usleep(100000);
}