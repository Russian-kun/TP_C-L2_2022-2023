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