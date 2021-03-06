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
 * @file task.c
 * @brief Modul mit allen Methoden, die in einem bestimmten Zeitraster aufgerufen
 * werden muessen.
 *
 * @author Volker Stegmann
 */
  
#define _TASK_C_

#include "gen_types.h"
#include "param.h"
#include "zeit.h"
#include "task.h"

/* Versionstring */
const char* TASK_C_SVNVersion = "$Revision$";

static 
void task_partytime_schalter_lesen( const int                               all_partydauer,
                                    const di_bitbyte_t                      schaltzustand,
                                          zeit_partytime_schalter_t * const status          )
{
    if(    ( schaltzustand     >= IO_EIN ) 
        && ( status->alterwert == IO_AUS ) ) {
        status->partytime_flg = SET;   /* Ruecksetzen in task_test_partytime() */
        status->party_restzeit_min = all_partydauer;
    }
    status->alterwert = schaltzustand;
}

void task_Run( const int                  all_partydauer,
               const di_bitbyte_t         all_party,
               const di_bitbyte_t         ww_party,
               const float                all_tau_mw,
                     task_tau_t   * const tau,
                     zeit_event_t * const schedule,
                     zeit_party_t * const partytime       )
{
    task_partytime_schalter_lesen( all_partydauer, all_party, &partytime->all );
    task_partytime_schalter_lesen( all_partydauer, ww_party,  &partytime->ww  );   

    if( schedule->min_flg == SET ) {
        task_minute( all_party, ww_party, all_tau_mw, partytime, tau );
        schedule->min_flg = RESET;
    }
    if( schedule->hour_flg == SET ) {
        task_stunde( tau );
        schedule->hour_flg = RESET;
    }
}

static 
void task_test_partytime( const di_bitbyte_t                      schaltzustand,
                                zeit_partytime_schalter_t * const status         )
{
    /* Partyflag Ruecksetzzeitpunkt ermitteln */
    if(  status->party_restzeit_min > 0 ) {
        status->party_restzeit_min --;
    }
    else {
        status->partytime_flg = RESET;
    }
    /* Partyflag auf jeden Fall zuruecksetzen,
     * wenn Partyschalter wieder ausgeschaltet wird */
    if( schaltzustand == IO_AUS ) {
        status->partytime_flg = RESET;
    }
}

static 
void task_minute( const di_bitbyte_t         all_party,
                  const di_bitbyte_t         ww_party,
                  const float                all_tau_mw,
                        zeit_party_t * const partytime,
                        task_tau_t   * const tau        )
{
    static int  index = 0;

    /* Partyflags nach Ablauf der Nachlaufzeit oder manuellem Ruecksetzen loeschen */
    task_test_partytime( all_party, &partytime->all );
    task_test_partytime( ww_party,  &partytime->ww  );
    
    /* Berechnung des 1 Stundenmittelwerts der Aussentemperatur
     * aus 60 Werten alle Minuten */
    tau->t_1h_summe += all_tau_mw - tau->t_1min_Intervall[index];
    tau->t_1min_Intervall[index] = all_tau_mw;
    index ++;
    if( index > 59 )
        index = 0;
    tau->t_1h_mittel = tau->t_1h_summe/60.0;
 }

static 
void task_stunde( task_tau_t * const tau )
{
    static int index = 0;

    /* Berechnung des 36h (default) Mittelwerts der Aussentemperatur aus 36 1h Mittelwerten */
    tau->t_36h_summe += tau->t_1h_mittel - tau->t_1h_mittel_36h_Intervall[index];
    tau->t_1h_mittel_36h_Intervall[index] = tau->t_1h_mittel;
    index ++;
    if( index >= param_all_tau_mittel_zeit )
        index = 0;
    tau->t_36h_mittel = tau->t_36h_summe / param_all_tau_mittel_zeit;
}

void task_Init(       task_tau_t * const tau, 
                const float              all_tau_mw )
{
    int i;

    for( i=0; i<60; i++ ) 
        tau->t_1min_Intervall[i] = all_tau_mw;
    for( i=0; i<param_all_tau_mittel_zeit; i++ ) 
        tau->t_1h_mittel_36h_Intervall[i] = all_tau_mw;
    tau->t_1h_summe = all_tau_mw * 60;
    tau->t_1h_mittel = all_tau_mw;
    tau->t_36h_summe = all_tau_mw * param_all_tau_mittel_zeit;
    tau->t_36h_mittel = all_tau_mw;
}


