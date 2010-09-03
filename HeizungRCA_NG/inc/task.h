#ifndef _TASK_H_
#define _TASK_H_

#include "gen_types.h"
#include "zeit.h"

/* <Typen> */
typedef struct {
    float t_1min_Intervall[60];
    float t_1h_mittel_36h_Intervall[MAX_ALL_Tau_mittel_Zeit];
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
PUBLIC u16_t     task_hk_Aufheizzeit;         /* Zeit von Heizbeginn bis zum Erreichen der Raumtemperatur in Minuten */
PUBLIC u32_t     task_ww_Zaehler;             /* Wasserzaehler */
PUBLIC u32_t     task_kes_Betriebszeit_sec;   /* Betriebszeitzähler Kessel in Sek. Applikation rechnet in Stunden um */
/* <Variablen/> */

/* <Prototypen> */
#ifdef _TASK_C_
static void task_partytime_schalter( const int          all_partydauer,
                                     const di_bitbyte_t all_party,
                                     const di_bitbyte_t ww_party,
                                           zeit_party_t *partytime );

static void task_minute( const di_bitbyte_t all_party,
                         const di_bitbyte_t ww_party,
                         const float        all_tau_mw,
                               zeit_party_t *partytime,
                               task_tau_t   *tau       );

static void task_stunde( task_tau_t *tau );
#endif

void task_Init( task_tau_t *tau,
                float all_tau_mw );

void task_Run( const int          all_partydauer,
               const di_bitbyte_t all_party,
               const di_bitbyte_t ww_party,
               const float        all_tau_mw,
                     task_tau_t   *tau,
                     zeit_event_t *schedule,
                     zeit_party_t *partytime );

/* <Prototypen/> */

#endif


