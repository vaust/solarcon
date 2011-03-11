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

#ifndef _CNTRL_H_
#define _CNTRL_H_

#include "reg.h"
#include "gen_types.h"

#include "zeit.h"
#include "task.h"
#include "sol.h"
#include "fb.h"
#include "hk.h"
#include "ww.h"
#include "kes.h"
#include "err.h"
// #include <time.h>   /**< Fuer Uptime Funktionalitaet */

/**
 * @brief Zusammenfassung der Modul Aktiv Flags der einzelnen Tasks
 */
typedef struct cntrl_enable_modul_s {
    u16_t sol_aktiv       : 1;  /**< Statusbit Solarkollektor aktiv             */
    u16_t fb_aktiv        : 1;  /**< Statusbit Fussbodenheizung aktiv           */
    u16_t hk_aktiv        : 1;  /**< Statusbit Heizkoerperheizkreis aktiv       */
    u16_t ww_aktiv        : 1;  /**< Statusbit Warmwassersteuerung aktiv        */
    u16_t kes_aktiv       : 1;  /**< Statusbit Kesselsteuerung aktiv            */
    u16_t err_aktiv       : 1;  /**< Statusbit Sammelstoermeldung aktiv         */
    u16_t inp_sol_aktiv   : 1;  /**< Statusbit Solar-Eingabe aktiv              */
    u16_t inp_fb_aktiv    : 1;  /**< Statusbit Fussbodenheizung-Eingabe aktiv   */
    u16_t inp_hk_aktiv    : 1;  /**< Statusbit Heizkoerper-Eingabe aktiv        */
    u16_t inp_ww_aktiv    : 1;  /**< Statusbit Warmwasser-Eingabe aktiv         */
    u16_t inp_kes_aktiv   : 1;  /**< Statusbit Kessel-Eingabe aktiv             */
    u16_t inp_err_aktiv   : 1;  /**< Statusbit Sammelstoermeldung Eingabe aktiv */
} cntrl_enable_modul_t;

/* <Globals> Sichtbar in cntrl.c und telnet.c */
#undef PUBLIC
#ifdef _CNTRL_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

/** @brief Instanz der Aktiv Flags */
PUBLIC cntrl_enable_modul_t    cntrl_mdl_aktiv;

/** \brief Variablen fuer Zeit */
PUBLIC zeit_Betriebszustand_t  cntrl_zeit_absenkung;
PUBLIC zeit_event_t            cntrl_zeit_event;
PUBLIC zeit_party_t            cntrl_zeit_party;

/** \brief Mittelwertbildung fuer Aussentemperatur */
PUBLIC task_tau_t          cntrl_tau;

/** \brief Instanz des Solarkollektorheizkreises */
PUBLIC sol_class_t         cntrl_sol;

/** \brief Instanz der Fussbodenheizung */
PUBLIC fb_class_t          cntrl_fb;

/** \brief Instanz des Heizkoerperheizkreises */
PUBLIC hk_class_t          cntrl_hk;

/** \brief Instanz des Warmwasserheizkreises */
PUBLIC ww_class_t          cntrl_ww;

/** \brief Instanz des Kesselkreises */
PUBLIC kes_class_t         cntrl_kes;

/** \brief Instanz einer Stoermeldung */
PUBLIC err_class_t         cntrl_err;

/** @brief DEBUG Variablen */
PUBLIC u32_t               cntrl_cnt;
PUBLIC s16_t               cntrl_TaskFlag_cnt;
// PUBLIC time_t              cntrl_startTime;
// PUBLIC time_t              cntrl_currentTime;

/** @brief globales Schedulerwarteflag */
PUBLIC u8_t                cntrl_TaskFlag;

/** @brief globaler Heart Beat */
PUBLIC u8_t		           cntrl_Heartbeat;

/** @brief Stoerungslampe */
PUBLIC u8_t		           cntrl_Stoerungslampe;

/* Prototypen */
void cntrl_open( void );
void cntrl_run( int sig );
void cntrl_close( void );

#endif /* _CNTRL_H_ */

