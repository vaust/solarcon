#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#undef PUBLIC
#ifdef _MAIN_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

#include "gen_types.h"
#include "zeit.h"

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

PUBLIC zeit_party_t zeit_party;

/* Arrays für Berechnung des gleitenden Mittelwerts der Aussentemperatur */
PUBLIC float     Tau_1min_Intervall[60];
PUBLIC float     Tau_1h_mittel_36h_Intervall[MAX_ALL_Tau_mittel_Zeit];
PUBLIC float     Tau_1h_Summe_f;
PUBLIC float     Tau_1h_mittel_f;
PUBLIC float     Tau_36h_Summe_f;
PUBLIC float     Tau_36h_mittel_f;

#endif


