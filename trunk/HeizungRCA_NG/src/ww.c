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
 * \file ww.c
 * \brief Warmwassertemperaturregelung
 */
#define _WW_C_

#include "param.h"
#include "ww.h"



/** 
  * @brief Steuerung des Mischventils.
  *
  * Steuert die Stellung des Mischventils, das die Vorlauftemperatur
  * fuer den Warmwasser-Waermetauscher einstellt.
  * @param self Pointer auf Instanz der Klasse ww_class_t
  * @return kein
  */
static 
void ww_MV_Steuerung( ww_class_t *self )
{
    self->o.hzg_tvl_sw = self->p.tww_sw + self->p.kes_sp_dt_sw;
    if( self->i.sp1_to_mw > self->i.hzg_trl_mw ) {
        self->o.hzg_mv_y =
            (self->o.hzg_tvl_sw - self->i.hzg_trl_mw) * 100.0 /
                (self->i.sp1_to_mw - self->i.hzg_trl_mw)
          + (self->o.hzg_tvl_sw - self->i.hzg_tvl_mw) * self->p.mv_korr;
    }
    else {
        self->o.hzg_mv_y = MAX_Y_PCT;  /* dann stimmt was nicht -> Ventil voll auf */
    }
    self->o.hzg_mv_y = reg_Limit( self->o.hzg_mv_y, MIN_Y_PCT, MAX_Y_PCT );
}

/** 
  * @brief Verteilventilsteuerung.
  *
  * Verteilventil zwischen den Speichern 1 und 2 entsprechend der Speichertemperaturen
  * einstellen.
  * @param self Pointer auf Instanz der Klasse ww_class_t
  * @return kein
  */
static 
void ww_VV_Steuerung( ww_class_t *self )
{
    if( self->i.tau_avg        > self->p.at_start ) {
        if( self->i.hzg_trl_mw < self->i.sp2_tu_mw ) self->o.hzg_vv_sb = WW_VV_SP2;
        else                                         self->o.hzg_vv_sb = WW_VV_SP1;
    }
    else {
        if( self->i.hzg_trl_mw < self->i.hk_tvl_sw ) self->o.hzg_vv_sb = WW_VV_SP2;
        else                                         self->o.hzg_vv_sb = WW_VV_SP1;
    }
}

/** 
 * @brief Schwachlaststeuerung fuer wenige Duschbenutzer
 *
 * Die Schwachlaststeuerung soll eingreifen, wenn nur wenig Warmwasser gebraucht wird und 10%
 * Pumpenleistung fuer den Waermetauscher bereits zu viel Leistung bringt. Dann soll die Pumpe nach
 * einer definierten Zeit komplett abschalten.
 *
 * @param self Pointer auf Instanz der Klasse \ref ww_class_t
 * @return kein
 */
static 
void ww_Schwachlast_Steuerung( ww_class_t *self )
{
    /* Pumpe waehrend Duschbetrieb nicht abschalten, wegen Schwingung */
    if( self->o.hzg_pu_y < self->p.hzg_pu_y_min ) {
        self->schwachlastzeit ++;
        if( self->schwachlastzeit < self->p.schwachlastzeit_max ) {
            self->o.hzg_pu_y = self->p.hzg_pu_y_min;
        }
    } /* nach 30s ununterbrochener Schwachlast darf die Pumpe abschalten */
    else {
        self->schwachlastzeit = 0;
    }
}

/**
 * \brief Initialisierung der ww-Task.
 *
 * Die minimale Pumpenleistung wird bei 11% Stellgroesse erreicht. Unter 10% ist die
 * Pumpe aus. Der PI-Regler der fuer die wird hier mit initialisiert.
 *
 * \param self Pointer auf Instanz der Klasse ww_class_t
 * \return kein
 */
void ww_Init( ww_class_t *self, u16_t akt_wz )
{
    int n;

    self->p.kes_sp_dt_sw        = param_kes_sp_dt_sw;
    self->p.tww_sw              = param_ww_tww_sw;
    self->p.tww_min_sw          = 20.0;     /* todo Parameter anlegen */
    self->p.tww_hyst_sw         =  5.0;     /* todo Parameter anlegen */
    self->p.frostschutz         = param_all_frostschutz;
    self->p.at_start            = param_all_at_start;
    self->p.mv_korr             = param_ww_mv_korr;
    self->p.hzg_pu_y_min        = 11.0;     /* todo Parameter anlegen */
    self->p.schwachlastzeit_max = 300;      /* todo Parameter anlegen */
    self->p.schwachlast_aktiv   = zEin;
    self->schwachlastzeit       = 0;        /* Schwachlaststeuerung komponententauglich */

    reg_PI_Init( &(self->reg_pu), MSEC2SEC(param_sys_zykluszeit),
                                  param_ww_pu_reg_kp,
                                  param_ww_pu_reg_ki,
                                  param_ww_pu_reg_ap,
                                  MIN_Y_PCT,
                                  MAX_Y_PCT,
                                  &(self->o.hzg_pu_y),
                                  &(self->p.tww_sw),
                                  &(self->i.tww_mw)    );

    for( n=0; n<MAX_WZ_HISTORY; n++) {
        self->wz_history[n] = akt_wz;
    }
    self->ringzaehler = 0;
}

