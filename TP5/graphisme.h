#ifndef GRAPHISME_H
#define GRAPHISME_H

#include <ncurses.h>
#include "logique.h"

void interface_afficher_quadrillage(Monde mon);

void interface_afficher_pommes(Pomme pom);

void interface_afficher_pommes_liste(ListePomme *l);

void interface_afficher_serpent(Serpent s);

void interface_afficher_monde(Monde mon);

void interface_piloter(Monde *mon);

void afficher_score(Monde mon);

#endif
