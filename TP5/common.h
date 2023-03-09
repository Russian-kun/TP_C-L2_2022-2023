#ifndef COMMON_H
#define COMMON_H

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

#endif