/*
 *  SOLARCON Modular Solar Supported Home Heating Controller
 *  Copyright (C) 2011  Volker Stegmann
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file filter.h
 * @brief Interface fuer verschiedene digitale Filteralgorithmen.
 */

#ifndef _FILTER_H_
#define _FILTER_H_

#include "gen_types.h"

/* <Defines> */
#define FILTER_MAXLEN 60  /**< @brief Maximale Laenge eines Ringspeichers digitaler Filter */
/* <Defines/> */

/* <Typen> */
/** @brief Definition der Komponentenklasse des gleitenden Mittelwerts (Moving Average) */
typedef struct filter_avg_s {
    float   x[FILTER_MAXLEN];   /**< Ringspeicher der Eingangswerte                    */
    u16_t   idx;                /**< Indexzeiger auf aktuelles Element im Ringspeicher */
    u16_t   len;                /**< Laenge des Ringspeichers                          */
    float   sum;                /**< Summe vor Normierung durch Laenge                 */
    float   avg;                /**< Eigentlicher Mittelwert                           */
} filter_avg_t;

/** @brief Definition der Komponentenklasse des Finite Impulse Response Filters */
typedef struct filter_fir_s {
    float   x[FILTER_MAXLEN];   /**< Ringspeicher der Eingangswerte                    */
    u16_t   idx;                /**< Indexzeiger auf aktuelles Element im Ringspeicher */
    u16_t   len;                /**< Laenge des Ringspeichers                          */
    float   a[FILTER_MAXLEN];   /**< Koeffizienten des Ringspeichers mult. mit nrm     */
    float   nrm;                /**< Normierungsfaktor, um Rundungsfehler zu min.      */
    float   sum;                /**< Summe vor Normierung durch nrm                    */
    float   fir;                /**< Eigentlicher Filterwert                           */
} filter_fir_t;

/** @brief Definition der Komponentenklasse des infinite Impulse Response Filters */
typedef struct filter_iir_s {
    float   x[FILTER_MAXLEN];   /**< Ringspeicher der Eingangswerte                    */
    float   y[FILTER_MAXLEN];   /**< Ringspeicher der Ausgangswerte                    */
    u16_t   idx;                /**< Indexzeiger auf aktuelles Element im Ringspeicher */
    u16_t   len;                /**< Laenge des Ringspeichers                          */
    float   a[FILTER_MAXLEN];   /**< Zaehlerkoeffizienten multipliziert mit nrm        */
    float   b[FILTER_MAXLEN];   /**< Nennerkoeffizienten multipliziert mit nrm         */
    float   nrm;                /**< Normierungsfaktor, um Rundungsfehler zu min.      */
    float   sum;                /**< Summe vor Normierung durch nrm                    */
    float   iir;                /**< Eigentlicher Filterwert                           */
} filter_iir_t;
 
/* <Typen/> */

/* <Prototypen> */
void filter_avg_Init( filter_avg_t *self, u16_t len );
void filter_avg_Run( filter_avg_t *self, float xn );
/* <Prototypen/> */

#endif /* _FILTER_H_ */

