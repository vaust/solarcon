#include <stdio.h>
#include <time.h>

#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

void cntrl_zeitprogramm( void )
{
    time_t      aktZeit;
    struct tm   *aktZeitElemente_p;
    int         aktSec, aktMin, aktHour, aktWday, aktUhrzeit;
    int         i;
    static int  oldSec=0, oldMin=0, oldHour=0;

#ifdef __MODULTEST__
    printf( "Uhrzeit Wochentag: " ); scanf( "%d", &aktWday );
    printf( "Uhrzeit Stunde:    " ); scanf( "%d", &aktHour );
    printf( "Uhrzeit Minute:    " ); scanf( "%d", &aktMin );
#else
    time( &aktZeit );
    aktZeitElemente_p = localtime( &aktZeit );
    aktWday           = aktZeitElemente_p->tm_wday;
    aktHour           = aktZeitElemente_p->tm_hour;
    aktMin            = aktZeitElemente_p->tm_min;
    aktSec            = aktZeitElemente_p->tm_sec;
#endif

    aktUhrzeit  = WOCHENZEIT(aktWday, aktHour, aktMin);

    /* Flags fuer nur alle Sekunden, Minuten bzw. einmal pro Stunde auszufuehrende Tasks nach Ablauf setzen */
    if( oldSec != aktSec ) {
        schedule_sec_flg = SET;
    }
    oldSec = aktSec;

    if( oldMin != aktMin ) {
        schedule_min_flg = SET;
    }
    oldMin = aktMin;

    if( oldHour != aktHour ) {
        schedule_hour_flg = SET;
    }
    oldHour = aktHour;

    /* Betriebszustand Heizkoerperheizkreis */
    for( i=0; i<hk_states; i++ ) {
        if( aktUhrzeit <= HK_Aus_Schaltzeiten[i] ) break;
    }
    if( (aktUhrzeit > HK_Ein_Schaltzeiten[i]) && (aktUhrzeit <= HK_Aus_Schaltzeiten[i]) ) {
        z_HK_Zustand = zNormal;
    }
    else {
        z_HK_Zustand = zAbgesenkt;
    }

    /* Betriebszustand Fussbodenheizkreis */
    for( i=0; i<fb_states; i++ ) {
        if( aktUhrzeit <= FB_Aus_Schaltzeiten[i] ) break;
    }
    if( (aktUhrzeit > FB_Ein_Schaltzeiten[i]) && (aktUhrzeit <= FB_Aus_Schaltzeiten[i]) ) {
        z_FB_Zustand = zNormal;
    }
    else {
        z_FB_Zustand = zAbgesenkt;
    }

    /* Betriebszustand Zirkulationspumpe */
    for( i=0; i<zirk_states; i++ ) {
        if( aktUhrzeit <= ZIRK_Aus_Schaltzeiten[i] ) break;
    }
    if( (aktUhrzeit > ZIRK_Ein_Schaltzeiten[i]) && (aktUhrzeit <= ZIRK_Aus_Schaltzeiten[i]) ) {
        z_Zirk_Zustand = zEin;
    }
    else {
        z_Zirk_Zustand = zAus;
    }

    /* Duschzeit */
    for( i=0; i<dusch_states; i++ ) {
        if( aktUhrzeit <= DUSCH_Aus_Schaltzeiten[i] ) break;
    }
    if( (aktUhrzeit > DUSCH_Ein_Schaltzeiten[i]) && (aktUhrzeit <= DUSCH_Aus_Schaltzeiten[i]) ) {
        z_Duschzeit = zJa;
    }
    else {
        z_Duschzeit = zNein;
    }
} 
