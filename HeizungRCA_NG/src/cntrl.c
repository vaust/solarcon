#define __IO_MASTER__

#include <stdio.h>
#include <unistd.h>

#include "gen_types.h"
#include "param.h"
#include "zeit.h"
#include "task.h"
#include "solar.h"
#include "fb.h"
#include "hk.h"
#include "ww.h"
#include "kes.h"

#ifdef __WAGO__
#include <asm/types.h>
#include "kbusapi.h"
#include "io.h"
#endif

#ifdef __REENTRANT__
#define MUTEX_LOCK()    pthread_mutex_lock( &mutex )
#define MUTEX_UNLOCK()  pthread_mutex_unlock( &mutex ) 
#else
#define MUTEX_LOCK()   
#define MUTEX_UNLOCK() 
#endif

#ifdef __REENTRANT__
extern pthread_mutex_t	mutex;
void *cntrl_thread( void *arg )
#else
int main( void )
#endif
{
    int n;

    /* Variablen fuer Zeit */
    zeit_Betriebszustand_t  zeit_absenkung;
    zeit_event_t            zeit_event;
    zeit_party_t            zeit_party;

    /* Mittelwertbildung fuer Aussentemperatur */
    task_tau_t   tau;

    /* Variablen fuer Solarkollektorsteuerung */
    sol_in_t     sol_in_Sp1, sol_in_Sp2;
    do_bitbyte_t sol_sp1_av_sb, sol_sp2_av_sb, sol_pu_sb;
    sol_param_t  sol_par;

    /* Variablen fuer Fussbodenheizung */
    fb_param_t          fb_par;
    fb_out_t            fb_out;
    fb_in_t             fb_in;
    sup_digreg_coeff_t  fb_q;

    /* Variablen fuer Heizkörperkreis */
    hk_param_t          hk_par;
    hk_out_t            hk_out;
    hk_in_t             hk_in;
    sup_digreg_coeff_t  hk_q;

    /* Variablen fuer Warmwasserkreis */
    ww_param_t          ww_par;
    ww_out_t            ww_out;
    ww_in_t             ww_in;
    sup_digreg_coeff_t  ww_q;

    /* Variablen fuer Kessel Steuerung */
    kes_param_t         kes_par; 
    kes_in_t            kes_in;
    kes_out_t           kes_out;
    
    MUTEX_LOCK();
    param_Init();
    zeit_Init( &zeit_absenkung, &zeit_event );
    task_Init( &tau, ALL_Tau_MW );
    solar_Init( &sol_par );
    fb_Init( &fb_par, &fb_q );
    hk_Init( &hk_par, &hk_q );
    ww_Init( &ww_par, &ww_q );
    kes_Init();
    MUTEX_UNLOCK();

#ifdef __TEST__
    zeit_TEST_Schaltzeiten();
    param_TEST_Vorgaben();
#endif


//    while( 1 ) {
#ifdef __WAGO__
        KbusOpen();
        KbusUpdate();
#endif

        MUTEX_LOCK();
        task_Run( param_all_partydauer, ALL_PARTY, WW_PARTY, ALL_Tau_MW, &tau, &zeit_event, &zeit_party );
        zeit_Run( &zeit_absenkung, &zeit_event );

        /** solar_Run(), fb_Run() und hk_Run() sind unabhängig von einander */

        /** Solar Controller */
        sol_in_Sp1.koll_t_mw = 85.0;  // = SOL_KOLL_T_MW;
        sol_in_Sp1.sp_to_mw  = 38.0;  // = SOL_SP1_To_MW;
        sol_in_Sp1.sp_tu_mw  = 34.0;  // = SOL_SP1_Tu_MW;

        sol_in_Sp2.koll_t_mw = 85.0;  // = SOL_KOLL_T_MW;
        sol_in_Sp2.sp_to_mw  = 57.0;  // = SOL_SP2_To_MW;
        sol_in_Sp2.sp_tu_mw  = 44.0;  // = SOL_SP2_Tu_MW;

        solar_Run( &sol_par, &sol_in_Sp1, &sol_in_Sp2, &sol_sp1_av_sb, &sol_sp2_av_sb, &sol_pu_sb );

        /** Fussbodenheizung Controller */
        fb_in.tau_mw        = 11.0;   // = ALL_Tau_MW;
        fb_in.tau_avg       = 13.4;   // = tau.t_36h_mittel;
        fb_in.sek_tvl_mw    = 27.0;   // = FB_SEK_Tvl_MW;
        fb_in.zustand       = zeit_absenkung.FB_Zustand;
        fb_in.partytime_flg = zeit_party.all_partytime_flg;

        fb_Run( &fb_par, &fb_q, &fb_in, &fb_out );

        /** Heizkoerper Controller */
        hk_in.tau_mw        = 11.0;   // = ALL_Tau_MW;
        hk_in.tau_avg       = 13.4;   // = tau.t_36h_mittel;
        hk_in.tvl_mw        = 45.0;   // = HK_Tvl_MW;
        hk_in.zustand       = zeit_absenkung.HK_Zustand;
        hk_in.partytime_flg = zeit_party.all_partytime_flg;
        
        hk_Run( &hk_par, &fb_q, &hk_in, &hk_out );

        /** ww_Run() Eingabewerte sind abhängig von Ausgabewerten von hk_Run() */
        ww_in.tww_mw        = 41.4;   // = WW_Tww_MW;
        ww_in.tau_mw        = 11.0;   // = ALL_Tau_MW;
        ww_in.tau_avg       = 13.4;   // = tau.t_36h_mittel;
        ww_in.hzg_trl_mw    = 31.0;   // = HK_Trl_MW;
        ww_in.hk_tvl_sw     = hk_out.tvl_sw;
        ww_in.sol_sp1_to_mw = 67.9;   // = SOL_SP1_To_MW;
        ww_in.sol_sp2_tu_mw = 42.0;   // = SOL_SP2_Tu_MW;
        
        ww_Run( &ww_par, &ww_q, &ww_in, &ww_out );
        
        /** kes_Run() Eingabewerte abhängig von Ausgabewerten von hk_Run(), fb_Run() */
        kes_in.sp1_to_mw = 67.0;    // = SOL_SP1_To_MW;
        kes_in.sp1_tu_mw = 45.0;    // = SOL_SP1_Tu_MW;
        kes_in.sp2_to_mw = 56.0;    // = SOL_SP2_To_MW;
        kes_in.sp2_tu_mw = 31.0;    // = SOL_SP2_Tu_MW;
        kes_in.tvl_mw    = 60.0;    // = KES_Tvl_MW;
        kes_in.duschzeit = zeit_absenkung.Duschzeit; 
        kes_in.hk_tvl_sw = hk_out.tvl_sw;
        kes_in.fb_tvl_sw = fb_out.tvl_sw;
        kes_in.partytime_flg = zeit_party.ww_partytime_flg;
        
        kes_Run( &kes_par, &kes_in, &kes_out );
 
        /** Ab hier Ausgabe des Prozessabbildes */
        printf( "Zeit: Absenkung Fußbodenheizung: %d\n", zeit_absenkung.FB_Zustand );
        printf( "sp1_av_sb=%d\nsp2_av_sb=%d\nsol_pu_sb=%d\n",
                sol_sp1_av_sb, sol_sp2_av_sb, sol_pu_sb );



        /** Lebenszeichen der Steuerung */
        CONTROL_AKTIV = !CONTROL_AKTIV;  

#ifdef __WAGO__
        KbusOpen();
        KbusUpdate();
#endif
        MUTEX_UNLOCK();
        
        /* Abtastzeit abwarten ACHTUNG: Rechenzeit nicht beruecksichtigt */
        usleep( ABTASTZEIT_USEC );
//    }
    return( 0 );
}

