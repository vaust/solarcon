#ifndef _VARIABLEN_H_
#define _VARIABLEN_H_

#undef PUBLIC
#ifdef _MAIN_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

#include "gen_types.h"

PUBLIC float     all_Tau_mittel_f;       /* Mittlere Außentemperatur */
PUBLIC int       all_Partyzeit_i;        /* Fußbodenheizkreis Betriebszeitverlängerung aktiv */
PUBLIC int       sol_SP1_Vorrang_i;      /* Vorrang für Speicher 1 */
PUBLIC float     kes_Tvl_SW_Sp1_f;       /* Sollwert Speicher1 Kesselvorlauftemperatur in °C */
PUBLIC float     kes_Tvl_SW_Sp2_f;       /* Sollwert Speicher2 Kesselvorlauftemperatur in °C */
PUBLIC float     sol_SP1_To_SW_f;        /* neu von Andreas  04.04.2010 */
PUBLIC float     sol_SP2_To_SW_f;        /* neu von Andreas  04.04.2010 */
PUBLIC int       kes_BtrStd_i;           /* Betriebsstundenzähler Kessel */
PUBLIC float     hk_Tvl_SW_f;            /* Heizkörper Heizkreis Vorlaufsollwert in °C*/
PUBLIC float     hk_mv_y_f;              /* Heizkörper Mischventil Stellsignal */

PUBLIC float     fb_Tvl_SW_f;            /* Fußbodenheizkreis Vorlauftemperatursollwert in °C */
PUBLIC int       hk_Aufheizzeit_i;       /* Zeit von Heizbeginn bis zum Erreichen der Raumtemperatur in Minuten */
PUBLIC float     ww_HZG_Tvl_SW_f;        /* Heizungs-Vorlauftemperatur-Sollwert */
PUBLIC long      ww_Zaehler_l;           /* Zähler für Warmwasser */
PUBLIC int       ww_Durchfluss_i;        /* Durchfluss in Pulse / sec entspr. 1 liter/sec */

/* Variablen für Anzahl der Schaltpunkte der einzelnen Zeitprogramme */
PUBLIC int       hk_states;
PUBLIC int       fb_states;
PUBLIC int       zirk_states;
PUBLIC int       sp1_states;
PUBLIC int       sp2_states;
PUBLIC int       haus_states;
PUBLIC int       dusch_states;

/* Flags für zyklische Tasks */

PUBLIC int       schedule_sec_flg;
PUBLIC int       schedule_min_flg;
PUBLIC int       schedule_hour_flg;

/* Partyflag */
PUBLIC int       partytime_flg;
PUBLIC int       all_party_restzeit_min;
PUBLIC int       ww_partytime_flg;
PUBLIC int       ww_party_restzeit_min;

/* Arrays für Berechnung des gleitenden Mittelwerts der Aussentemperatur */
PUBLIC float     Tau_1min_Intervall[60];
PUBLIC float     Tau_1h_mittel_36h_Intervall[MAX_ALL_Tau_mittel_Zeit];
PUBLIC float     Tau_1h_Summe_f;
PUBLIC float     Tau_1h_mittel_f;
PUBLIC float     Tau_36h_Summe_f;
PUBLIC float     Tau_36h_mittel_f;

PUBLIC abgesenkt_t   z_HK_Zustand;           /* HK-Heizkreis Zeitprogramm normal / abgesenkt / abgeschaltet */
PUBLIC abgesenkt_t   z_FB_Zustand;           /* Zustand Fußbodenheizung */
PUBLIC ein_aus_t     z_Zirk_Zustand;         /* Einschaltzustand Zirkulationspumpe */
PUBLIC freigabe_t    z_SP1_Freigabe;         /* Freigabe des Speichers 1 über Kessel */
PUBLIC freigabe_t    z_SP2_Freigabe;         /* Freigabe des Speichers 2 über Kessel */
PUBLIC nutzzeit_t    z_Bootshausnutzung;     /* Bootshausnutzung */
PUBLIC nutzzeit_t    z_Duschzeit;            /* wird gerade geduscht ? */

#endif


