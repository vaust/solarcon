#ifndef VARIABLEN_H
#define VARIABLEN_H

#undef _EXT_
#ifdef _MAIN_C_
    #define _EXT_
#else
    #define _EXT_ extern
#endif

_EXT_ float     all_Tau_mittel_f;       /* Mittlere Außentemperatur */
_EXT_ int       all_Partyzeit_i;        /* Fußbodenheizkreis Betriebszeitverlängerung aktiv */
_EXT_ int       sol_SP1_Vorrang_i;      /* Vorrang für Speicher 1 */
_EXT_ float     kes_Tvl_SW_Sp1_f;       /* Sollwert Speicher1 Kesselvorlauftemperatur in °C */
_EXT_ float     kes_Tvl_SW_Sp2_f;       /* Sollwert Speicher2 Kesselvorlauftemperatur in °C */
_EXT_ float     sol_SP1_To_SW_f;        /* neu von Andreas  04.04.2010 */
_EXT_ float     sol_SP2_To_SW_f;        /* neu von Andreas  04.04.2010 */
_EXT_ int       kes_BtrStd_i;           /* Betriebsstundenzähler Kessel */
_EXT_ float     hk_Tvl_SW_f;            /* Heizkörper Heizkreis Vorlaufsollwert in °C*/
_EXT_ float     hk_mv_y_f;              /* Heizkörper Mischventil Stellsignal */

_EXT_ float     fb_Tvl_SW_f;            /* Fußbodenheizkreis Vorlauftemperatursollwert in °C */
_EXT_ int       hk_Aufheizzeit_i;       /* Zeit von Heizbeginn bis zum Erreichen der Raumtemperatur in Minuten */
_EXT_ float     ww_HZG_Tvl_SW_f;        /* Heizungs-Vorlauftemperatur-Sollwert NICHT BENUTZT */
_EXT_ long      ww_Zaehler_l;           /* Zähler für Warmwasser */
_EXT_ int       ww_Durchfluss_i;        /* Durchfluss in Pulse / sec entspr. 1 liter/sec */

/* Variablen für Anzahl der Schaltpunkte der einzelnen Zeitprogramme */
_EXT_ int       hk_states;
_EXT_ int       fb_states;
_EXT_ int       zirk_states;
_EXT_ int       sp1_states;
_EXT_ int       sp2_states;
_EXT_ int       haus_states;
_EXT_ int       dusch_states;

/* Flags für zyklische Tasks */
#define SET     1
#define RESET   0
_EXT_ int       schedule_sec_flg;
_EXT_ int       schedule_min_flg;
_EXT_ int       schedule_hour_flg;

/* Partyflag */
_EXT_ int       partytime_flg;
_EXT_ int       minutes_since_party_pressed;
_EXT_ int       ww_partytime_flg;
_EXT_ int       ww_minutes_since_party_pressed;

/* Arrays für Berechnung des gleitenden Mittelwerts der Aussentemperatur */
_EXT_ float     Tau_1min_Intervall[60];
_EXT_ float     Tau_1h_mittel_36h_Intervall[MAX_ALL_Tau_mittel_Zeit];
_EXT_ float     Tau_1h_Summe_f;
_EXT_ float     Tau_1h_mittel_f;
_EXT_ float     Tau_36h_Summe_f;
_EXT_ float     Tau_36h_mittel_f;

/* Betriebszustände, die sich für die einzelnen Heizkreise aus dem Zeitprogramm ergeben */
typedef enum { zAbgesenkt, zNormal } zustand_hk_t;
typedef enum { zAus, zEin } ein_aus_t;
typedef enum { zGesperrt, zFreigegeben } freigabe_t;
typedef enum { zNein, zJa } nutzzeit_t;

_EXT_ zustand_hk_t  z_HK_Zustand;           /* HK-Heizkreis Zeitprogramm normal / abgesenkt / abgeschaltet */
_EXT_ zustand_hk_t  z_FB_Zustand;           /* Zustand Fußbodenheizung */
_EXT_ ein_aus_t     z_Zirk_Zustand;         /* Einschaltzustand Zirkulationspumpe */
_EXT_ freigabe_t    z_SP1_Freigabe;         /* Freigabe des Speichers 1 über Kessel */
_EXT_ freigabe_t    z_SP2_Freigabe;         /* Freigabe des Speichers 2 über Kessel */
_EXT_ nutzzeit_t    z_Bootshausnutzung;     /* Bootshausnutzung */
_EXT_ nutzzeit_t    z_Duschzeit;            /* wird gerade geduscht ? */

#endif
