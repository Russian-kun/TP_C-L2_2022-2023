# TP 3

BAILLARGEAU Axel
BOUHAFA Siwar

## Introduction

Le but de ce tp est de creer un chronometre. Il y a trois chronometres differents plus ou moins complets.

## Explications

### ChronoSimple

Le chrono simple est un chrono qui affiche le temps ecoule depuis le debut de l'execution. Il est affiche dans la console. Il imprime toutes les 500 ms le temps ecoule depuis le debut de l'execution. Il est arrete avec ctrl+c.

### ChronoMoyen

Le chrono moyen est un chrono utilisant ncurses qui peut se mettre en pause et de reprendre. Le temps est affiche au centre de la fenetre. Il est arrete avec espace et peut etre quitter avec "backspace".

Afin de pouvoir reprendre le chronometre, on soustrait le temps courant (prit au moment de la reprise) au temps chronometre. On peut donc reprendre le chronometre sans que le temps ecoule ne soit modifie.

### Chrono

Chrono est la version complete du chrono. Il permet de chronometrer et d'ajouter des tours. Il est possible de le mettre en pause et de le reprendre. Il est possible de le reset avec "r", de quitter avec "q", ainsi que mettre en place un avertissement qui affiche des etoiles colorees alternant entre rouge et bleu. Il est possible de mettre en pause le chrono avec "space" et de le reprendre avec "space".

L'avertissement ne fait que verifier si le temps ecoule est superieur a l'avertissement. Le seul moyen de l'arreter est de remettre le chrono a 0 ou augmenter le temps d'avertissement.

## Annexe

### Compilation

Le tp se compile a l'aide du makefile avec la commande :
gcc -o $$$$$ -Wall -Wfatal-errors -fdiagnostics-color=always -g -lncurses. Les -g est present a des fins de debugging.

### Execution et utilisation

L'execution se fait a l'aide des differents fichiers sans extensions. Il n'y a pas d'arguments a donner. Les controles se font au clavier.
