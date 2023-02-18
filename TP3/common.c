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
    short int tmp = (short int)(nb_ms / (1000 * 60)) % 60;
    return tmp < 0 ? tmp * -1 : tmp;
}

int nb_ms_vers_heures(int nb_ms) {
    short int tmp = (short int)(nb_ms / (1000 * 60 * 60)) % 99;
    return tmp < 0 ? tmp * -1 : tmp;
}

Chronometre initialiser_chronometre() {
    Chronometre c;
    c.duree_totale = 0;
    c.avertissement = 25000;
    c.indice_der_tour = 0;
    c.nb_tours = 0;
    for (int i = 0; i < 6; i++) {
        c.tab[i] = 0;
    }
    return c;
}

void reinitialiser_chronometre(Chronometre *chrono) {
    chrono->duree_totale = 0;
    chrono->indice_der_tour = 0;
    chrono->nb_tours = 0;
}

void ajouter_tour(Chronometre *chrono) {
    for (int i = 0; i < chrono->nb_tours; i++) {
        int ind_inv = chrono->nb_tours - i - 1;
        chrono->tab[ind_inv] = chrono->tab[ind_inv - 1];
    }
    chrono->tab[0] = chrono->duree_totale;
    if (chrono->nb_tours == 6) {
        chrono->nb_tours--;
    }
    chrono->nb_tours++;
    chrono->indice_der_tour++;
}

int avertissement(Chronometre chrono) {
    return chrono.duree_totale > chrono.avertissement;
}