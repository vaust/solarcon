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
PUBLIC u16_t     hk_Aufheizzeit;         /* Zeit von Heizbeginn bis zum Erreichen der Raumtemperatur in Minuten */
PUBLIC u32_t     ww_Zaehler;             /* Wasserzaehler */
PUBLIC u32_t     kes_Betriebszeit_sec;   /* Betriebszeitzähler Kessel in Sek. Applikation rechnet in Stunden um */

PUBLIC task_tau_t task_tau;              /* global Außentemperaturdaten */ 
/* <Variablen/> */

/* <Prototypen> */
void task_Init();
void task_main( void );

void task_minute( const di_bitbyte_t all_party, 
                  const di_bitbyte_t ww_party, 
                  const float        all_tau_mw,
                        zeit_party_t *partytime,
                        task_tau_t   *tau       );
void task_hour( task_tau_t *tau );
/* <Prototypen/> */

#endif


