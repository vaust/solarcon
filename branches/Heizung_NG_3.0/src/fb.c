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
 * @file fb.c
 * @brief implementierung der Komponente fuer die Fussbodenheizungsregelung
 * @author Volker Stegmann
 */

#define _FB_C_

// #include "gen_types.h"
#include "fb.h"
#include "param.h"

/**
 * @brief Fussbodenheizung Initialisierung.
 *
 * @param self Pointer auf Instanz der Klasse fb_class
 * @return kein
 */
void fb_Init( fb_class_t *self )
{
    /* Vorgaben aus Parametrierung */
    self->p.frostschutz   = param.all.frostschutz;
    self->p.at_start      = param.all.at_start;
    self->p.tvl_absenk    = param.fb.tvl.absenk;
    self->p.tvl_max       = param.fb.tvl.max;
    self->p.tvl_min       = param.fb.tvl.min;
    self->p.tvl_niveau    = param.fb.tvl.niveau;
    self->p.tvl_steigung  = param.fb.tvl.steigung;
    self->p.tr_sw         = param.fb.tr_sw;

    reg_PI_Init( &(self->reg), MSEC2SEC(param.sys.zykluszeit),
                               param.fb.reg.kp,
                               param.fb.reg.ki,
                               param.fb.reg.ap,
                               MIN_Y_PCT,
                               MAX_Y_PCT,
                               &(self->o.prim_mv_y),
                               &(self->o.tvl_sw),
                               &(self->i.sek_tvl_mw)  );
    
    self->o.prim_pu_sb = IO_AUS;
    self->o.sek_pu_sb = IO_AUS;
}

/** \brief Fussbodenheizung Reglerfunktion
 *
 *  \param self Pointer auf Instanz der Klasse fb_class_t
 *  \return kein
 */
void fb_Run( fb_class_t *self )
{
    /* Vorlauftemperatursollwert im Floatformat berechnen  */
    self->o.tvl_sw =  (self->p.tr_sw - self->i.tau_mw) * self->p.tvl_steigung
                    + self->p.tr_sw + self->p.tvl_niveau;
    if( (self->i.zustand == zAbgesenkt) && (self->i.partytime_flg == RESET) ) {
        self->o.tvl_sw -= self->p.tvl_absenk;
    }
    self->o.tvl_sw = reg_Limit( self->o.tvl_sw, self->p.tvl_min, self->p.tvl_max );

    /* Mischventil PI-Regleralgorithmus mit Anti Windup */
    reg_PI_Run( &(self->reg) );

    if(   (self->i.tau_avg < self->p.at_start) && /* Die mittlere Aussentemperatur liegt unter der Betriebsschwelle */
          (self->o.tvl_sw  > self->p.tr_sw   )    /* Der berechnete Vorlauftemperatursollwert > Raumtemp.-sollwert  */
        ) {
        self->o.prim_pu_sb = IO_EIN;
        self->o.sek_pu_sb  = IO_EIN;
    }
    else if( self->i.tau_avg > (self->p.at_start+1.0) ) {  /* 1.0 ist Pumpenschalthysterese : todo Parameter! */
        self->o.prim_pu_sb = IO_AUS;
        self->o.sek_pu_sb  = IO_AUS;
    }
    else if( self->i.tau_mw < self->p.frostschutz ) {
        self->o.prim_pu_sb = IO_EIN;
        self->o.sek_pu_sb  = IO_EIN;
    }
}

/**
 * \brief Befuellen des Eingangsvektors
 */
void fb_WriteInp(       fb_class_t   *self,
                  const float        tau_mw,                  const float        tau_avg,                  const float        sek_tvl_mw,                  const abgesenkt_t  zustand,                  const u8_t         partytime_flg )
{
    self->i.tau_mw         = tau_mw;
    self->i.sek_tvl_mw     = sek_tvl_mw;
    self->i.tau_avg        = tau_avg;
    self->i.zustand        = zustand;
    self->i.partytime_flg  = partytime_flg;
}


