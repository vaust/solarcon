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
 * @file hk.h
 * @brief Interface fuer die Heizkoerperheizkreiskomponente
 */

#ifndef _HK_H_
#define _HK_H_

#include "reg.h"

/* <Typen> */

/**
 * @brief Zusammenfassung der Heizkoerperparameter
 */
typedef struct hk_param_s {
    float tvl_absenk;            /**< Nachtabsenkung in Grad C             */
    float tvl_steigung;          /**< Heizkurvensteigung                   */
    float tvl_niveau;            /**< Heizkurven Parallelverschiebung      */
    float tvl_min;               /**< min. Vorlauftemperatur in Grad C     */
    float tvl_max;               /**< max. Vorlauftemperatur in Grad C     */
    float at_start;              /**< Aussentemperatur ab der geheizt wird */
    float frostschutz;           /**< Frostschutztemperatur in Grad C      */
    float tr_sw;                 /**< Raumtemperatursollwert in Grad C     */
} hk_param_t;

/**
 * @brief Zusammenfassung der Eingangsgroessen der Heizkoerperheizung
 */
typedef struct hk_in_s {
    float        tau_mw;         /**< Messwert der Aussentemperatur                            */
    float        tau_avg;        /**< gleitender Mittelwert der AT ueber 36h                   */
    float        tvl_mw;         /**< Vorlauftemperatur auf der Sek.-seite des Waermetauschers */
    abgesenkt_t  zustand;        /**< Absenkungsstatus der Fussbodenheizung                    */
    u8_t         partytime_flg;  /**< Partyzeitanzeige                                         */
} hk_in_t;

/**
 * @brief Zusammenfassung der Ausgangsgroessen der Heizkoerperheizung
 */
typedef struct hk_out_s {
    float            tvl_sw;     /**< berechneter Vorlauftemperatursollwert          */
    float            mv_y;       /**< dazu notwendige Mischventilstellung in Prozent */
    do_bitbyte_t     pu_sb;      /**< Schaltstatus der Pumpe                         */
} hk_out_t;

/**
 * @brief Definition der Komponentenklasse der Heizkoerperheizung
 */
typedef struct hk_class_s {
    reg_class_t reg;
    hk_param_t  p;
//    hk_in_t     i;
//    hk_out_t    o;
} hk_class_t;

/* <Typen/> */

/* <Prototypen> */
void hk_Init( hk_class_t *self );
void hk_Run( hk_class_t *self );
void hk_WriteInp(       hk_class_t  *self,
                  const float        tau_mw,
                  const float        tau_avg,
                  const float        tvl_mw,
                  const abgesenkt_t  zustand,
                  const u8_t         partytime_flg );
/* <Prototypen/> */

#endif /* _HK_H_ */

