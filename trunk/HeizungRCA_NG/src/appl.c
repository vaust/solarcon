#define __IO_MASTER__
#define __TEST__

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

#ifdef __WAGO__
#include <asm/types.h>
#include "kbusapi.h"
#include "io.h"
#endif

extern pthread_mutex_t	mutex;

#ifdef __REENTRANT__
void *main_thread( void *arg )
#else
void main( void )
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

#ifdef __REENTRANT__    
    pthread_mutex_lock( &mutex );
#ifdef __REENTRANT__
    param_Init();
    zeit_Init( &zeit_absenkung, &zeit_event );
    task_Init( &tau, ALL_Tau_MW );
    solar_Init( &sol_par );
    fb_Init( &fb_par, &fb_q );
    hk_Init( &hk_par, &hk_q );
    ww_Init( &ww_par, &ww_q );
#ifdef __REENTRANT__
    pthread_mutex_unlock( &mutex );
#ifdef __REENTRANT__    

#ifdef __TEST__
    zeit_TEST_Schaltzeiten();
    for( n=0; n<PARSE_SET_N; n++ ) {
        printf( Vorgaben[n].VarName );
        printf( "= " );
        printf( Vorgaben[n].format, *(float *)Vorgaben[n].VarPointer );
        printf( "\n" );
    }
#endif


    while( 1 ) {
#ifdef __WAGO__
        KbusOpen();
        KbusUpdate();
#endif


    /*  sol_in_Sp1.koll_t_mw = ALL_Tau_MW;
        sol_in_Sp1.sp_to_mw = SOL_SP1_To_MW;
        sol_in_Sp1.sp_tu_mw = SOL_SP1_Tu_MW;

        sol_in_Sp2.koll_t_mw = ALL_Tau_MW;
        sol_in_Sp2.sp_to_mw = SOL_SP2_To_MW;
        sol_in_Sp2.sp_tu_mw = SOL_SP2_Tu_MW;
    */
        sol_in_Sp1.koll_t_mw = 85.0;
        sol_in_Sp1.sp_to_mw = 38.0;
        sol_in_Sp1.sp_tu_mw = 34.0;

        sol_in_Sp2.koll_t_mw = 85.0;
        sol_in_Sp2.sp_to_mw = 57.0;
        sol_in_Sp2.sp_tu_mw = 44.0;


        task_Run( param_all_partydauer, ALL_PARTY, WW_PARTY, ALL_Tau_MW, &tau, &zeit_event, &zeit_party );
        zeit_Run( &zeit_absenkung, &zeit_event );
        
        solar_Run( &sol_par, &sol_in_Sp1, &sol_in_Sp2, &sol_sp1_av_sb, &sol_sp2_av_sb, &sol_pu_sb );
        fb_Run( &fb_par, &fb_q, &fb_in, &fb_out );
        hk_Run( &hk_par, &fb_q, &hk_in, &hk_out ); 
        ww_Run( &ww_par, &ww_q, &ww_in, &ww_out );
        
    printf( "Zeit: Absenkung Fußbodenheizung: %d\n", zeit_absenkung.FB_Zustand );
    printf( "sp1_av_sb=%d\nsp2_av_sb=%d\nsol_pu_sb=%d\n",
            sol_sp1_av_sb, sol_sp2_av_sb, sol_pu_sb );

    return( 0 );
}

