#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#define NB_LIGNES 3
#define NB_COLONNES 5

/// @brief Une tablette est un tableau NB_LIGNES * NB_COLONNES
typedef struct _tablette {
    int tab[NB_LIGNES][NB_COLONNES];
} Tablette;

typedef enum _joueur { JOUEUR_1,
                       JOUEUR_2 } Joueur;

/// @brief Une position est une tablette et un joueur
typedef struct _position {
    Tablette carre;
    Joueur player;
} Position;

/// @brief Un coup est une position (x, y) sur la tablette
typedef struct _coup {
    int x, y;
} Coup;

/**
 * @brief Renvoie l’adversaire du joueur
 *
 * @param joueur
 * @return Joueur
 */
Joueur adversaire(Joueur joueur) {
    return !joueur;
}

/**
 * @brief Renvoie une variable de Tablette de dimension
 * NB_LIGNES * NB_COLONNES. La tablette renvoyée
 * possède tous ses carrés de chocolat.
 *
 * @return Tablette
 */
Tablette creer_tablette() {
    Tablette tab;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            tab.tab[i][j] = 1;
        }
    }
    return tab;
}

/**
 * @brief modifie la tablette tab de sorte à manger le carré de
 * chocolat en position (x, y) ainsi que tous ceux qui sont en
 * dessous de lui et à sa droite.
 *
 * @param tab
 * @param x
 * @param y
 */
void manger(Tablette *tab, int x, int y) {
    for (int j = x; j < NB_COLONNES; j++) {
        for (int i = y; i < NB_LIGNES; i++) {
            tab->tab[i][j] = 0;
        }
    }
}

/**
 * @brief Test si le coup est legal
 *
 * @param pos
 * @param coup
 * @return int
 */
int est_legal(Position pos, Coup coup) {
    return pos.carre.tab[coup.y][coup.x];
}

/**
 * @brief Test si le jeu est fini. Devrai etre appele apres
 * les coups. Puisque jouer_coup change le joueur, on
 * considere que le joueur actuel est celui qui a gagne.
 *
 * @param pos
 * @param joueur_gagnant
 * @return int
 */
int est_jeu_termine(Position pos, Joueur *joueur_gagnant) {
    if (!pos.carre.tab[0][0]) {
        *joueur_gagnant = pos.player;
        return 1;
    }
    return 0;
}

/**
 * @brief Joue le coup coup dans la position pos si il est
 * legal.
 *
 * @param pos
 * @param coup
 */
void jouer_coup(Position *pos, Coup coup) {
    if (!est_legal(*pos, coup))
        return;
    manger(&pos->carre, coup.x, coup.y);
    pos->player = adversaire(pos->player);
}

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

int main() {
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    Position pos;
    pos.carre = creer_tablette();
    Coup coup;
    Joueur gagnant;

    while (pos.carre.tab[0][0]) {
        mvprintw(0, 0, "Tour du joueur %d", pos.player + 1);
        afficher_position(pos);
        // mvprintw(LINES / 2, COLS / 2, "O");
        refresh();

        coup = lire_coup(pos);
        jouer_coup(&pos, coup);
        if (est_jeu_termine(pos, &gagnant))
            break;
        clear();
    }
    clear();

    int len = strlen("Victoire du Joueur  ");
    mvprintw(LINES / 2, COLS / 2 - len / 2, "Victoire du Joueur %d", gagnant + 1);

    refresh();
    getch();
    endwin();
    return 0;
}