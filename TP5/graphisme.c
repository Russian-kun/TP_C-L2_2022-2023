#include "graphisme.h"

void interface_afficher_quadrillage(Monde mon) {
    for (int i = 0; i < mon.height; i++) {
        for (int j = 0; j < mon.width; j++) {
            mvprintw(i, j, " ");
        }
    }
}

void interface_afficher_pommes(Pomme pom) {
    mvprintw(pom.y, pom.x, "o");
}

void interface_afficher_pommes_liste(ListePomme *l) {
    while (l != NULL && l->pos != NULL) {
        attron(COLOR_PAIR(l->type));
        interface_afficher_pommes(*l->pos);
        attroff(COLOR_PAIR(l->type));
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

void effacer_serpent(Serpent s) {
    Body *b = s.tete;
    while (b != NULL) {
        mvprintw(b->pos->y, b->pos->x, " ");
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
            if (mon->snake.direction != DOWN)
                mon->snake.direction = UP;
            break;
        case KEY_RIGHT:
            if (mon->snake.direction != LEFT)
                mon->snake.direction = RIGHT;
            break;
        case KEY_DOWN:
            if (mon->snake.direction != UP)
                mon->snake.direction = DOWN;
            break;
        case KEY_LEFT:
            if (mon->snake.direction != RIGHT)
                mon->snake.direction = LEFT;
            break;
        case 'p':
            mvprintw(LINES / 2, COLS / 2, "Pause");
            nodelay(stdscr, FALSE);
            getch();
            nodelay(stdscr, TRUE);
            clear();
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