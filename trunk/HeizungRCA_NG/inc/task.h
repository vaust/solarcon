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

#ifndef _TASK_H_
#define _TASK_H_


#include "gen_types.h"
#include "param.h"
#include "zeit.h"

/* <Typen> */
typedef struct task_tau_s {
    float t_1min_Intervall[60];                                 /**< Temperaturen der letzten Stunde im Minutenintervall */
    float t_1h_mittel_36h_Intervall[MAX_ALL_Tau_mittel_Zeit];   /**< Temperaturen der letzten 36h    im Stundenintervall */
    float t_1h_summe;
    float t_1h_mittel;
    float t_36h_summe;
    float t_36h_mittel;
} task_tau_t;
/* <Typen/> */

#undef PUBLIC
#ifdef _TASK_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

/* <Variablen> */
PUBLIC u16_t     task_hk_Aufheizzeit;         /**< Zeit von Heizbeginn bis zum Erreichen der Raumtemperatur in Minuten */
PUBLIC u32_t     task_ww_Zaehler;             /**< Wasserzaehler */
PUBLIC u32_t     task_kes_Betriebszeit_sec;   /**< Betriebszeitzähler Kessel in Sek. Applikation rechnet in Stunden um */
/* <Variablen/> */

/* <Prototypen> */
#ifdef _TASK_C_
static void task_partytime_schalter_lesen( const int                               all_partydauer,
                                           const di_bitbyte_t                      schaltzustand,
                                                 zeit_partytime_schalter_t * const status          );

static void task_test_partytime( const di_bitbyte_t                      schaltzustand,
                                       zeit_partytime_schalter_t * const status         );
                                           
static void task_minute( const di_bitbyte_t         all_party,
                         const di_bitbyte_t         ww_party,
                         const float                all_tau_mw,
                               zeit_party_t * const partytime,
                               task_tau_t   * const tau        );

static void task_stunde( task_tau_t * const tau );
#endif

void task_Init( task_tau_t *tau,
                float all_tau_mw );

void task_Run( const int                  all_partydauer,
               const di_bitbyte_t         all_party,
               const di_bitbyte_t         ww_party,
               const float                all_tau_mw,
                     task_tau_t   * const tau,
                     zeit_event_t * const schedule,
                     zeit_party_t * const partytime      );

/* <Prototypen/> */

#endif


