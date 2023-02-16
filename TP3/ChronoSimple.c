#include "common.h"

int main() {
    int tmp = 500;
    int cent = 0, sec = 0, min = 0, heu = 0;
    int milli = 0;
    int milli2 = milli;
    struct timeval *deb = malloc(sizeof(struct timeval));
    struct timeval *fin = malloc(sizeof(struct timeval));
    printf("%d : %d : %d : %d\n", heu, min, sec, cent);
    gettimeofday(deb, NULL);
    while (1) {
        // gettimeofday(deb, NULL);
        usleep(tmp * 100);
        gettimeofday(fin, NULL);

        milli = intervalle_ms(*deb, *fin);
        milli2 = milli;
        cent = nb_ms_vers_centiemes(milli);
        sec = nb_ms_vers_secondes(milli);
        milli -= sec * 1000;
        min = nb_ms_vers_minutes(milli);
        milli -= min * 60000;
        heu = nb_ms_vers_heures(milli);
        milli -= heu * 360000;

        printf("%d : %d : %d : %d : %d : %d\n", heu, min, sec, cent, milli, milli2);
    }
    free(deb);
    free(fin);
    return 0;
}