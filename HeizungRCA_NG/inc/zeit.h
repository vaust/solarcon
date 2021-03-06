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

#ifndef _ZEIT_H_
#define _ZEIT_H_

#include "gen_types.h"

/* <Makros> */
#define WOCHENZEIT(D, H, M)     ((M)+60*((H)+24*(D))) /**< Wochentag, Stunde und Minute in Minuten umrechnen */
#define TAGESZEIT(H, M)         ((M)+60*(H))          /**< Tageszeit in Minuten                              */
#define JAHRESTAG(M, T)         ((T)+32*(M))          /**< Feiertagsdatum in eindeutige Zahl von Tagen umr.  */

#ifdef __WAGO__
    #define ZEITPROGRAMMDATEI       "/home/wochenzeitprogramm.ini"
#else
    #define ZEITPROGRAMMDATEI       "wochenzeitprogramm.ini"
#endif
/* </Makros> */

/* <Konstanten> */
#define ZEIT_SCHALTSTATES_MAX  16
#define FEIERTAGE_MAX          16
/* </Konstanten> */

/* <Typen> */
typedef struct zeit_Betriebszustand_s {
    abgesenkt_t   HK_Zustand;           /**< HK-Heizkreis Zeitprogramm normal / abgesenkt / abgeschaltet */
    abgesenkt_t   FB_Zustand;           /**< Zustand Fussbodenheizung */
    ein_aus_t     Zirk_Zustand;         /**< Einschaltzustand Zirkulationspumpe */
    freigabe_t    SP1_Freigabe;         /**< Freigabe des Speichers 1 ueber Kessel */
    freigabe_t    SP2_Freigabe;         /**< Freigabe des Speichers 2 ueber Kessel */
    nutzzeit_t    Bootshausnutzung;     /**< Bootshausnutzung */
    nutzzeit_t    Duschzeit;            /**< wird gerade geduscht ? */
} zeit_Betriebszustand_t;

typedef struct zeit_event_s {
    u8_t    sec_flg  :1;
    u8_t    min_flg  :1;
    u8_t    hour_flg :1;
    u8_t             :5;
} zeit_event_t;

typedef struct zeit_partytime_schalter_s {
    u8_t    partytime_flg;
    u16_t   party_restzeit_min;
    u8_t    alterwert;
} zeit_partytime_schalter_t;

typedef struct {
    zeit_partytime_schalter_t   all;
    zeit_partytime_schalter_t   ww;
} zeit_party_t;

typedef struct zeit_schaltzeiten_s {
    zeit_schaltpunkt_t Ein[ZEIT_SCHALTSTATES_MAX];
    zeit_schaltpunkt_t Aus[ZEIT_SCHALTSTATES_MAX];
    u8_t               states;
} zeit_schaltzeiten_t;
/* </Typen> */


/* <Variablen> */
/* <Globals> Sichtbar in zeit.c und telnet.c */
#undef PUBLIC
#ifdef _ZEIT_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

PUBLIC zeit_schaltzeiten_t HK_Schaltzeiten;        /**< Zeitprogramm_Heizkoerperheizkreis         */
PUBLIC zeit_schaltzeiten_t FB_Schaltzeiten;        /**< Zeitprogramm Fussbodenheizung             */
PUBLIC zeit_schaltzeiten_t ZIRK_Schaltzeiten;      /**< Zeitprogramm Warmwasser Zirkulationspumpe */
PUBLIC zeit_schaltzeiten_t DUSCH_Schaltzeiten;     /**< Zeitprogramm Duschzeiten                  */

PUBLIC int                 zeit_hour_offset;

PUBLIC zeit_schaltpunkt_t  Feiertag[FEIERTAGE_MAX];
PUBLIC u8_t                feiertage_anzahl;

/* </Variablen> */


/* <Prototypen> */
void zeit_Init( zeit_Betriebszustand_t * const absenkung,
                zeit_event_t           * const schedule   );

void zeit_Run( zeit_Betriebszustand_t * const absenkung,
               zeit_event_t           * const schedule   );

/* \brief Hilfsfunktion um in Telnet die aktuelle Softwarezeit anzuzeigen.
 * Hilfreich wegen des Bugs in der ucLinux Implementierung  von localtime().
 */
void zeit_getLocaltime( s16_t * const wday,
                        s16_t * const hour,
                        s16_t * const min,
                        s16_t * const sec );
/* </Prototypen> */


/** TESTCODE */
#ifdef __TEST__
void zeit_TEST_Schaltzeiten( void );
#endif /* __TEST__ */

#endif /* _ZEIT_H_ */

