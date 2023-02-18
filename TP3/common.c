#include "common.h"

int intervalle_ms(struct timeval debut, struct timeval fin) {
    long int tmp = (fin.tv_usec - debut.tv_usec) / 1000 + (fin.tv_sec - debut.tv_sec) * 1000;
    return tmp < 0 ? tmp * -1 : tmp;
}

int nb_ms_vers_centiemes(int nb_ms) {
    short int tmp = (short int)(nb_ms / 10) % 100;
    return tmp < 0 ? tmp * -1 : tmp;
}

int nb_ms_vers_secondes(int nb_ms) {
    short int tmp = (short int)(nb_ms / 1000) % 60;
    return tmp < 0 ? tmp * -1 : tmp;
}

int nb_ms_vers_minutes(int nb_ms) {
    short int tmp = (short int)(nb_ms / 60000) % 60;
    return tmp < 0 ? tmp * -1 : tmp;
}

int nb_ms_vers_heures(int nb_ms) {
    short int tmp = (short int)(nb_ms / 360000);
    return tmp < 0 ? tmp * -1 : tmp;
}

Chronometre initialiser_chronometre() {
    Chronometre c;
    c.duree_totale = 0;
    c.avertissement = 25000;
    c.indice_der_tour = 0;
    c.nb_tours = 0;
    return c;
}

void reinitialiser_chronometre(Chronometre *chrono) {
    chrono->duree_totale = 0;
    chrono->indice_der_tour = 0;
    chrono->nb_tours = 0;
}

void ajouter_tour(Chronometre *chrono) {
    if (chrono->indice_der_tour == 6) {
        for (int i = 0; i < 5; i++) {
            chrono->tab[i] = chrono->tab[i + 1];
        }
        chrono->indice_der_tour--;
    }
    chrono->nb_tours++;
    chrono->indice_der_tour++;
    chrono->tab[chrono->indice_der_tour - 1] = chrono->duree_totale;
}

int avertissement(Chronometre chrono) {
    return chrono.duree_totale > chrono.avertissement;
}