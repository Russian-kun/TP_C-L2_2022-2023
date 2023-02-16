#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>

#define _DEFAULT_SOURCE 1

/**
 * @brief Renvoie le nombre de millisecondes entre deux timeval
 *
 * @param debut
 * @param fin
 * @return int
 */
int intervalle_ms(struct timeval debut, struct timeval fin);

/**
 * @brief Convertit les milisecondes en centiemes de seconde modulo 100
 *
 * @param nb_ms
 * @return int
 */
int nb_ms_vers_centiemes(int nb_ms);

/**
 * @brief Convertit les milisecondes en secondes modulo 60
 *
 * @param nb_ms
 * @return int
 */
int nb_ms_vers_secondes(int nb_ms);

/**
 * @brief Convertit les milisecondes en minutes modulo 60
 *
 * @param nb_ms
 * @return int
 */
int nb_ms_vers_minutes(int nb_ms);

/**
 * @brief Convertit les milisecondes en heures
 *
 * @param nb_ms
 * @return int
 */
int nb_ms_vers_heures(int nb_ms);