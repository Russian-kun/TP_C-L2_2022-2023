# TP4

BAILLARGEAU Axel
BOUHAFA Siwar

## Introduction

Le but de ce TP est de creer un jeu de Chomp dans ncurses. Le jeu se joue a deux joueurs. Le premier joueur a jouer est celui qui a le plus de points. Le joueur qui a le moins de points commence. Le joueur qui a le plus de points commence.

Il a permit de mettre en pratique les notions de ncurses et modularisation du code en plusieurs fichiers.

## Moyens mis en oeuvre

### Fonctionnement du jeu

Le jeu se joue a deux joueurs. Le but est faire manger la derniere case a l'adversaire.

Le joueur 1 commence.

### Fonctionnement du code

Le code est decoupe en plusieurs fichiers:

- `Chomp.c` : contient la fonction `main`
- `common.h` : contient les structures et les prototypes des fonctions principales du jeu
- `graphique.h` : contient les prototypes des fonctions de gestion de l'affichage

#### Fonctions principales

Le jeu en lui meme n'est pas complexe. La difficulte est de gerer l'affichage. La fonction la plus importante est donc `afficher_position`. Elle affiche le plateau de jeu centre dans la fenetre. Elle affiche aussi<!-- les scores et --> le joueur qui doit jouer.

## Conclusion

Ce TP nous a permis de mettre en pratique les notions de ncurses et de modularisation du code en plusieurs fichiers.

## Annexes

### Compilation

Pour compiler le code, il est possible d'utiliser le script `Compilation.sh` fourni ou bien le makefile. Notez que le makefile n'utilise pas le script `Compilation.sh`. Afin de compiler la version non modulaire avec le makefile, il faut utiliser la commande `make nonmodulaire`.

### Execution

Pour executer le code, il est possible d'utiliser le script `Execution.sh` fourni ou bien le makefile. Notez que le makefile n'utilise pas le script `Execution.sh`. Afin d'executer la version non modulaire avec le makefile, il faut utiliser la commande `make nonmodulaire`.
