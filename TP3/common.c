#include "common.h"

int intervalle_ms(struct timeval debut, struct timeval fin) {
    return fin.tv_usec - debut.tv_usec;
}

int nb_ms_vers_centiemes(int nb_ms) {
    return (int)(nb_ms / 10) % 100;
}

int nb_ms_vers_secondes(int nb_ms) {
    return (int)(nb_ms / 100) % 60;
}

int nb_ms_vers_minutes(int nb_ms) {
    return (int)(nb_ms / 6000) % 60;
}

int nb_ms_vers_heures(int nb_ms) {
    return (int)(nb_ms / 360000);
}