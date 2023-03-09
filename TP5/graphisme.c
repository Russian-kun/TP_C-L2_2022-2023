#include "graphisme.h"

void interface_afficher_quadrillage(Monde mon) {
    for (int i = 0; i < mon.height; i++) {
        for (int j = 0; j < mon.width; j++) {
            mvprintw(i, j, " ");
        }
    }
}

void interface_afficher_pommes(Pomme pom) {
    mvprintw(pom.pos->y, pom.pos->x, "o");
}

void interface_afficher_pommes_liste(ListePomme *l) {
    while (l != NULL) {
        interface_afficher_pommes(*l->pomme);
        l = l->suiv;
    }
}

void interface_afficher_serpent(Serpent s) {
    Body *b = s.tete;
    while (b != NULL) {
        mvprintw(b->pos->y, b->pos->x, "x");
        b = b->suiv;
    }
}

void interface_afficher_monde(Monde mon) {
    interface_afficher_quadrillage(mon);
    interface_afficher_pommes_liste(mon.pommes);
    interface_afficher_serpent(mon.snake);
}

void interface_piloter(Monde *mon) {
    int c = getch();
    switch (c) {
        case KEY_UP:
            mon->snake.direction = UP;
            break;
        case KEY_DOWN:
            mon->snake.direction = DOWN;
            break;
        case KEY_LEFT:
            mon->snake.direction = LEFT;
            break;
        case KEY_RIGHT:
            mon->snake.direction = RIGHT;
            break;
        default:
            break;
    }
}

void afficher_score(Monde mon) {
    // fin de partie
    mvprintw(LINES / 2, COLS / 2, "Fin de la partie");
    mvprintw(LINES / 2 + 1, COLS / 2, "Score : %d", mon.score);
}