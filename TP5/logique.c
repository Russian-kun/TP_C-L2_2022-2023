#include "logique.h"

Pomme pomme_aléatoire(int nb_lignes, int nb_colonnes) {
    Pomme p;
    p.x = rand() % nb_colonnes;
    p.y = rand() % nb_lignes;
    return p;
}

void ajouter_pomme_liste(Pomme *p, ListePomme *l) {
    int cmpt_pomme = 0;
    if (l->pos == NULL) {
        l->pos = p;
        l->type = POMM;
        l->suiv = NULL;
        return;
    }
    while (l->suiv != NULL) {
        l = l->suiv;
        if (l->type == POMM || l->type == BONU)
            cmpt_pomme++;
    }
    l->suiv = malloc(sizeof(ListePomme));
    l->suiv->pos = p;
    l->suiv->type = rand() % 4 + 1;
    if (cmpt_pomme == 0)
        l->suiv->type = POMM;
    l->suiv->suiv = NULL;
}

void supprimer_pomme_liste(Pomme *p, ListePomme *l) {
    ListePomme *tmp = l;
    while (l->suiv != NULL) {
        if (l->pos->x == p->x && l->pos->y == p->y) {
            tmp->suiv = l->suiv;
            free(l);
            return;
        }
        tmp = l;
        l = l->suiv;
    }
}

void free_pomme_liste(ListePomme *l) {
    while (l != NULL) {
        ListePomme *tmp = l;
        l = l->suiv;
        free(tmp->pos);
        free(tmp);
    }
}

int is_in_Case(ListeCase *l, Case pos) {
    while (l != NULL && l->pos != NULL) {
        if (l->pos->x == pos.x && l->pos->y == pos.y) {
            return 1;
        }
        l = l->suiv;
    }
    return 0;
}

void monde_ajouter_pomme(Monde *mon) {
    Pomme *p = malloc(sizeof(Pomme));
    do {
        *p = pomme_aléatoire(mon->height, mon->width);
        if (is_in_Case(mon->snake.tete, *p) || is_in_Case(mon->pommes, *p)) {
            continue;
        } else {
            break;
        }
    } while (1);
    ajouter_pomme_liste(p, mon->pommes);
}

Serpent serpent_initialiser(int nb_lignes, int nb_colonnes, int taille) {
    Serpent s;
    s.tete = malloc(sizeof(Body));
    s.tete->pos = malloc(sizeof(Case));
    s.tete->pos->x = nb_colonnes / 2;
    s.tete->pos->y = nb_lignes / 2;
    s.tete->type = SERP;
    s.tete->suiv = NULL;
    Body *b = s.tete;
    for (int i = 1; i < taille; i++) {
        b->suiv = malloc(sizeof(Body));
        b->suiv->pos = malloc(sizeof(Case));
        b->suiv->pos->x = b->pos->x - 1;
        b->suiv->pos->y = b->pos->y;
        b->suiv->type = SERP;
        b->suiv->suiv = NULL;
        b = b->suiv;
    }
    s.direction = RIGHT;
    s.length = taille;
    return s;
}

void free_serpent(Serpent s) {
    Body *b = s.tete;
    while (b != NULL) {
        Body *tmp = b;
        b = b->suiv;
        free(tmp->pos);
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
    m.width = nb_colonnes;
    m.height = nb_lignes;
    m.snake = serpent_initialiser(nb_lignes, nb_colonnes, taille_serpent);
    m.pommes = malloc(sizeof(ListePomme));
    m.pommes->pos = NULL;
    for (int i = 0; i < nb_pommes; i++) {
        monde_ajouter_pomme(&m);
    }
    m.score = 0;
    m.pause = 0;
    m.vitesse = 250000;
    m.boost = 0;
    m.poison = 0;
    return m;
}

void free_monde(Monde m) {
    free_serpent(m.snake);
    free_pomme_liste(m.pommes);
}

int monde_est_mort_serpent(Monde mon) {
    Case c = serpent_case_visee(mon.snake);
    if (c.x < 0 - 1 || c.x >= mon.width + 1 || c.y < 0 - 1 || c.y >= mon.height + 1 || mon.poison) {
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
    Case c = serpent_case_visee(mon->snake);  // On récupère la case où le serpent va se déplacer
    Body *b = mon->snake.tete;
    while (b->suiv != NULL) {
        b = b->suiv;
    }
    // TODO COMPLETEMENT BROKEN
    b->suiv = malloc(sizeof(Body));  // On alloue un nouveau maillon à la queue du serpent
    b->suiv->pos = malloc(sizeof(Case));
    b->suiv->type = SERP;
    b->suiv->pos->x = mon->snake.tete->pos->x;  // On copie les coordonnées de la tête dans le nouveau maillon
    b->suiv->pos->y = mon->snake.tete->pos->y;
    b->suiv->suiv = NULL;
    b = mon->snake.tete;
    mon->snake.tete = mon->snake.tete->suiv;  // On décale la tête de la queue
    free(b->pos);                             // On libère la mémoire occupée par la tête
    free(b);
    mon->snake.tete->pos->x = c.x;  // On déplace la tête vers la case c
    mon->snake.tete->pos->y = c.y;
}

void monde_maj(Monde *mon) {
    monde_evoluer_serpent(mon);
    int cmpt_pomme = 0;
    // On mange une pomme
    for (ListePomme *l = mon->pommes; l != NULL; l = l->suiv) {
        if (l->pos != NULL && (l->type != POIS || l->type != VITE)) {
            cmpt_pomme++;
        }
        if (l->pos->x == mon->snake.tete->pos->x && l->pos->y == mon->snake.tete->pos->y) {
            int aggrand = 0;
            switch (l->type) {
                case POMM:
                    mon->score++;
                    aggrand = 1;
                    break;

                case POIS:
                    mon->poison = 1;
                    break;

                case BONU:
                    mon->score += 2;
                    aggrand = 1;
                    break;

                case VITE:
                    mon->vitesse /= 2;
                    mon->boost = 1;
                    break;

                default:
                    break;
            }
            // On ajoute un body au serpent
            if (aggrand) {
                Body *b = mon->snake.tete;
                while (b->suiv != NULL) {
                    b = b->suiv;
                }
                // TODO COMPLETEMENT BROKEN
                b->suiv = malloc(sizeof(Body));
                b->suiv->pos = malloc(sizeof(Case));
                b->suiv->pos->x = b->pos->x;
                b->suiv->pos->y = b->pos->y;
                b->suiv->suiv = NULL;
                mon->snake.length++;
            }
            // supprimer_pomme_liste(l->pos, mon->pommes);
            // On modifie la pomme
            *l->pos = pomme_aléatoire(mon->height, mon->width);
            if (l->type == POMM || l->type == BONU) cmpt_pomme--;
            l->type = rand() % 4 + 1;
            if ((l->type == POIS || l->type == VITE) && cmpt_pomme == 0) l->type = POMM;
            // On ajoute une pomme
            monde_ajouter_pomme(mon);
            break;
        }
    }
}
