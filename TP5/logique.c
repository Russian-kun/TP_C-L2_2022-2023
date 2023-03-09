#include "logique.h"

Pomme pomme_aléatoire(int nb_lignes, int nb_colonnes) {
    Pomme p;
    p.pos = malloc(sizeof(Case));
    p.pos->x = rand() % nb_colonnes;
    p.pos->y = rand() % nb_lignes;
    return p;
}

void ajouter_pomme_liste(Pomme *p, ListePomme *l) {
    while (l->suiv != NULL) {
        l = l->suiv;
    }
    l->suiv = malloc(sizeof(ListePomme));
    l->suiv->pomme = p;
    l->suiv->suiv = NULL;
}

void free_pomme_liste(ListePomme *l) {
    while (l != NULL) {
        ListePomme *tmp = l;
        l = l->suiv;
        free(tmp);
    }
}

int is_in_Snake(Serpent s, int x, int y) {
    Body *b = s.tete;
    while (b != NULL) {
        if (b->pos->x == x && b->pos->y == y) {
            return 1;
        }
        b = b->suiv;
    }
    return 0;
}

int is_in_Pomme(ListePomme *l, int x, int y) {
    while (l != NULL) {
        if (l->pomme->pos->x == x && l->pomme->pos->y == y) {
            return 1;
        }
        l = l->suiv;
    }
    return 0;
}

void monde_ajouter_pomme(Monde *mon) {
    Pomme p;
    do {
        p = pomme_aléatoire(mon->height, mon->width);
    } while (is_in_Snake(mon->snake, p.pos->x, p.pos->y) || is_in_Pomme(mon->pommes, p.pos->x, p.pos->y));
    ajouter_pomme_liste(&p, mon->pommes);
}

Serpent serpent_initialiser(int nb_lignes, int nb_colonnes, int taille) {
    Serpent s;
    s.tete = malloc(sizeof(Body));
    s.tete->pos->x = nb_colonnes / 2;
    s.tete->pos->y = nb_lignes / 2;
    s.tete->suiv = NULL;
    Body *b = s.tete;
    for (int i = 1; i < taille; i++) {
        b->suiv = malloc(sizeof(Body));
        b->suiv->pos->x = b->pos->x - 1;
        b->suiv->pos->y = b->pos->y;
        b->suiv->suiv = NULL;
        b = b->suiv;
    }
    return s;
}

void free_serpent(Serpent s) {
    Body *b = s.tete;
    while (b != NULL) {
        Body *tmp = b;
        b = b->suiv;
        free(tmp);
    }
}

// Renvoie la case dans la quelle le serpent vas se déplacer
Case serpent_case_visee(Serpent serp) {
    int direction = serp.direction;
    int x = serp.tete->pos->x, y = serp.tete->pos->y;
    switch (direction) {
        case 0:
            y--;
            break;
        case 1:
            x++;
            break;
        case 2:
            y++;
            break;
        case 3:
            x--;
            break;
    }
    Case c;
    c.x = x;
    c.y = y;
    return c;
}

Monde monde_initialiser(int nb_lignes, int nb_colonnes, int taille_serpent, int nb_pommes) {
    Monde m;
    m.snake = serpent_initialiser(nb_lignes, nb_colonnes, taille_serpent);
    m.pommes = malloc(sizeof(ListePomme));
    m.pommes->suiv = NULL;
    for (int i = 0; i < nb_pommes; i++) {
        monde_ajouter_pomme(&m);
    }
    m.score = 0;
    m.width = nb_colonnes;
    m.height = nb_lignes;
    return m;
}

void free_monde(Monde m) {
    free_serpent(m.snake);
    free_pomme_liste(m.pommes);
}

int monde_est_mort_serpent(Monde mon) {
    Case c = serpent_case_visee(mon.snake);
    if (c.x < 0 || c.x >= mon.width || c.y < 0 || c.y >= mon.height) {
        return 1;
    }
    Body *b = mon.snake.tete;
    while (b != NULL) {
        if (b->pos->x == c.x && b->pos->y == c.y) {
            return 1;
        }
        b = b->suiv;
    }
    return 0;
}

void monde_evoluer_serpent(Monde *mon) {
    Case c = serpent_case_visee(mon->snake);
    Body *b = mon->snake.tete;
    while (b->suiv != NULL) {
        b = b->suiv;
    }
    b->suiv = malloc(sizeof(Body));
    b->suiv->pos = malloc(sizeof(Case));
    b->suiv->pos->x = c.x;
    b->suiv->pos->y = c.y;
    b->suiv->suiv = NULL;
    b = mon->snake.tete;
    mon->snake.tete = mon->snake.tete->suiv;
    free(b);
}

void monde_maj(Monde *mon) {
    monde_evoluer_serpent(mon);
    // On mange une pomme
    for (ListePomme *l = mon->pommes; l != NULL; l = l->suiv) {
        if (l->pomme->pos->x == mon->snake.tete->pos->x && l->pomme->pos->y == mon->snake.tete->pos->y) {
            mon->score++;
            // On ajoute une pomme
            monde_ajouter_pomme(mon);
            // On ajoute un body au serpent
            Body *b = mon->snake.tete;
            while (b->suiv != NULL) {
                b = b->suiv;
            }
            b->suiv = malloc(sizeof(Body));
            b->suiv->pos = malloc(sizeof(Case));
            b->suiv->pos->x = b->pos->x;
            b->suiv->pos->y = b->pos->y;
            b->suiv->suiv = NULL;
            // On supprime la pomme
            ListePomme *tmp = l->suiv;
            l->suiv = l->suiv->suiv;
            free(tmp);
        }
    }
}