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
#include "all_types.h"

/* <Konstanten> */
#define REG_STATEVARS 4
/* <Konstanten/> */

/* <Typen> */
/**
 * @brief Struktur mit allen Parameter des Reglers
 */
typedef struct reg_par_s {
    all_reg_t pi;           /**< Reglerparameter ki, kp und AP        */
    float TA;               /**< Abtastzeit                           */
    float ki_x_TA;          /**< Ki x TA in init() einmalig berechnen */
    float lower_limit;      /**< Untere Begrenzung des Reglerausgangs */
    float upper_limit;      /**< Obere  Begrenzung des Reglerausgangs */
} reg_par_t;

/**
 * @brief Klassendefinition des Reglers
 *
 * Die Eingangs- und Ausgangsgroessen sind als Pointer auf die Groessen der uebergeordneten,
 * den Regler anwendenden Komponente angelegt.
 */
typedef struct reg_class_s {
    reg_par_t   p;                    /**< Parametersatz des PI-Reglers   */
    float       *y;                   /**< Pointer auf Stellgroesse zum Zeitpunkt t   */
    float       *soll;                /**< Pointer auf Sollwert zum Zeitpunkt t       */
    float       *ist;                 /**< Pointer auf Istwert zum Zeitpunkt t        */
    float       x[REG_STATEVARS];     /**< Zustandsgroessen fuer Blockdarstellung des Anti Windup PI-Reglers */
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




