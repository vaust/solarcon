#ifndef ZEITPROGRAMM_H
#define ZEITPROGRAMM_H

#include <time.h>

typedef long schaltpunkt_t;

#define WOCHENZEIT(D, H, M) 	((M)+60*((H)+24*(D))) /* Wochentag, Stunde und Minute in Minuten umrechnen */
#define TAGESZEIT(H, M) 		((M)+60*(H))          /* Tageszeit in Minuten                              */

#ifdef _INIT_VAR_C_                            
/* Zeitprogramm_Heizkörperheizkreis   */
#define HK_STATES_MAX 4
schaltpunkt_t HK_Ein_Schaltzeiten[HK_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 
schaltpunkt_t HK_Aus_Schaltzeiten[HK_STATES_MAX] = { TAGESZEIT(12, 0), TAGESZEIT(22, 30) }; 
 
/* Zeitprogramm Fußbodenheizung       */
#define FB_STATES_MAX 4
schaltpunkt_t FB_Ein_Schaltzeiten[FB_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 
schaltpunkt_t FB_Aus_Schaltzeiten[FB_STATES_MAX] = { TAGESZEIT(12, 0), TAGESZEIT(22, 30) }; 

/* Zeitprogramm Warmwasser Zirkulationspumpe */
#define ZIRK_STATES_MAX 4
schaltpunkt_t ZIRK_Ein_Schaltzeiten[ZIRK_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 
schaltpunkt_t ZIRK_Aus_Schaltzeiten[ZIRK_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 

/* Zeitprogramm Speicher 1 */
#define SP1_STATES_MAX 4
schaltpunkt_t SP1_Ein_Schaltzeiten[SP1_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 
schaltpunkt_t SP1_Aus_Schaltzeiten[SP1_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 

/* Zeitprogramm Speicher 2 */
#define SP2_STATES_MAX 4
schaltpunkt_t SP2_Ein_Schaltzeiten[SP2_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 
schaltpunkt_t SP2_Aus_Schaltzeiten[SP2_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 

/* Nutzzeit Bootshaus */
#define HAUS_STATES_MAX 4
schaltpunkt_t HAUS_Ein_Schaltzeiten[HAUS_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 
schaltpunkt_t HAUS_Aus_Schaltzeiten[HAUS_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 

/* Duschzeiten */
#define DUSCH_STATES_MAX 4
schaltpunkt_t DUSCH_Ein_Schaltzeiten[DUSCH_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 
schaltpunkt_t DUSCH_Aus_Schaltzeiten[DUSCH_STATES_MAX] = { TAGESZEIT(6, 0), TAGESZEIT(13, 30) }; 
#else
extern schaltpunkt_t HK_Ein_Schaltzeiten[];
extern schaltpunkt_t HK_Aus_Schaltzeiten[];

extern schaltpunkt_t FB_Ein_Schaltzeiten[];
extern schaltpunkt_t FB_Aus_Schaltzeiten[];

extern schaltpunkt_t ZIRK_Ein_Schaltzeiten[];
extern schaltpunkt_t ZIRK_Aus_Schaltzeiten[];

extern schaltpunkt_t SP1_Ein_Schaltzeiten[];
extern schaltpunkt_t SP1_Aus_Schaltzeiten[];

extern schaltpunkt_t SP2_Ein_Schaltzeiten[];
extern schaltpunkt_t SP2_Aus_Schaltzeiten[];

extern schaltpunkt_t HAUS_Ein_Schaltzeiten[];
extern schaltpunkt_t HAUS_Aus_Schaltzeiten[];

extern schaltpunkt_t DUSCH_Ein_Schaltzeiten[];
extern schaltpunkt_t DUSCH_Aus_Schaltzeiten[];
#endif

#endif

