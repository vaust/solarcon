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
 * @file hk.c
 * @brief Implementierung der Komponente fuer die Heizkoerperheizkreisregelung
 * @author Volker Stegmann
 */

#define _HK_C_

#include "gen_types.h"
#include "param.h"
#include "hk.h"
#include "reg.h"

/* Versionstring */
const char* HK_C_SVNVersion = "$Revision$";

void hk_Init( hk_class_t *self )
{
    /* Vorgaben aus Parametrierung */
    self->p.frostschutz  = param_all_frostschutz;
    self->p.at_start     = param_all_at_start;
    self->p.tvl_absenk   = param_hk_tvl_absenk;
    self->p.tvl_max      = param_hk_tvl_max;
    self->p.tvl_min      = param_hk_tvl_min;
    self->p.tvl_niveau   = param_hk_tvl_niveau;
    self->p.tvl_steigung = param_hk_tvl_steigung;
    self->p.tr_sw        = param_hk_tr_sw;

    reg_PI_Init( &(self->reg), MSEC2SEC(param_sys_zykluszeit),
                               param_hk_reg_kp,
                               param_hk_reg_ki,
                               param_hk_reg_ap,
                               MIN_Y_PCT,
                               MAX_Y_PCT,
                               &(self->o.mv_y),
                               &(self->o.tvl_sw),
                               &(self->i.tvl_mw)  );
}

/**
 * \brief Regler fuer den Waermetauscher, der den Heizkoerperheizkreis beheizt.
 *
 * \param self Pointer auf Instanz der Klasse hk_class_t
 */
void hk_Run( hk_class_t *self )
{
    /* Vorlauftemperatursollwert im Floatformat berechnen   */
    self->o.tvl_sw = (self->p.tr_sw - self->i.tau_mw) * self->p.tvl_steigung + self->p.tr_sw + self->p.tvl_niveau;
    if( (self->i.zustand == zAbgesenkt) && (self->i.partytime_flg == RESET) ) {
        self->o.tvl_sw -= self->p.tvl_absenk;
    }

    self->o.tvl_sw = reg_Limit( self->o.tvl_sw, self->p.tvl_min, self->p.tvl_max );
    reg_PI_Run( &(self->reg) );

    if( (self->i.tau_avg < self->p.at_start) &&         /* mittlere AT unter Betriebsschwelle */
        (self->o.tvl_sw > 30.0             )    )       /* VL-Temp. ab der HK wirklich heizt  */
        self->o.pu_sb = IO_EIN;                         /* Heizkreis Pumpe einschalten */
    else if( self->i.tau_avg > self->p.at_start + 1.0 )
        self->o.pu_sb = IO_AUS;                         /* Heizkreis Pumpe ausschalten */
    else if (self->i.tau_mw < self->p.frostschutz )     /* AT unter Frostschutzmarke   */
        self->o.pu_sb = IO_EIN;                         /* Heizkreis Pumpe einschalten */
}

/**
 * \brief Befuellen des Eingangsvektors
 */
void hk_WriteInp(       hk_class_t  *self,
                  const float        tau_mw,
                  const float        tau_avg,
                  const float        tvl_mw,
                  const abgesenkt_t  zustand,
                  const u8_t         partytime_flg )
{
    self->i.tau_mw           = tau_mw;
    self->i.tau_avg          = tau_avg;
    self->i.tvl_mw           = tvl_mw;
    self->i.zustand          = zustand;
    self->i.partytime_flg    = partytime_flg;
}
