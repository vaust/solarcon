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

#ifndef _FB_H_
#define _FB_H_

#include "gen_types.h"
#include "all_types.h"
#include "reg.h"

/* <Typen> */
/**
 * @brief Zusammenfassung der Fussbodenheizungsparameter
 */
typedef struct fb_param_s {
//    float tvl_absenk;   /**< Nachtabsenkung in Grad C         */
//    float tvl_steigung; /**< Heizkurvensteigung               */
//    float tvl_niveau;   /**< Heizkurven Parallelverschiebung  */
//    float tvl_min;
//    float tvl_max;      /**< max. Vorlauftemperatur in Grad C */
    all_tvl_t tvl;      /**
    float at_start;
    float frostschutz;  /**< Frostschutztemperatur in Grad C  */
    float tr_sw;        /**< Raumtemperatursollwert in Grad C */
} fb_param_t;

/**
 * @brief Zusammenfassung der Eingangsgroessen der Fussbodenheizung
 */
typedef struct fb_in_s {
    float       tau_mw;
    float       tau_avg;
    float       sek_tvl_mw;
    abgesenkt_t zustand;
    u8_t        partytime_flg;
} fb_in_t;

/**
 * @brief Zusammenfassung der Ausgangsgroessen der Fussbodenheizung
 */
typedef struct fb_out_s {
    float            tvl_sw;
    float            prim_mv_y;
    do_bitbyte_t     prim_pu_sb;
    do_bitbyte_t     sek_pu_sb;
} fb_out_t;
/* <Typen/> */

/**
 * @brief Definition der Komponentenklasse der Fussbodenheizung
 */
typedef struct fb_class_s {
    reg_class_t reg;
    fb_param_t  p;
    fb_in_t     i;
    fb_out_t    o;
} fb_class_t;

/* <Prototypen> */
void fb_Init( fb_class_t *self );
void fb_Run( fb_class_t *self );
void fb_WriteInp(       fb_class_t   *self,
                  const float        tau_mw,
                  const float        tau_avg,
                  const float        sek_tvl_mw,
                  const abgesenkt_t  zustand,
                  const u8_t         partytime_flg );
/* <Prototypen/> */

#endif /* _FB_H_ */

