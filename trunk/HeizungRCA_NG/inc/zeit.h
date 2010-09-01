#ifndef _ZEIT_H_
#define _ZEIT_H_

typedef long schaltpunkt_t;

#define WOCHENZEIT(D, H, M) 	((M)+60*((H)+24*(D))) /* Wochentag, Stunde und Minute in Minuten umrechnen */
#define TAGESZEIT(H, M) 		((M)+60*(H))          /* Tageszeit in Minuten                              */

#define ZEITPROGRAMMDATEI       "/home/wochenzeitprogramm.ini"

#ifdef _ZEIT_C_
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
/* nicht nach Außen sichtbar: nur über get Methode Ergebnis liefern!! */
/*** 
extern schaltpunkt_t HK_Ein_Schaltzeiten[];
extern schaltpunkt_t HK_Aus_Schaltzeiten[];

extern schaltpunkt_t FB_Ein_Schaltzeiten[];
extern schaltpunkt_t FB_Aus_Schaltzeiten[];

extern schaltpunkt_t ZIRK_Ein_Schaltzeiten[];
extern schaltpunkt_t ZIRK_Aus_Schaltzeiten[];

extern schaltpunkt_t DUSCH_Ein_Schaltzeiten[];
extern schaltpunkt_t DUSCH_Aus_Schaltzeiten[];
*/

#endif /* _ZEIT_C_ */

#endif /* _ZEIT_H_ */

