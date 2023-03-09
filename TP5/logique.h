#ifndef LOGIQUE_H
#define LOGIQUE_H

#include <stdlib.h>
#include <stdio.h>
// #include "common.h"

typedef struct _case_ {
    int x, y;
} Case;

typedef enum _direction_ {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct _body_ {
    Case *pos;
    struct _body_ *suiv;
    struct _body_ *prec;
} Body;

typedef struct _snake_ {
    Body *tete;
    int length;
    Direction direction;
} Serpent;

typedef struct _food_ {
    Case *pos;
} Pomme;

typedef struct _foodlist_ {
    Pomme *pomme;
    struct _foodlist_ *suiv;
} ListePomme;

typedef struct _game_ {
    Serpent snake;
    ListePomme *pommes;
    int score;
    int width, height;
} Monde;

Pomme pomme_aléatoire(int nb_lignes, int nb_colonnes);

void ajouter_pomme_liste(Pomme *p, ListePomme *l);

void free_pomme_liste(ListePomme *l);

int is_in_Snake(Serpent s, int x, int y);

int is_in_Pomme(ListePomme *l, int x, int y);

void monde_ajouter_pomme(Monde *mon);

Serpent serpent_initialiser(int nb_lignes, int nb_colonnes, int taille);

void free_serpent(Serpent s);

Case serpent_case_visee(Serpent serp);

Monde monde_initialiser(int nb_lignes, int nb_colonnes, int taille_serpent, int nb_pommes);

void free_monde(Monde m);

int monde_est_mort_serpent(Monde mon);

void monde_evoluer_serpent(Monde *mon);

void monde_maj(Monde *mon);

#endif
