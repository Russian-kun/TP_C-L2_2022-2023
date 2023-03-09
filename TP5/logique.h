#ifndef LOGIQUE_H
#define LOGIQUE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct _case_ {
    int x, y;
} Case, Pomme;

typedef enum _type_ {
    SERP,
    POMM,
    POIS,
    BONU,
    VITE
} Type;

typedef struct _listecase_ {
    Case *pos;
    Type type;
    struct _listecase_ *suiv;
} ListeCase, Body, ListePomme;

typedef enum _direction_ {
    UP,
    RIGHT,
    DOWN,
    LEFT
} Direction;

typedef struct _snake_ {
    Body *tete;
    int length;
    Direction direction;
} Serpent;

typedef struct _game_ {
    Serpent snake;
    ListePomme *pommes;
    int score, pause, boost, vitesse, poison;
    int width, height;
} Monde;

Pomme pomme_aléatoire(int nb_lignes, int nb_colonnes);

void ajouter_pomme_liste(Pomme *p, ListePomme *l);

void free_pomme_liste(ListePomme *l);

int is_in_Case(ListeCase *l, Case pos);

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
