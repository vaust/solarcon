#ifndef _ZEIT_H_
#define _ZEIT_H_

#include "gen_types.h"

/* <Typen> */
typedef struct {
    abgesenkt_t   HK_Zustand;           /* HK-Heizkreis Zeitprogramm normal / abgesenkt / abgeschaltet */
    abgesenkt_t   FB_Zustand;           /* Zustand Fußbodenheizung */
    ein_aus_t     Zirk_Zustand;         /* Einschaltzustand Zirkulationspumpe */
    freigabe_t    SP1_Freigabe;         /* Freigabe des Speichers 1 über Kessel */
    freigabe_t    SP2_Freigabe;         /* Freigabe des Speichers 2 über Kessel */
    nutzzeit_t    Bootshausnutzung;     /* Bootshausnutzung */
    nutzzeit_t    Duschzeit;            /* wird gerade geduscht ? */
} zeit_Betriebszustand_t;

typedef struct {
    u8_t    sec_flg  :1;
    u8_t    min_flg  :1;
    u8_t    hour_flg :1;
    u8_t             :5;
} zeit_event_t;

typedef struct {
    u8_t    all_partytime_flg;
    u8_t    ww_partytime_flg;
    u16_t   all_party_restzeit_min;
    u16_t   ww_party_restzeit_min;
} zeit_party_t;

/* <Typen/> */

/* <Makros> */
#define WOCHENZEIT(D, H, M) 	((M)+60*((H)+24*(D))) /* Wochentag, Stunde und Minute in Minuten umrechnen */
#define TAGESZEIT(H, M) 		((M)+60*(H))          /* Tageszeit in Minuten                              */

#define ZEITPROGRAMMDATEI       "wochenzeitprogramm.ini"
/* <Makros/> */

/* <Variablen> */
#ifdef _ZEIT_C_
/* Zeitprogramm_Heizkörperheizkreis   */
#define HK_STATES_MAX 10
zeit_schaltpunkt_t HK_Ein_Schaltzeiten[HK_STATES_MAX];
zeit_schaltpunkt_t HK_Aus_Schaltzeiten[HK_STATES_MAX];

/* Zeitprogramm Fußbodenheizung       */
#define FB_STATES_MAX 10
zeit_schaltpunkt_t FB_Ein_Schaltzeiten[FB_STATES_MAX];
zeit_schaltpunkt_t FB_Aus_Schaltzeiten[FB_STATES_MAX];

/* Zeitprogramm Warmwasser Zirkulationspumpe */
#define ZIRK_STATES_MAX 10
zeit_schaltpunkt_t ZIRK_Ein_Schaltzeiten[ZIRK_STATES_MAX];
zeit_schaltpunkt_t ZIRK_Aus_Schaltzeiten[ZIRK_STATES_MAX];

/* Duschzeiten */
#define DUSCH_STATES_MAX 10
zeit_schaltpunkt_t DUSCH_Ein_Schaltzeiten[DUSCH_STATES_MAX];
zeit_schaltpunkt_t DUSCH_Aus_Schaltzeiten[DUSCH_STATES_MAX];

/* Variablen für Anzahl der Schaltpunkte der einzelnen Zeitprogramme */
u8_t    hk_states;
u8_t    fb_states;
u8_t    zirk_states;
u8_t    sp1_states;
u8_t    sp2_states;
u8_t    haus_states;
u8_t    dusch_states;
#endif /* _ZEIT_C_ */

#undef PUBLIC
#ifdef _ZEIT_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

PUBLIC zeit_party_t zeit_party;

/* <Variablen/> */

/* <Prototypen> */
int zeit_Init( zeit_Betriebszustand_t *absenkung, 
               zeit_event_t           *schedule );

void zeit_Run( zeit_Betriebszustand_t *absenkung, 
               zeit_event_t           *schedule );      

       
/*** TESTCODE ***/
#ifdef __TEST__
void zeit_TEST_Schaltzeiten( void );               
#endif /* __TEST__ */

#endif /* _ZEIT_H_ */