/**
 * \brief Berechne den Durchfluss an Warmwasser innerhalb von \ref MAX_WZ_HISTORY Aufrufen
 *
 * \param par_p Pointer auf Struktur mit Parametern
 * \return Durchfluss als Integerzahl
 *
 * Es wird die gleitende Differenz der Wasserzaehlerwerte ueber eine Zeitspanne von
 * \ref MAX_WZ_HISTORY x \ref ABTASTZEIT berechnet.
 * Dies entspricht bei MAX_WZ_HISTORY=60 und ABTASTZEIT=1.0sec dem durchschnittlichen Durchfluss der
 * letzten Minute in Zaehlereinheiten pro Minute.
 * Bei einem Impuls pro Liter entspricht dies der Einheit l/min.
 *
 * \todo Den Wasserzaehlerfaktor noch mit einbringen und damit den Rückgabewert auf l/min skalieren.
 */
static
s16_t ww_calcDurchfluss( ww_class_t *self )
{
    s32_t   wz_diff;

    wz_diff = (s32_t) self->i.wz_mw - (s32_t) self->wz_history[self->ringzaehler];
    if( self->i.wz_mw < self->wz_history[self->ringzaehler] ) {
        /* neuer Zaehlerwert kleiner als alter Wert: unplausibles Ereignis -> Zaehler ist uebergelaufen! */
        wz_diff = wz_diff+0x10000L;
    }
    self->wz_history[self->ringzaehler] = self->i.wz_mw;
    self->ringzaehler ++;
    if( self->ringzaehler >= MAX_WZ_HISTORY ) {
        self->ringzaehler = 0;
    }
    return ((s16_t) wz_diff);
}

/**
  * \brief Eigentlicher Warmwasser Task.
  *
  * \param par_p Pointer auf Struktur mit Parametern
  * \return kein  
  */
void ww_Run( ww_class_t *self )
{
    /*
    Anforderungen an WW Heizungspumpe:
    1. Wenn 1 Minute (Parameter anlegen) kein Wasser verbraucht wurde,
         dann Warmwasserheizungspumpe abschalten (geregelte Pumpe 0-10v)

    2. Die Pumpe muss laufen, wenn
         Außentemp. < -3°C UND WW-Temp. < 20°C (Gleiche Bedingungen, wie bei Zirkulationspumpe)
    -    Die Pumpe mit einer Hysterese solange laufen lassen, bis WW-Temp. >  25°C

    3.  2. Anforderung ist höher prior als 1. Anforderung
    */

    if( (self->i.tww_mw < self->p.tww_min_sw) && (self->i.tau_mw < self->p.frostschutz) ) {
        self->o.hzg_pu_sb = IO_EIN;
    }
    else if( self->i.tww_mw > (self->p.tww_min_sw + self->p.tww_hyst_sw) ) {
        if( ww_calcDurchfluss(self) != 0 ) {
            self->o.hzg_pu_sb = IO_EIN;
        }
        else {
            self->o.hzg_pu_sb = IO_AUS;
        }
    }

    // /* Wasserzaehler funktioniert noch nicht. Erst mal alter Stand: WW-Heizungspumpe immer ein */
    // self->o.hzg_pu_sb = IO_EIN;

    /* Zirkulationspumpe ansteuern */
    if( (self->i.zirkzustand == zEin) || (self->i.tau_mw < self->p.frostschutz) )
        self->o.zirk_pu_sb = IO_EIN;
    else
        self->o.zirk_pu_sb = IO_AUS;

    /* PI-Regler fuer WW Heizungspumpe */
    reg_PI_Run( &(self->reg_pu) );

    /* Berechnung von WW_HZG_MV_Y aus den Temperaturen von Speicher und Ruecklauf */
    ww_MV_Steuerung( self );

    /* Schwachlast Steuerung (ueber Telnet Interface ausschaltbar, default eingeschaltet) */
    if( self->p.schwachlast_aktiv == zEin ) {
        ww_Schwachlast_Steuerung( self );
    }

    /* Kriterium fuer Warmwasser Heizungsverteilventil */
    ww_VV_Steuerung( self );
}

/**
 * \brief Befuellen des Eingangsvektors.
 */
void ww_WriteInp(           ww_class_t *self,
                      const float       tww_mw,
                      const float       tau_mw,
                      const float       tau_avg,
                      const u16_t       wz_mw,
                      const float       hzg_tvl_mw,
                      const float       hzg_trl_mw,
                      const float       hk_tvl_sw,
                      const float       sp1_to_mw,
                      const float       sp2_tu_mw,
                      const ein_aus_t   zirkzustand,
                      const nutzzeit_t  duschzeit    )
{
    self->i.tww_mw       = tww_mw;
    self->i.tau_mw       = tau_mw;
    self->i.tau_avg      = tau_avg;
    self->i.wz_mw        = wz_mw;
    self->i.hzg_tvl_mw   = hzg_tvl_mw;
    self->i.hzg_trl_mw   = hzg_trl_mw;
    self->i.hk_tvl_sw    = hk_tvl_sw;
    self->i.sp1_to_mw    = sp1_to_mw;
    self->i.sp2_tu_mw    = sp2_tu_mw,
    self->i.zirkzustand  = zirkzustand;
    self->i.duschzeit    = duschzeit;
}




