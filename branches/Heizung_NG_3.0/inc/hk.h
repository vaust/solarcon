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

#ifndef _HK_H_
#define _HK_H_

#include "reg.h"

/* <Typen> */
typedef struct hk_param_s {
    float tvl_absenk;
    float tvl_steigung;
    float tvl_niveau;
    float tvl_min;
    float tvl_max;
    float at_start;
    float frostschutz;
    float tr_sw;
} hk_param_t;

typedef struct hk_in_s {
    float        tau_mw;
    float        tau_avg;
    float        tvl_mw;
    abgesenkt_t  zustand;
    u8_t         partytime_flg;
} hk_in_t;

typedef struct hk_out_s {
    float            tvl_sw;
    float            mv_y;
    do_bitbyte_t     pu_sb;
} hk_out_t;

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

