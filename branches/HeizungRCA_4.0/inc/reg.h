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

#ifndef _REG_H_
#define _REG_H_

#include "gen_types.h"

/* <Konstanten> */
#define REG_STATEVARS 4
/* <Konstanten/> */

/* <Typen> */
/**
 * @brief Rueckgabewert für Reglermethoden
 */
typedef enum reg_return_e { REG_OK, REG_NOK } reg_return_t;

/**
 * @brief Struktur mit allen Parameter des Reglers
 */
typedef struct reg_par_s {
    float TA;               /**< Abtastzeit                           */
    float kp;               /**< Proportionalbeiwert                  */
    float ki;               /**< Integralbeiwert                      */
    float ap;               /**< Arbeitspunkt des Reglers             */
    float lower_limit;      /**< Untere Begrenzung des Reglerausgangs */
    float upper_limit;      /**< Obere  Begrenzung des Reglerausgangs */
} reg_par_t;

/**
 * @brief Struktur mit den Eingangswerten des Reglers
 */
typedef struct reg_in_s {
	float ist;				/**< Istwert zum Zeitpunkt t  */
	float soll;				/**< Sollwert zum Zeitpunkt t */
} reg_in_t;

/**
 * @brief Struktur mit den Ausgangswerten des Reglers
 */
typedef struct reg_out_s {
	float y;				/**< Stellgroesse y zum Zeitpunkt t */
} reg_out_t;

/** 
 * @brief Typendefinitionen f�r Interfacemethoden
 */
typedef reg_return_t (*reg_read_in_t)(reg_in_t *);
typedef reg_return_t (*reg_write_out_t)(reg_out_t *);

/**
 * @brief Klassendefinition des Reglers
 *
 * Die Eingangs- und Ausgangsgroessen werden ueber Interfacemethoden ermittelt.
 * den Regler anwendenden Komponente angelegt.
 */
typedef struct reg_class_s {
    reg_par_t   	p;                    /**< Parametersatz des PI-Reglers   */
    float       	x[REG_STATEVARS];     /**< Zustandsgroessen fuer Blockdarstellung des Anti Windup PI-Reglers */
	reg_read_in_t	read_in;
	reg_write_out_t	write_out;
} reg_class_t;

/* <Typen> */

/* <Prototypen> */
float reg_Limit( float value, const float lower_limit, const float upper_limit );
void reg_PI_Init(       reg_class_t *self,
                  const float        TA,
                  const float        kp,
                  const float        ki,
                  const float        ap,
                  const float        lower_limit,
                  const float        upper_limit,
                        float       *y,
                        float       *soll,
                        float       *ist      );

float reg_PI_Run( reg_class_t *self );
/* <Prototypen/> */

#endif /* _SUP_H_ */




