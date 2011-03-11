/*
 *  SOLARCON Modular Solar Supported Home Heating Controller
 *  Copyright (C) 2011  Volker Stegmann
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/** \file Zeitini Datei einlesen und waehrend Laufzeit Absenkungen ermitteln
 *  \author Andreas und Volker Stegmann
 */
#define _ZEIT_C_

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "gen_types.h"
#include "param.h"
#include "zeit.h"


static
int zeit_einlesen( const int states_max, zeit_schaltpunkt_t schaltzeiten[] )
{
    int     states = 0;
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
                else {
                    break;
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

static
int zeit_feiertage_einlesen( const int max_feiertage, zeit_schaltpunkt_t feiertag[] )
{
    int     n = 0;
    int     monat, tag;
    char    *value;

    while( n < max_feiertage ) {
        value = strtok( NULL, "." );    /* Tagesteilstring */
        if( value != NULL ) {
            sscanf( value, "%d", &tag );
            value = strtok( NULL, ",;" );   /* Monatsteilstring */
            if( value != NULL ) {
                sscanf( value, "%d", &monat );
                feiertag[n] = JAHRESTAG( monat, tag );
                // printf( "ZEIT.C: Debug: Feiertag %d  Monat = %d Tag = %d\n", feiertag[n], monat, tag );
                n ++;
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
    return( n );
}


void zeit_Init( zeit_Betriebszustand_t * const absenkung,
                zeit_event_t           * const schedule   )
{
    FILE    *handle;
    char    linestr[128];
    char    *parameter, *value;

    zeit_hour_offset = 1; /* Default Wert fuer Zeitprogramm falls nicht in ini-Datei enthalten */
    
    handle = fopen( ZEITPROGRAMMDATEI, "r" );
    if( handle == NULL ) {
        printf( "ZEIT.C: Datei wochenzeitprogramm.ini konnte nicht geoeffnet werden!\n" );
    }
    else {
        printf( "ZEIT.C: wochenzeitprogramm.ini einlesen:\n" );
        while( !feof( handle ) )  {
            fgets( linestr, 127, handle );
            if( linestr[0] != '%' ) {
                parameter = strtok( linestr, "=" );
                if( strncmp( parameter, "HK_EIN", 6 ) == 0 ) {
                    HK_Schaltzeiten.states = zeit_einlesen( ZEIT_SCHALTSTATES_MAX, HK_Schaltzeiten.Ein );
                }
                else if( strncmp( parameter, "HK_AUS", 6 ) == 0 ) {
                    HK_Schaltzeiten.states = zeit_einlesen( ZEIT_SCHALTSTATES_MAX, HK_Schaltzeiten.Aus );
                }
                else if( strncmp( parameter, "FB_EIN", 6 ) == 0 ) {
                    FB_Schaltzeiten.states = zeit_einlesen( ZEIT_SCHALTSTATES_MAX, FB_Schaltzeiten.Ein );
                }
                else if( strncmp( parameter, "FB_AUS", 6 ) == 0 ) {
                    FB_Schaltzeiten.states = zeit_einlesen( ZEIT_SCHALTSTATES_MAX, FB_Schaltzeiten.Aus );
                }
                else if( strncmp( parameter, "ZIRK_EIN", 8 ) == 0 ) {
                    ZIRK_Schaltzeiten.states = zeit_einlesen( ZEIT_SCHALTSTATES_MAX, ZIRK_Schaltzeiten.Ein );
                }
                else if( strncmp( parameter, "ZIRK_AUS", 8 ) == 0 ) {
                    ZIRK_Schaltzeiten.states = zeit_einlesen( ZEIT_SCHALTSTATES_MAX, ZIRK_Schaltzeiten.Aus );
                }
                else if( strncmp( parameter, "DUSCH_EIN", 9 ) == 0 ) {
                    DUSCH_Schaltzeiten.states = zeit_einlesen( ZEIT_SCHALTSTATES_MAX, DUSCH_Schaltzeiten.Ein );
                }
                else if( strncmp( parameter, "DUSCH_AUS", 9 ) == 0 ) {
                    DUSCH_Schaltzeiten.states = zeit_einlesen( ZEIT_SCHALTSTATES_MAX, DUSCH_Schaltzeiten.Aus );
                }
                else if( strncmp( parameter, "HOUR_OFFSET", 11 ) == 0 ) {
                    value = strtok( NULL, ";" );
                    sscanf( value, "%d", &zeit_hour_offset );
                }
                else if( strncmp( parameter, "FEIERTAG", 8 ) == 0 ) {
                    feiertage_anzahl = zeit_feiertage_einlesen( FEIERTAGE_MAX, Feiertag );
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

void zeit_Run( zeit_Betriebszustand_t * const absenkung, 
               zeit_event_t           * const schedule   )
{
    time_t      aktZeit;
    struct tm   *aktZeitElemente_p;
    int         aktSec, aktMin, aktHour, aktWday, aktMon, aktMday;
    int         aktUhrzeit, aktJahrestag;
    int         i;
    static int  oldSec=0, oldMin=0, oldHour=0;

    time( &aktZeit );
    aktZeitElemente_p = localtime( &aktZeit );
    aktWday           = aktZeitElemente_p->tm_wday;
    aktHour           = aktZeitElemente_p->tm_hour + zeit_hour_offset;  // Workaround fuer Problem mit localtime()
    aktMin            = aktZeitElemente_p->tm_min;
    aktSec            = aktZeitElemente_p->tm_sec;
    aktMon            = aktZeitElemente_p->tm_mon + 1;  /* tm_mon  = [0,11] */
    aktMday           = aktZeitElemente_p->tm_mday;     /* tm_mday = [1,31] */

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

    aktJahrestag = JAHRESTAG(aktMon, aktMday);
    for( i=0; i<feiertage_anzahl; i++ ) {
        if( aktJahrestag == Feiertag[i] ) {
            aktWday = 0; /* Feiertage sind wie Sonntage zu behandeln! */
            break;
        }
    }
    aktUhrzeit   = WOCHENZEIT(aktWday, aktHour, aktMin);

    /* Betriebszustand Heizkoerperheizkreis */
    for( i=0; i<HK_Schaltzeiten.states; i++ )
        if( aktUhrzeit <= HK_Schaltzeiten.Aus[i] ) break;

    if( aktUhrzeit > HK_Schaltzeiten.Ein[i] )
        absenkung->HK_Zustand = zNormal;
    else 
        absenkung->HK_Zustand = zAbgesenkt;

    /* Betriebszustand Fussbodenheizkreis */
    for( i=0; i<FB_Schaltzeiten.states; i++ )
        if( aktUhrzeit <= FB_Schaltzeiten.Aus[i] ) break;

    if( aktUhrzeit > FB_Schaltzeiten.Ein[i] )
        absenkung->FB_Zustand = zNormal;
    else 
        absenkung->FB_Zustand = zAbgesenkt;

    /* Betriebszustand Zirkulationspumpe */
    for( i=0; i<ZIRK_Schaltzeiten.states; i++ )
        if( aktUhrzeit <= ZIRK_Schaltzeiten.Aus[i] ) break;
    
    if( aktUhrzeit > ZIRK_Schaltzeiten.Ein[i] )
        absenkung->Zirk_Zustand = zEin;
    else 
        absenkung->Zirk_Zustand = zAus;

    /* Duschzeit */
    for( i=0; i<DUSCH_Schaltzeiten.states; i++ )
        if( aktUhrzeit <= DUSCH_Schaltzeiten.Aus[i] ) break;
        
    if( aktUhrzeit > DUSCH_Schaltzeiten.Ein[i] )
        absenkung->Duschzeit = zJa;
    else 
        absenkung->Duschzeit = zNein;
}

/* \brief Hilfsfunktion um in Telnet die aktuelle Softwarezeit anzuzeigen.
 * Hilfreich wegen des Bugs in der ucLinux Implementierung  von localtime().
 */
void zeit_getLocaltime( s16_t * const wday,
                        s16_t * const hour,
                        s16_t * const min,
                        s16_t * const sec )
{
    time_t      aktZeit;
    struct tm   *aktZeitElemente_p;

    time( &aktZeit );
    aktZeitElemente_p = localtime( &aktZeit );
    *wday             = aktZeitElemente_p->tm_wday;
    *hour             = aktZeitElemente_p->tm_hour;
    *min              = aktZeitElemente_p->tm_min;
    *sec              = aktZeitElemente_p->tm_sec;
}


