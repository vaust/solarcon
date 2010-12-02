#ifndef _ZEIT_H_
#define _ZEIT_H_

#include "gen_types.h"

/* <Typen> */
typedef struct {
    abgesenkt_t   HK_Zustand;           /* HK-Heizkreis Zeitprogramm normal / abgesenkt / abgeschaltet */
    abgesenkt_t   FB_Zustand;           /* Zustand Fu�bodenheizung */
    ein_aus_t     Zirk_Zustand;         /* Einschaltzustand Zirkulationspumpe */
    freigabe_t    SP1_Freigabe;         /* Freigabe des Speichers 1 �ber Kessel */
    freigabe_t    SP2_Freigabe;         /* Freigabe des Speichers 2 �ber Kessel */
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
    u8_t    partytime_flg;
    u16_t   party_restzeit_min;
    u8_t    alterwert;
} zeit_partytime_schalter_t;

typedef struct {
    zeit_partytime_schalter_t   all;
    zeit_partytime_schalter_t   ww;
} zeit_party_t;

/* <Typen/> */

/* <Makros> */
#define WOCHENZEIT(D, H, M)     ((M)+60*((H)+24*(D))) /* Wochentag, Stunde und Minute in Minuten umrechnen */
#define TAGESZEIT(H, M)         ((M)+60*(H))          /* Tageszeit in Minuten                              */

#ifdef __WAGO__
    #define ZEITPROGRAMMDATEI       "/home/wochenzeitprogramm.ini"
#else
    #define ZEITPROGRAMMDATEI       "wochenzeitprogramm.ini"
#endif
/* <Makros/> */

/* <Variablen> */
#ifdef _ZEIT_C_
/* Zeitprogramm_Heizkoerperheizkreis   */
#define HK_STATES_MAX 16
zeit_schaltpunkt_t HK_Ein_Schaltzeiten[HK_STATES_MAX];
zeit_schaltpunkt_t HK_Aus_Schaltzeiten[HK_STATES_MAX];

/* Zeitprogramm Fussbodenheizung       */
#define FB_STATES_MAX 16
zeit_schaltpunkt_t FB_Ein_Schaltzeiten[FB_STATES_MAX];
zeit_schaltpunkt_t FB_Aus_Schaltzeiten[FB_STATES_MAX];

/* Zeitprogramm Warmwasser Zirkulationspumpe */
#define ZIRK_STATES_MAX 16
zeit_schaltpunkt_t ZIRK_Ein_Schaltzeiten[ZIRK_STATES_MAX];
zeit_schaltpunkt_t ZIRK_Aus_Schaltzeiten[ZIRK_STATES_MAX];

/* Duschzeiten */
#define DUSCH_STATES_MAX 16
zeit_schaltpunkt_t DUSCH_Ein_Schaltzeiten[DUSCH_STATES_MAX];
zeit_schaltpunkt_t DUSCH_Aus_Schaltzeiten[DUSCH_STATES_MAX];

/* Variablen fuer Anzahl der Schaltpunkte der einzelnen Zeitprogramme */
u8_t    hk_states;
u8_t    fb_states;
u8_t    zirk_states;
u8_t    sp1_states;
u8_t    sp2_states;
u8_t    haus_states;
u8_t    dusch_states;

int zeit_hour_offset;
#else
#ifdef _TELNET_C_
extern zeit_schaltpunkt_t HK_Ein_Schaltzeiten[];
extern zeit_schaltpunkt_t HK_Aus_Schaltzeiten[];
extern zeit_schaltpunkt_t FB_Ein_Schaltzeiten[];
extern zeit_schaltpunkt_t FB_Aus_Schaltzeiten[];
extern zeit_schaltpunkt_t ZIRK_Ein_Schaltzeiten[];
extern zeit_schaltpunkt_t ZIRK_Aus_Schaltzeiten[];
extern zeit_schaltpunkt_t DUSCH_Ein_Schaltzeiten[];
extern zeit_schaltpunkt_t DUSCH_Aus_Schaltzeiten[];
extern u8_t    hk_states;
extern u8_t    fb_states;
extern u8_t    zirk_states;
extern u8_t    sp1_states;
extern u8_t    sp2_states;
extern u8_t    haus_states;
extern u8_t    dusch_states;
extern int     zeit_hour_offset;
#endif

#endif /* _ZEIT_C_ */

/* <Variablen/> */


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
/** TESTCODE */
#ifdef __TEST__
void zeit_TEST_Schaltzeiten( void );
#endif /* __TEST__ */

#endif /* _ZEIT_H_ */

