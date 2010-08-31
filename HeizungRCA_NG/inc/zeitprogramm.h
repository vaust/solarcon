#ifndef _ZEITPROGRAMM_H_
#define _ZEITPROGRAMM_H_

typedef long schaltpunkt_t;

#define WOCHENZEIT(D, H, M) 	((M)+60*((H)+24*(D))) /* Wochentag, Stunde und Minute in Minuten umrechnen */
#define TAGESZEIT(H, M) 		((M)+60*(H))          /* Tageszeit in Minuten                              */


#ifdef _INIT_C_
/* Zeitprogramm_Heizkörperheizkreis   */
#define HK_STATES_MAX 10
schaltpunkt_t HK_Ein_Schaltzeiten[HK_STATES_MAX];
schaltpunkt_t HK_Aus_Schaltzeiten[HK_STATES_MAX];

/* Zeitprogramm Fußbodenheizung       */
#define FB_STATES_MAX 10
schaltpunkt_t FB_Ein_Schaltzeiten[FB_STATES_MAX];
schaltpunkt_t FB_Aus_Schaltzeiten[FB_STATES_MAX];

/* Zeitprogramm Warmwasser Zirkulationspumpe */
#define ZIRK_STATES_MAX 10
schaltpunkt_t ZIRK_Ein_Schaltzeiten[ZIRK_STATES_MAX];
schaltpunkt_t ZIRK_Aus_Schaltzeiten[ZIRK_STATES_MAX];

/* Duschzeiten */
#define DUSCH_STATES_MAX 10
schaltpunkt_t DUSCH_Ein_Schaltzeiten[DUSCH_STATES_MAX];
schaltpunkt_t DUSCH_Aus_Schaltzeiten[DUSCH_STATES_MAX];
#else
extern schaltpunkt_t HK_Ein_Schaltzeiten[];
extern schaltpunkt_t HK_Aus_Schaltzeiten[];

extern schaltpunkt_t FB_Ein_Schaltzeiten[];
extern schaltpunkt_t FB_Aus_Schaltzeiten[];

extern schaltpunkt_t ZIRK_Ein_Schaltzeiten[];
extern schaltpunkt_t ZIRK_Aus_Schaltzeiten[];

extern schaltpunkt_t DUSCH_Ein_Schaltzeiten[];
extern schaltpunkt_t DUSCH_Aus_Schaltzeiten[];
#endif /* _INIT_C_ */

#endif /* _ZEITPROGRAMM_H_ */

