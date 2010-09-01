#define _ZEIT_C_

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "gen_types.h"

#include "param.h"
#include "variablen.h"
#include "zeit.h"

int zeit_einlesen( int states_max, schaltpunkt_t schaltzeiten[])
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

int init_zeitprogramm( void )
{
	FILE 	*handle;
   	char	linestr[128];
 	char	*parameter, *value;
    int     wday, hour, min;
    int     i;

	handle = fopen( ZEITPROGRAMMDATEI, "r" );
	if( handle == NULL ) {
        /* todo */
        printf( "DEBUG: Datei wochenzeitprogramm.ini konnte nicht geöffnet werden!\n" );
    }
    else {
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
}

void cntrl_zeitprogramm( void )
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

    aktUhrzeit  = WOCHENZEIT(aktWday, aktHour, aktMin);

    /* Flags fuer nur alle Sekunden, Minuten bzw. einmal pro Stunde auszufuehrende Tasks nach Ablauf setzen */
    if( oldSec != aktSec ) 
        schedule_sec_flg = SET;
    oldSec = aktSec;

    if( oldMin != aktMin ) 
        schedule_min_flg = SET;
    oldMin = aktMin;

    if( oldHour != aktHour ) 
        schedule_hour_flg = SET;
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

// VERSCHIEBEN nach woanders !! 
void init_variables( void )
{
	int i;

	Tau_1h_Summe_f    = 0.0;
	Tau_1h_mittel_f   = 0.0;
	Tau_36h_Summe_f   = 0.0;
	Tau_36h_mittel_f  = 0.0;
	schedule_min_flg  = RESET;
	schedule_hour_flg = RESET;
	partytime_flg     = RESET;
    all_party_restzeit_min = 0;
    ww_party_restzeit_min  = 0;

	for( i=0; i<60; i++ ) {
		Tau_1min_Intervall[i] = 0.0;
	}
	for( i=0; i<MAX_ALL_Tau_mittel_Zeit; i++ ) {
		Tau_1h_mittel_36h_Intervall[i] = 0.0;
	}
}


