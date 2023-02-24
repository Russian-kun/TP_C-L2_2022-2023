#include "graphique.h"
#include <stdlib.h>

/**
 * @brief Retourne la taille d'un carré en fonction de la taille de la fenêtre
 * Le carre ne peut pas etre inferieur a 3 afin de pouvoir dessiner la grille
 * composée de carrés creux
 *
 * @return int
 */
int get_carre_size() {
    int carre = 0;
    if (LINES < NB_LIGNES || COLS < NB_COLONNES) {
        return -1;
    }
    if (LINES / NB_LIGNES < COLS / NB_COLONNES) {
        carre = LINES / NB_LIGNES;
    } else {
        carre = COLS / NB_COLONNES;
    }
    if (carre < 3 || carre * NB_LIGNES - (NB_LIGNES - 1) > LINES || carre * NB_COLONNES - (NB_COLONNES - 1) > COLS) {
        return -1;
    }
    return carre;
}

/**
 * @brief Transforme un couple de coordonnees sur une fenetre en coordonnees
 * sur la grille
 *
 * @param x
 * @param y
 * @return Coup
 */
int is_in_carre(int x, int y, Coup *coup) {
    Coup coords = couple_to_coord(x, y);
    if (coords.x != -1 && coords.y != -1) {
        *coup = coords;
        return 1;
    }
    return 0;
}

/**
 * @brief Affiche un carré de taille taille dont le coin superieur gauche est à la position (x, y)
 *
 * @param x
 * @param y
 * @param taille
 */
void affiche_carre(int x, int y, int taille) {
    if (taille <= 2 || x < 0 || y < 0)
        return;
    // lignes
    for (int i = 0; i < taille; i++) {
        mvaddch(y, x + i, '*');
        mvaddch(y + taille - 1, x + i, '*');
    }
    // colonnes
    for (int i = 0; i < taille; i++) {
        mvaddch(y + i, x, '*');
        mvaddch(y + i, x + taille - 1, '*');
    }
}

/**
 * @brief Affiche la grille de jeu. Les cases sont représentées par des carrés
 * creux connectes par leurs bords.
 *
 * @param pos
 */
void afficher_position(Position pos) {
    int carre = get_carre_size();
    if (carre == -1) {
        // Taille trop petite
        clear();
        mvprintw(LINES / 2, COLS / 2 - 10, "Taille de la fenetre trop petite");
        return;
    }
    int centrex = COLS / 2, centrey = LINES / 2;
    int x0 = centrex - (NB_COLONNES / 2) * carre + (NB_COLONNES / 2);
    int y0 = centrey + (NB_LIGNES / 2) - ((NB_LIGNES / 2) * carre);
    if (NB_COLONNES % 2 == 1)
        x0 -= carre / 2;
    if (NB_LIGNES % 2 == 1)
        y0 -= carre / 2;

    for (int i = 0; i < NB_COLONNES; i++) {
        for (int j = 0; j < NB_LIGNES; j++) {
            if (pos.carre.tab[j][i] == 1) {
                affiche_carre(x0 + i * (carre - 1), y0 + j * (carre - 1), carre);
                refresh();
            }
            // affiche_carre(x0 + i * (carre - 1), y0 + j * (carre - 1), carre);
            refresh();
        }
    }
    attron(COLOR_PAIR(1));
    affiche_carre(x0, y0, carre);
    attroff(COLOR_PAIR(1));
}

/**
 * @brief Transforme un couple de coordonnees sur une fenetre en coordonnees
 * sur la grille
 *
 * @param x
 * @param y
 * @return Coup
 */
Coup couple_to_coord(int x, int y) {
    int carre = get_carre_size();
    int centrex = COLS / 2, centrey = LINES / 2;
    int x0 = centrex - (NB_COLONNES / 2) * carre + (NB_COLONNES / 2);
    int y0 = centrey + (NB_LIGNES / 2) - ((NB_LIGNES / 2) * carre);
    if (NB_COLONNES % 2 == 1)
        x0 -= carre / 2;
    if (NB_LIGNES % 2 == 1)
        y0 -= carre / 2;

    int colonne = (x - x0) / (carre - 1);
    int ligne = (y - y0) / (carre - 1);

    return (Coup){colonne, ligne};
}

/**
 * @brief Lit un coup sur la fenetre graphique et le retourne
 * sous forme de Coup
 *
 * @param pos
 * @return Coup
 */
Coup lire_coup(Position pos) {
    MEVENT mouse;
    int touche = -1;
    Coup res;
    while (1) {
        touche = getch();
        getmouse(&mouse);
        if (touche == KEY_MOUSE) {
            if (mouse.x == 0 && mouse.y == 0) {
                // si on est sur le coin superieur gauche
                // Laisse ici pour le debug
                endwin();
                exit(0);
            }
            if (is_in_carre(mouse.x, mouse.y, &res)) {
                // si on est sur un carre disponible
                if (pos.carre.tab[res.y][res.x])
                    return res;
            }
        }
    }
}
