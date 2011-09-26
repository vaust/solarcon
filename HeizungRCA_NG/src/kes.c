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

#define _KES_C_

#include "gen_types.h"
#include "param_v2.h"
#include "kes.h"

void kes_Init( kes_class_t *self )
{
    self->p.sp_dt_sw     = param.kes.sp_dt_sw;
    self->p.ww_tww_sw    = param.ww.tww_sw;

    /* Ausgaenge initialisieren: (notwendig wg. undefinierten Zustands in Hystereseschleife zum Programmstart */
    self->o.pu_sp1_sb = IO_AUS;
    self->o.pu_sp2_sb = IO_AUS;
}
/**
 * \brief Speichersolltemperaturen berechnen, Speicherpumpen ansteuern
 * und Kesselsollvorlauftemperatur bestimmen.
 *
 * \param self Pointer auf Instanz der Klasse kes_class_t
 */
void kes_Run( kes_class_t *self )
{
    /* Speicher 1 = Warmwasser und Heizkoerper  
       Speicher 2 = Fussbodenheizung            */

    /* Berechne Solltemperatur Speicher 1: */
    if( (self->i.duschzeit == zJa) &&
        (self->i.hk_tvl_sw < (self->p.ww_tww_sw + self->p.sp_dt_sw)) )
        self->o.sp1_to_sw = self->p.ww_tww_sw + self->p.sp_dt_sw;
    else
        self->o.sp1_to_sw = self->i.hk_tvl_sw + self->p.sp_dt_sw;

    /* Berechne Solltemperatur Speicher 2: */
    self->o.sp2_to_sw = self->i.fb_tvl_sw + self->p.sp_dt_sw;

    /* Schaltkriterium fuer Speicherladepumpe 1 */
    if( self->i.sp1_to_mw < self->o.sp1_to_sw ) {
        self->o.tvl_sw_sp1 = self->o.sp1_to_sw + self->p.sp_dt_sw;
        /* Einschalten der Pumpe erst wenn Brenner ein oder die Vorlauftemperatur > Speichertemperatur */
        /* if( (self->i.br_bm == IO_EIN) || (self->i.tvl_mw > self->i.sp1_to_mw) ) */
        self->o.pu_sp1_sb = IO_EIN;
        /* Wenn Sp.-pumpe 1 ein, Sp.-pumpe 2 immer aus! */
        self->o.pu_sp2_sb = IO_AUS;
    }
    else if( self->i.sp1_to_mw >= (self->o.sp1_to_sw + self->p.sp_dt_sw) ) {
        self->o.tvl_sw_sp1 = 0.0;   /* Kessel AUS */
        self->o.pu_sp1_sb = IO_AUS;
    }
    
    /* Schaltkriterium fuer Speicherladepumpe 2 */
    if( self->o.pu_sp1_sb == IO_AUS ) {
    /* Sp.-pumpe 2 nur einschalten, wenn Sp.-pumpe 1 aus ist! */
        if( self->i.sp2_to_mw < self->o.sp2_to_sw ) {
            self->o.tvl_sw_sp2 = self->o.sp2_to_sw + self->p.sp_dt_sw;
            /* Einschalten der Pumpe erst wenn Brenner ein oder die Vorlauftemperatur > Speichertemperatur */
            /* if( (self->i.br_bm == IO_EIN) || (self->i.tvl_mw > self->i.sp2_to_mw) ) */
            self->o.pu_sp2_sb = IO_EIN;
        }
        else if( self->i.sp2_to_mw >= (self->o.sp2_to_sw + self->p.sp_dt_sw/2.0) ) {
            self->o.tvl_sw_sp2 = 0.0;  /* Kessel AUS */
            self->o.pu_sp2_sb = IO_AUS;
        }
    }
    else /* if( KES_PU_SP1_SB == IO_EIN ) */ {
        self->o.tvl_sw_sp2 = 0.0;  /* Kessel AUS */
        self->o.pu_sp2_sb = IO_AUS;
    }

    /* Notfall in dem Sp.-pumpe 2 immer laufen soll: */
    /* if( self->i.sp2_to_mw < (self->i.fb_tvl_sw - self->p.sp_dt_sw) ) */
    if( self->i.fb_prim_mv_y > 95.0 ) {
        if( self->i.br_bm == IO_EIN ) self->o.pu_sp2_sb = IO_EIN;
    }
    
    /* Sollwertvorgabe fuer den Kessel:
     * %-Zahl entspricht Vorlauftemperatur in °C
     * 100% entspr. 100°C
     * 10%  entpsr.  10°C
     * Werte kleiner 10%: Kessel ist abgeschaltet
     */

    if( self->o.tvl_sw_sp1 >= self->o.tvl_sw_sp2 )
        self->o.tvl_sw = self->o.tvl_sw_sp1;
    else 
        self->o.tvl_sw = self->o.tvl_sw_sp2;
}

void kes_WriteInp(       kes_class_t   *self,
                   const float         sp1_to_mw,
                   const float         sp2_to_mw,
                   const float         tvl_mw,
                   const u32_t         gz_mw,
                   const float         hk_tvl_sw,
                   const float         fb_tvl_sw,
                   const float         fb_prim_mv_y,
                   const nutzzeit_t    duschzeit,
                   const di_bitbyte_t  br_bm      )
{
    self->i.sp1_to_mw    = sp1_to_mw;
    self->i.sp2_to_mw    = sp2_to_mw;
    self->i.tvl_mw       = tvl_mw;
    self->i.gz_mw        = gz_mw;
    self->i.hk_tvl_sw    = hk_tvl_sw;
    self->i.fb_tvl_sw    = fb_tvl_sw;
    self->i.fb_prim_mv_y = fb_prim_mv_y;
    self->i.duschzeit    = duschzeit;
    self->i.br_bm        = br_bm;
}
