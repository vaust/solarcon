/* Debugeinstellungen */

//#define __LOGFILE__

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#ifdef __WAGO__
#include <asm/types.h>
#include "kbusapi.h"
#endif

#include <string.h>
#include <time.h>

#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* Prototypen */
void ProzentToAnalogOut( float scale ,ao_0_10V_t *ausgang );
void cntrl_initAverageTau( float currTau );
void cntrl_zeitprogramm( void );
void log_variables( FILE *fp );

/* Digitale Regler */
void cntrl_Solarbeheizung( void );
void cntrl_Speicher( void );
void cntrl_Kessel( void );
void cntrl_FB_Heizkreis( void );
void cntrl_HK_Heizkreis( void );
void cntrl_WW_Heizkreis( void );

void cntrl_task( void );
void cntrl_min_task( void );
void cntrl_hour_task( void );

/* externe Funktionsprototypen, die in diesem Modul verwendet werden  */
int init_parameters( void );
int init_zeitprogramm( void );
void init_variables( void );

/* Hilfsfunktionen              */

/* %-Wert in 0-10V Stellgroesse umrechnen */
void ProzentToAnalogOut( float scale ,ao_0_10V_t *ausgang )
{
    *ausgang = (ao_0_10V_t) ((scale*VFULLSCALE)/100);
}

void cntrl_task( void )
{
    static int  old_ALL_PARTY = IO_AUS;
    static int  old_WW_PARTY = IO_AUS;

#ifdef __WAGO__
 	KbusUpdate();
#endif
	cntrl_zeitprogramm();

    /* ALL_Party Flag ermitteln */
    if( ( ALL_PARTY >= IO_EIN ) && ( old_ALL_PARTY == IO_AUS ) ) {
        partytime_flg = SET;  /* Ruecksetzen in cntrl_min_task() */
        all_party_restzeit_min = all_partydauer;
    }
    old_ALL_PARTY = ALL_PARTY;

    /* WW_Party Flag ermitteln */
    if( ( WW_PARTY >= IO_EIN ) && ( old_WW_PARTY == IO_AUS ) ) {
        ww_partytime_flg = SET;  /* Ruecksetzen in cntrl_min_task() */
        ww_party_restzeit_min = all_partydauer;
    }
    old_WW_PARTY = WW_PARTY;

    if( schedule_min_flg == SET ) {
        cntrl_min_task();
        schedule_min_flg = RESET;
    }
    if( schedule_hour_flg == SET ) {
        cntrl_hour_task();
        schedule_hour_flg = RESET;
    }

    cntrl_Solarbeheizung();
    cntrl_FB_Heizkreis();
    cntrl_HK_Heizkreis();
    cntrl_WW_Heizkreis();

    /* Ansteuerung der Speicher unbedingt nach FB und HK,
     * da abhaengig von berechneten Sollwerten
     */
    cntrl_Speicher();
    /* Kesselansteuerung ist abhaengig von Speicherbeschickung */
    cntrl_Kessel();

#ifdef __WAGO__
	KbusUpdate();
#endif
}

void cntrl_min_task( void )
{
    static int		index = 0;

    FILE *fp;

    /* Partyflag Ruecksetzzeitpunkt ermitteln */
    if(  all_party_restzeit_min > 0 ) {
        all_party_restzeit_min --;
    }
    else {
        partytime_flg = RESET;
    }
    /* Partyflag auf jeden Fall zuruecksetzen, wenn Partyschalter wieder ausgeschaltet wird */
    if( ALL_PARTY == IO_AUS ) {
        partytime_flg = RESET;
    }

    /* Warmwasser Partyflag Ruecksetzzeitpunkt ermitteln */
    if(  ww_party_restzeit_min > 0 ) {
        ww_party_restzeit_min --;
    }
    else {
        ww_partytime_flg = RESET;
    }
    /* Partyflag auf jeden Fall zuruecksetzen, wenn Partyschalter wieder ausgeschaltet wird */
    if( WW_PARTY == IO_AUS ) {
        ww_partytime_flg = RESET;
    }

    /* Berechnung des 1 Stundenmittelwerts der Aussentemperatur aus 60 Werten alle Minuten */
    Tau_1h_Summe_f += ALL_Tau_MW - Tau_1min_Intervall[index];
    Tau_1min_Intervall[index] = ALL_Tau_MW;
    index ++;
    if( index > 59 ) {
        index = 0;
    }
    Tau_1h_mittel_f = Tau_1h_Summe_f / 60.0;

#ifdef __LOGFILE__
    /* Logfile Eintraege schreiben */
    fp = fopen( "/home/RCA.log", "a" );
    if( fp != NULL ) {
        log_variables( fp );
        fclose( fp );
    }
#endif

}

void cntrl_hour_task( void )
{
	static int		index = 0;

	/* Berechnung des 36h (default) Mittelwerts der Aussentemperatur aus 36 1h Mittelwerten */
	Tau_36h_Summe_f += Tau_1h_mittel_f - Tau_1h_mittel_36h_Intervall[index];
    Tau_1h_mittel_36h_Intervall[index] = Tau_1h_mittel_f;
    index ++;
	if( index >= all_tau_mittel_zeit ) {
		index = 0;
	}
	Tau_36h_mittel_f = Tau_36h_Summe_f / all_tau_mittel_zeit;
}

void cntrl_initAverageTau( float currTau )
{
	int i;

	for( i=0; i<60; i++ ) {
        Tau_1min_Intervall[i] = currTau;
	}
	for( i=0; i<all_tau_mittel_zeit; i++ ) {
        Tau_1h_mittel_36h_Intervall[i] = currTau;
	}
	Tau_1h_Summe_f = currTau * 60;
	Tau_36h_Summe_f = currTau * all_tau_mittel_zeit;
}


