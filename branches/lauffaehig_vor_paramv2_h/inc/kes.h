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

#ifndef _KES_H_
#define _KES_H_

#include "gen_types.h"

/* <Typen> */
typedef struct kes_param_s {
    float sp_dt_sw;                 /**< Globaler Wert div 2 !! */
    float ww_tww_sw;
} kes_param_t;

typedef struct kes_in_s {
    float        sp1_to_mw;
    float        sp2_to_mw;
    float        tvl_mw;
    u32_t        gz_mw;         /**< Gaszaehlerstand (noch nicht in Verwendung */
    float        hk_tvl_sw;     
    float        fb_tvl_sw;
    float        fb_prim_mv_y;  /**< Fussbodenheizung Mischventil Ausgang */
    nutzzeit_t   duschzeit;
    di_bitbyte_t br_bm;
} kes_in_t;

typedef struct kes_out_s {
    float sp1_to_sw;            /**< Sollwert fuer obere Speichertemperatur Speicher 1 */
    float sp2_to_sw;            /**< Sollwert fuer obere Speichertemperatur Speicher 2 */
    float tvl_sw_sp1;           /**< Kesselvorlaufsollwert fuer Speicher 1 nur zur Info und Debugging */
    float tvl_sw_sp2;           /**< Kesselvorlaufsollwert fuer Speicher 1 nur zur Info und Debugging */
    float tvl_sw;               /**< eigentlicher Kesselvorlaufsollwert (Maximum aus tvl_sw_sp1 und tvl_sw_sp2 */
    do_bitbyte_t pu_sp1_sb;     /**< Pumpen Relais Speicher Pumpe 1 */
    do_bitbyte_t pu_sp2_sb;     /**< Pumpen Relais Speicher Pumpe 2 */
} kes_out_t;

typedef struct kes_class_s {
    kes_param_t p;
    kes_in_t    i;
    kes_out_t   o;
} kes_class_t;

/* <Typen/> */

/* <Prototypen> */
void kes_Init( kes_class_t *self );
void kes_Run( kes_class_t *self );
void kes_WriteInp(       kes_class_t  *self,
                   const float         sp1_to_mw,
                   const float         sp2_to_mw,
                   const float         tvl_mw,
                   const u32_t         gz_mw,
                   const float         hk_tvl_sw,
                   const float         fb_tvl_sw,
                   const float         fb_prim_mv_y,
                   const nutzzeit_t    duschzeit,
                   const di_bitbyte_t  br_bm         );
/* <Prototypen/> */

#endif /* _KES_H_ */

