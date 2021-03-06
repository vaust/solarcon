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
 * @file sol.h
 * @author Volker Stegmann
 * @brief Interface fuer Solarkomponente
 */

#ifndef _SOL_H_
#define _SOL_H_

#include "gen_types.h"

/* <Defines> */
#define SOL_NORMAL           0
#define SOL_UEBERTEMPERATUR -1

#define SOL_N_SP    2
#define SOL_N_KO    1

#define SP1     0
#define SP2     1
#define KO1     0
/* <Defines/> */

/* <Typen> */
/**
 * @brief Parameter der Komponente sol
 */
typedef struct sol_param_s {
    float sp_t_max;     /**< Maximal zulaessige Speichertemperatur                                      */
    float dt_ein_sw;    /**< Temperaturdifferenz zwischen Kollektor- und Speicher, die Ventil oeffnet   */
    float dt_aus_sw;    /**< Temperaturdifferenz zwischen Kollektor- und Speicher, die Ventil schliesst */
    float k_wlf;        /**< P(Solarheizkreis) = k_wlf * ( th_sol - th_sp_u ) / Einheit [kW/K]          */
    float TA;           /**< Abtastzeit als Integrationszeit fuer den Waermezaehler                     */
} sol_param_t;

/**
 * @brief Obere und untere Temperatur eines Solarspeichers
 */
typedef struct sol_sp_t_mw_s {
    float to_mw;        /**< Obere Speichertemperatur  */
    float tu_mw;        /**< Untere Speichertemperatur */
} sol_sp_t_mw_t;

/**
 * @brief Eingangsgroessen der Komponente sol
 */
typedef struct sol_in_s {
    float           koll_t_mw[SOL_N_KO];  /**< Array von Kollektortemperaturen (aktuell nur ein Element) */
    sol_sp_t_mw_t   t_sp[SOL_N_SP];       /**< Array auf Speichertemperaturpaare (aktuell 2 Elemente)    */
} sol_in_t;

/**
 * @brief Ausgangssgroessen der Komponente sol
 */
typedef struct sol_out_s {
    do_bitbyte_t    av_sb[SOL_N_SP];      /**< Array auf Absperrventilzustaende  (aktuell 2 Elemente)       */
    do_bitbyte_t    pu_sb[SOL_N_KO];      /**< Array auf Kollektorpumpenzustaende (aktuell nur ein Element) */
} sol_out_t;   

/**
 * @brief Definition der Klasse sol (Komponente)
 */
typedef struct sol_class_s {
    sol_param_t p;          /**< Parameter der Solar Komponente                   */
    sol_in_t    i;          /**< Eingangsgroessen der Solarkomponente             */
    sol_out_t   o;          /**< Ausgangsgroessen der Solarkomponente             */
    float       sol_wz;     /**< Waermezaehler fuer den Solarkreis / Einheit [kJ] */
} sol_class_t;

/* <Typen/> */
/* <Prototypen> */

void sol_Init( sol_class_t *self );
s16_t sol_Run( sol_class_t *self );
void sol_Wz( sol_class_t *self );

void sol_WriteInp(       sol_class_t *self,
                   const float        koll_t_mw,
                   const float        sp1_to_mw,
                   const float        sp1_tu_mw,
                   const float        sp2_to_mw,
                   const float        sp2_tu_mw );
/* <Prototypen/> */

#endif /* _SOL_H_ */

