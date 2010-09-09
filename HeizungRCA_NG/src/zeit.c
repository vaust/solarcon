#define _ZEIT_C_

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "gen_types.h"

#include "param.h"
// #include "variablen.h"
#include "zeit.h"

static int zeit_einlesen( int states_max, zeit_schaltpunkt_t schaltzeiten[] )
{   int     states = 0;
    int     wday, hour, min;
    char    *value;

    while( states < states_max )  {
        value = strtok( NULL, "-" );    /* Wochentagteilstring */
        if( value != NULL ) {
            sscanf( value, "%d", &wday );
            value = strtok( NULL, ":" );   /* Stundenteilstring */
            if( value != NULL ) {
                sscanf( value, "%d", &hour );
                value = strtok( NULL, ",;" );   /* Minutenteilstring */
                if( value != NULL ) {
                    sscanf( value, "%d", &min );
                    schaltzeiten[states] = WOCHENZEIT( wday, hour, min );
                    states ++;
                }
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
    return( states );
}

void zeit_Init( zeit_Betriebszustand_t *absenkung, zeit_event_t *schedule )
{
	FILE 	*handle;
   	char	linestr[128];
 	char	*parameter, *value;

	handle = fopen( ZEITPROGRAMMDATEI, "r" );
	if( handle == NULL ) {
        printf( "ZEIT.C: Datei wochenzeitprogramm.ini konnte nicht geöffnet werden!\n" );
    }
    else {
        printf( "ZEIT.C: wochenzeitprogramm.ini einlesen:\n" );
        while( !feof( handle ) )  {
            fgets( linestr, 127, handle );
            if( linestr[0] != '%' ) {
                parameter = strtok( linestr, "=" );
                if( strncmp( parameter, "HK_EIN", 6 ) == 0 ) {
                    hk_states = zeit_einlesen(HK_STATES_MAX, HK_Ein_Schaltzeiten);
                }
                else if( strncmp( parameter, "HK_AUS", 6 ) == 0 ) {
                    hk_states = zeit_einlesen(HK_STATES_MAX, HK_Aus_Schaltzeiten);
                }
                else if( strncmp( parameter, "FB_EIN", 6 ) == 0 ) {
                    fb_states = zeit_einlesen(FB_STATES_MAX, FB_Ein_Schaltzeiten);
                }
                else if( strncmp( parameter, "FB_AUS", 6 ) == 0 ) {
                    fb_states = zeit_einlesen(FB_STATES_MAX, FB_Aus_Schaltzeiten);
                }
                else if( strncmp( parameter, "ZIRK_EIN", 8 ) == 0 ) {
                    zirk_states = zeit_einlesen(ZIRK_STATES_MAX, ZIRK_Ein_Schaltzeiten);
                }
                else if( strncmp( parameter, "ZIRK_AUS", 8 ) == 0 ) {
                    zirk_states = zeit_einlesen(ZIRK_STATES_MAX, ZIRK_Aus_Schaltzeiten);
                }
                else if( strncmp( parameter, "DUSCH_EIN", 9 ) == 0 ) {
                    dusch_states = zeit_einlesen(DUSCH_STATES_MAX, DUSCH_Ein_Schaltzeiten);
                }
                else if( strncmp( parameter, "DUSCH_AUS", 9 ) == 0 ) {
                    dusch_states = zeit_einlesen(DUSCH_STATES_MAX, DUSCH_Aus_Schaltzeiten);
                }
                else if( strncmp( parameter, "HOUR_OFFSET", 11 ) == 0 ) {
                    value = strtok( NULL, ";" );
                    sscanf( value, "%d", &param_hour_offset );
                }
            }
        }
    }

    schedule->hour_flg = RESET;
    schedule->min_flg  = RESET;
    schedule->sec_flg  = RESET;

    absenkung->Bootshausnutzung = zJa;
    absenkung->Duschzeit        = zJa;
    absenkung->FB_Zustand       = zAbgesenkt;
    absenkung->HK_Zustand       = zAbgesenkt;
    absenkung->SP1_Freigabe     = zFreigegeben;
    absenkung->SP2_Freigabe     = zFreigegeben;
    absenkung->Zirk_Zustand     = zEin;
}

void zeit_Run( zeit_Betriebszustand_t *absenkung, zeit_event_t *schedule )
{
    time_t      aktZeit;
    struct tm   *aktZeitElemente_p;
    int         aktSec, aktMin, aktHour, aktWday, aktUhrzeit;
    int         i;
    static int  oldSec=0, oldMin=0, oldHour=0;

    time( &aktZeit );
    aktZeitElemente_p = localtime( &aktZeit );
    aktWday           = aktZeitElemente_p->tm_wday;
    aktHour           = aktZeitElemente_p->tm_hour + param_hour_offset;  // Workaround fuer Problem mit localtime()
    aktMin            = aktZeitElemente_p->tm_min;
    aktSec            = aktZeitElemente_p->tm_sec;

    aktUhrzeit = WOCHENZEIT(aktWday, aktHour, aktMin);

    /* Flags fuer nur alle Sekunden, Minuten bzw. einmal pro Stunde auszufuehrende Tasks nach Ablauf setzen */
    if( oldSec != aktSec )
        schedule->sec_flg = SET;
    oldSec = aktSec;

    if( oldMin != aktMin )
        schedule->min_flg = SET;
    oldMin = aktMin;

    if( oldHour != aktHour )
        schedule->hour_flg = SET;
    oldHour = aktHour;

    /* Betriebszustand Heizkoerperheizkreis */
    for( i=0; i<hk_states; i++ ) 
        if( aktUhrzeit <= HK_Aus_Schaltzeiten[i] ) break;

    if( aktUhrzeit > HK_Ein_Schaltzeiten[i] )  
        absenkung->HK_Zustand = zNormal;
    else 
        absenkung->HK_Zustand = zAbgesenkt;

    /* Betriebszustand Fussbodenheizkreis */
    for( i=0; i<fb_states; i++ ) 
        if( aktUhrzeit <= FB_Aus_Schaltzeiten[i] ) break;

    if( aktUhrzeit > FB_Ein_Schaltzeiten[i] ) 
        absenkung->FB_Zustand = zNormal;
    else 
        absenkung->FB_Zustand = zAbgesenkt;

    /* Betriebszustand Zirkulationspumpe */
    for( i=0; i<zirk_states; i++ ) 
        if( aktUhrzeit <= ZIRK_Aus_Schaltzeiten[i] ) break;
    
    if( aktUhrzeit > ZIRK_Ein_Schaltzeiten[i] ) 
        absenkung->Zirk_Zustand = zEin;
    else 
        absenkung->Zirk_Zustand = zAus;

    /* Duschzeit */
    for( i=0; i<dusch_states; i++ ) 
        if( aktUhrzeit <= DUSCH_Aus_Schaltzeiten[i] ) break;
        
    if( aktUhrzeit > DUSCH_Ein_Schaltzeiten[i] ) 
        absenkung->Duschzeit = zJa;
    else 
        absenkung->Duschzeit = zNein;
}

/** TESTCODE */
#ifdef __TEST__

void zeit_TEST_Schaltzeiten( void )
{
    int n;
    for( n=0; n<fb_states; n++ )
        printf( "ZEIT.C: TEST: FB_Ein_Schaltzeiten[%d] = %ld, FB_Aus_Schaltzeiten[%d] = %ld\n",
                n, FB_Ein_Schaltzeiten[n], n, FB_Aus_Schaltzeiten[n] );

    for( n=0; n<hk_states; n++ )
        printf( "ZEIT.C: TEST: HK_Ein_Schaltzeiten[%d] = %ld, HK_Aus_Schaltzeiten[%d] = %ld\n",
                n, HK_Ein_Schaltzeiten[n], n, HK_Aus_Schaltzeiten[n] );

    for( n=0; n<zirk_states; n++ )
        printf( "ZEIT.C: TEST: ZIRK_Ein_Schaltzeiten[%d] = %ld, ZIRK_Aus_Schaltzeiten[%d] = %ld\n",
                n, ZIRK_Ein_Schaltzeiten[n], n, ZIRK_Aus_Schaltzeiten[n] );

    for( n=0; n<dusch_states; n++ )
        printf( "ZEIT.C: TEST: DUSCH_Ein_Schaltzeiten[%d] = %ld, DUSCH_Aus_Schaltzeiten[%d] = %ld\n",
                n, FB_Ein_Schaltzeiten[n], n, FB_Aus_Schaltzeiten[n] );

    printf( "\n" );
}

#endif /* __TEST__ */


