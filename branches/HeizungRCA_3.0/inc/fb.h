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
 * @file fb.h
 * @brief Interface fuer die Fussbodenheizkreiskomponente.
 */

#ifndef _FB_H_
#define _FB_H_

#include "gen_types.h"
#include "reg.h"

/* <Typen> */
/**
 * @brief Zusammenfassung der Fussbodenheizungsparameter
 */
typedef struct fb_param_s {
    float tvl_absenk;   /**< Nachtabsenkung in Grad C             */
    float tvl_steigung; /**< Heizkurvensteigung                   */
    float tvl_niveau;   /**< Heizkurven Parallelverschiebung      */
    float tvl_min;      /**< min. Vorlauftemperatur in Grad C     */
    float tvl_max;      /**< max. Vorlauftemperatur in Grad C     */
    float at_start;     /**< Aussentemperatur ab der geheizt wird */
    float frostschutz;  /**< Frostschutztemperatur in Grad C      */
    float tr_sw;        /**< Raumtemperatursollwert in Grad C     */
} fb_param_t;

/**
 * @brief Zusammenfassung der Eingangsgroessen der Fussbodenheizung
 */
typedef struct fb_in_s {
    float       tau_mw;           /**< Messwert der Aussentemperatur                            */
    float       tau_avg;          /**< gleitender Mittelwert der AT ueber 36h                   */
    float       sek_tvl_mw;       /**< Vorlauftemperatur auf der Sek.-seite des Waermetauschers */
    abgesenkt_t zustand;          /**< Absenkungsstatus der Fussbodenheizung                    */
    u8_t        partytime_flg;    /**< Partyzeitanzeige                                         */
} fb_in_t;

/**
 * @brief Zusammenfassung der Ausgangsgroessen der Fussbodenheizung
 */
typedef struct fb_out_s {
    float            tvl_sw;      /**< berechneter Vorlauftemperatursollwert          */
    float            prim_mv_y;   /**< dazu notwendige Mischventilstellung in Prozent */
    do_bitbyte_t     prim_pu_sb;  /**< Schaltstatus der Primaerpumpe                  */
    do_bitbyte_t     sek_pu_sb;   /**< Schaltstatus der Sekundaerpumpe                */
} fb_out_t;
/* <Typen/> */

/**
 * @brief Datentypen fuer die Interfacefunktionen
 */
typedef std_ret_t (*fb_in_Read_t)(fb_in_t *);
typedef std_ret_t (*fb_out_Write_t)(fb_out_t *);

/**
 * @brief Definition der Komponentenklasse der Fussbodenheizung
 */
typedef struct fb_class_s {
    reg_class_t 	reg;
    fb_param_t  	p;
	fb_in_Read_t	iRead;
	fb_out_Write_t	oWrite;
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

