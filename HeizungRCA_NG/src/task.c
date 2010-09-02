/* Modul mit allen Methoden, die in einem bestimmten Zeitraster aufgerufen 
 * werden muessen.
 */
 #define _TASK_C_

/*
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
*/

#ifdef __WAGO__
#include <asm/types.h>
#include "kbusapi.h"
#endif

#include "gen_types.h"
#include "io.h"
#include "param.h"
#include "zeit.h"
#include "task.h"

void task_partytime_1s( const int          all_partydauer, 
                        const di_bitbyte_t all_party, 
                        const di_bitbyte_t ww_party,  
                              zeit_party_t *partytime )
                     {
    static di_bitbyte_t  old_all_party = IO_AUS;
    static di_bitbyte_t  old_ww_party = IO_AUS;

    
    if( ( all_party >= IO_EIN ) && ( old_all_party == IO_AUS ) ) {
        partytime->all_partytime_flg = SET;  /* Ruecksetzen in task_min() */
        partytime->all_party_restzeit_min = all_partydauer;
    }
    old_all_party = all_party;

    /* WW_Party Flag ermitteln */
    if( ( ww_party >= IO_EIN ) && ( old_ww_party == IO_AUS ) ) {
        partytime->ww_partytime_flg = SET;  /* Ruecksetzen in task_min() */
        partytime->ww_party_restzeit_min = all_partydauer;
    }
    old_ww_party = ww_party;
}

void task_event_1s( const di_bitbyte_t all_party, 
                    const di_bitbyte_t ww_party,
                    const float        all_tau_mw,
                          task_tau_t   *tau,
                          zeit_event_t *schedule,
                          zeit_party_t *partytime ) 
{
    if( schedule->min_flg == SET ) {
        task_minute( all_party, ww_party, all_tau_mw, partytime, tau );
        schedule->min_flg = RESET;
    }
    if( schedule->hour_flg == SET ) {
        task_hour( tau );
        schedule->hour_flg = RESET;
    }
}
       
void task_minute( const di_bitbyte_t all_party, 
                  const di_bitbyte_t ww_party, 
                  const float        all_tau_mw,
                        zeit_party_t *partytime,
                        task_tau_t   *tau       )
{
    static int		index = 0;

    /* Partyflag Ruecksetzzeitpunkt ermitteln */
    if(  partytime->all_party_restzeit_min > 0 ) {
        partytime->all_party_restzeit_min --;
    }
    else {
        partytime->all_partytime_flg = RESET;
    }
    /* Partyflag auf jeden Fall zuruecksetzen, 
     * wenn Partyschalter wieder ausgeschaltet wird */
    if( all_party == IO_AUS ) {
        partytime->all_partytime_flg = RESET;
    }

    /* Warmwasser Partyflag Ruecksetzzeitpunkt ermitteln */
    if( partytime->ww_party_restzeit_min > 0 ) {
        partytime->ww_party_restzeit_min --;
    }
    else {
        partytime->ww_partytime_flg = RESET;
    }
    /* Partyflag auf jeden Fall zuruecksetzen, 
     * wenn Partyschalter wieder ausgeschaltet wird */
    if( ww_party == IO_AUS ) {
        partytime->ww_partytime_flg = RESET;
    }

    /* Berechnung des 1 Stundenmittelwerts der Aussentemperatur 
     * aus 60 Werten alle Minuten */

    tau->t_1h_summe += all_tau_mw - tau->t_1min_Intervall[index];
    tau->t_1min_Intervall[index] = all_tau_mw; 
    index ++;
    if( index > 59 ) 
        index = 0;
    tau->t_1h_mittel = tau->t_1h_summe/60.0;
 }

void task_hour( task_tau_t *tau )
{
	static int index = 0;

	/* Berechnung des 36h (default) Mittelwerts der Aussentemperatur aus 36 1h Mittelwerten */
	tau->t_36h_summe += tau->t_1h_mittel - tau->t_1h_mittel_36h_Intervall[index];
    tau->t_1h_mittel_36h_Intervall[index] = tau->t_1h_mittel;
    index ++;
	if( index >= param_all_tau_mittel_zeit ) 
        index = 0;
	tau->t_36h_mittel = tau->t_36h_summe / param_all_tau_mittel_zeit;
}

void task_Init_Tau( task_tau_t *tau, float all_tau_mw )
{
	int i;

	for( i=0; i<60; i++ ) {
        tau->t_1min_Intervall[i] = all_tau_mw;
	}
	for( i=0; i<param_all_tau_mittel_zeit; i++ ) {
        tau->t_1h_mittel_36h_Intervall[i] = all_tau_mw;
	}
	tau->t_1h_summe = all_tau_mw * 60;
	tau->t_36h_summe = all_tau_mw * param_all_tau_mittel_zeit;
}

/** MAIN TASK **/ 
#ifdef __TEST__
void task_main( void )
{
    zeit_party_t zeit_party;
    zeit_event_t zeit_event;
    task_tau_t   tau;
    
#ifdef __WAGO__
 	KbusUpdate();
#endif
    task_partytime_1s( param_all_partydauer, ALL_PARTY, WW_PARTY, &zeit_party );
    task_event_1s( ALL_PARTY, WW_PARTY, ALL_Tau_MW, &tau, &zeit_event, &zeit_party );    


#ifdef __WAGO__
	KbusUpdate();
#endif
}
#endif /* __TEST__ */


