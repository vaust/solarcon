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
 * @file filter.c
 * @brief Implementierung von Filterfunktion wie Moving Average
 * @author Volker Stegmann
 */

#define _FILTER_C_

#include "filter.h"

/**
 * @brief Initialisierung eines gleitenden Mittelwerts.
 */
void filter_avg_Init( filter_avg_t *self, u16_t len )
{
    s16_t   n;
    
    self->len = len;
    for( n=0; n<FILTER_MAXLEN; n++ ) {
        self->x[n] = 0.0;
    }
    self->idx = 0;
    self->sum = 0.0;
    self->avg = 0.0;
}

/**
 * @brief Aufruffunktion zur Aktualisierung eins gleitenden Mittelwerts.
 *
 * Diese Funktion wird jedesmal aufgerufen, wenn ein neuer Messwert zur Verfuegung steht.
 * In der Regel wird der Messwert in einem festen Zeitraster ermittelt und dem Filter zugefuehrt.
 *
 * @param     self Pointer auf Objekt der Klasse \ref filter_avg_t
 * @param[in] xn   Neuer Messwert
 */
void filter_avg_Run( filter_avg_t *self, const float xn )
{
    self->sum += xn - self->x[self->idx];
    self->x[self->idx] = xn;
    self->idx ++;
    if( self->idx > self->len ) {
        self->idx = 0;
    }
    self->avg = self->sum/self->len;
}

void filter_fir_Run( filter_fir_t *self, const float xn )
{
   s16_t i;

   self->x[self->idx] = xn;
   for( i=0; i<self->len; i++ ) {
       self->sum += self->a[i] * self->x[(self->idx - i) % self->len];
   }
   self->fir = self->sum / self->nrm;
   self->idx ++;
   if( self->idx > self->len ) {
       self->idx = 0;
   }
}







    

