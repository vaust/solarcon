#define _CNTRL_C_

#include <stdio.h>
#include <unistd.h>

#include "gen_types.h"
#include "param.h"
#include "zeit.h"
#include "task.h"
#include "sol.h"
#include "fb.h"
#include "hk.h"
#include "ww.h"
#include "kes.h"
#include "io.h"
#include "cntrl.h"

#define SP1     0
#define SP2     1
#define KOLL    0

#ifdef __WIN__
#include <windows.h>
#define SLEEP(t) Sleep((t)/1000)
#else
#define SLEEP(t) usleep((t))
#endif

#ifdef __WAGO__
#include <asm/types.h>
#include "kbusapi.h"
#define KBUSOPEN()   KbusOpen()
#define KBUSUPDATE() KbusUpdate()
#define KBUSCLOSE()  KbusClose()
#else
#define KBUSOPEN() 
#define KBUSUPDATE() 
#define KBUSCLOSE()
#endif

#ifdef __REENTRANT__
#include <pthread.h>    /* Fuer Threadfunktionalitaet */
#include <semaphore.h>
#define MUTEX_LOCK()    pthread_mutex_lock( &mutex )
#define MUTEX_UNLOCK()  pthread_mutex_unlock( &mutex ) 
#else
#define MUTEX_LOCK()   
#define MUTEX_UNLOCK() 
#endif

#ifdef __REENTRANT__
extern pthread_mutex_t  mutex;
void *cntrl_thread( void *arg )
#else
int main( void )
#endif
{    
    KBUSOPEN();
    KBUSUPDATE();   

    MUTEX_LOCK();
    param_Init();
    zeit_Init( &cntrl_zeit_absenkung, &cntrl_zeit_event );
    task_Init( &cntrl_tau, io_get_ALL_Tau_MW() );
    sol_Init( &cntrl_sol_par );
    fb_Init( &cntrl_fb_par, &cntrl_fb_q, &cntrl_fb_out );
    hk_Init( &cntrl_hk_par, &cntrl_hk_q, &cntrl_hk_out );
    ww_Init( &cntrl_ww_par, &cntrl_ww_q, &cntrl_ww_out );
    kes_Init( &cntrl_kes_par, &cntrl_kes_out );
    MUTEX_UNLOCK();

#ifdef __TEST__
    zeit_TEST_Schaltzeiten();
    param_TEST_Vorgaben();
#endif

    while( 1  ) {
        MUTEX_LOCK();
        KBUSUPDATE();   /*---------- Prozessabbild aktualisieren ----------*/

        /*---------- EINGABE DES PROZESSABBILDES ------------*/
        /* alles was im Sekunden-, Minuten- und Stundenraster ablaufen muss und *
         * Aussentemperaturmittelwerte ermitteln                                */
        task_Run( param_all_partydauer, 
                  io_get_ALL_PARTY(), 
                  io_get_WW_PARTY(), 
                  io_get_ALL_Tau_MW(), 
                  &cntrl_tau, &cntrl_zeit_event, 
                  &cntrl_zeit_party );
        /* Absenkzeiten ermitteln */
        zeit_Run( &cntrl_zeit_absenkung, &cntrl_zeit_event );

        /* Prozessdaten */
        cntrl_sol_in.koll_t_mw[KOLL] = io_get_SOL_KOLL_T_MW();
        cntrl_sol_in.t_sp[SP1].to_mw = cntrl_ww_in.sol_sp1_to_mw  = cntrl_kes_in.sp1_to_mw = io_get_SOL_SP1_To_MW(); 
        cntrl_sol_in.t_sp[SP1].tu_mw                              = cntrl_kes_in.sp1_tu_mw = io_get_SOL_SP1_Tu_MW();  
        cntrl_sol_in.t_sp[SP2].to_mw                              = cntrl_kes_in.sp2_to_mw = io_get_SOL_SP2_To_MW(); 
        cntrl_sol_in.t_sp[SP2].tu_mw = cntrl_ww_in.sol_sp2_tu_mw  = cntrl_kes_in.sp2_tu_mw = io_get_SOL_SP2_Tu_MW();

        cntrl_fb_in.tau_mw         = cntrl_hk_in.tau_mw         = cntrl_ww_in.tau_mw     = io_get_ALL_Tau_MW();
        cntrl_fb_in.tau_avg        = cntrl_hk_in.tau_avg        = cntrl_ww_in.tau_avg    = cntrl_tau.t_36h_mittel;
        cntrl_fb_in.sek_tvl_mw                                                           = io_get_FB_SEK_Tvl_MW();
        cntrl_fb_in.zustand        = cntrl_zeit_absenkung.FB_Zustand;
        cntrl_fb_in.partytime_flg  = cntrl_hk_in.partytime_flg  = cntrl_zeit_party.all_partytime_flg;

        cntrl_hk_in.tvl_mw         = cntrl_ww_in.hzg_tvl_mw     = io_get_HK_Tvl_MW();
        cntrl_hk_in.zustand        = cntrl_zeit_absenkung.HK_Zustand;

        cntrl_ww_in.tww_mw         = io_get_WW_Tww_MW();
        cntrl_ww_in.hzg_trl_mw     = io_get_HK_Trl_MW();

        cntrl_kes_in.tvl_mw        = io_get_KES_Tvl_MW();
        cntrl_kes_in.duschzeit     = cntrl_zeit_absenkung.Duschzeit; 
        cntrl_kes_in.br_bm         = io_get_KES_BR_BM();
        cntrl_kes_in.partytime_flg = cntrl_zeit_party.ww_partytime_flg;
 
        /*---------- VERARBEITUNG DES PROZESSABBILDES -----------*/
        /* solar_Run(), fb_Run() und hk_Run() sind unabhaengig von einander */
        sol_Run( &cntrl_sol_par, &cntrl_sol_in, &cntrl_sol_out );
        fb_Run( &cntrl_fb_par, &cntrl_fb_q, &cntrl_fb_in, &cntrl_fb_out );
        hk_Run( &cntrl_hk_par, &cntrl_fb_q, &cntrl_hk_in, &cntrl_hk_out );

        /* ww_Run() Eingabewerte sind abhaengig von Ausgabewerten von hk_Run() */
        cntrl_ww_in.hk_tvl_sw  = cntrl_hk_out.tvl_sw;
        ww_Run( &cntrl_ww_par, &cntrl_ww_q, &cntrl_ww_in, &cntrl_ww_out );
        
        /* kes_Run() Eingabewerte abhaengig von Ausgabewerten von hk_Run() und fb_Run() */
        cntrl_kes_in.hk_tvl_sw = cntrl_hk_out.tvl_sw;
        cntrl_kes_in.fb_tvl_sw = cntrl_fb_out.tvl_sw;
        kes_Run( &cntrl_kes_par, &cntrl_kes_in, &cntrl_kes_out );
 
        /*---------- AUSGABE DES PROZESSABBILDES ------------*/
        io_put_SOL_PU_SB( cntrl_sol_out.sol_pu_sb[KOLL] );    
        io_put_SOL_SP1_AV_SB( cntrl_sol_out.sp_av_sb[SP1] );
        io_put_SOL_SP2_AV_SB( cntrl_sol_out.sp_av_sb[SP2] );
   
        io_put_FB_PRIM_MV_Y( cntrl_fb_out.prim_mv_y.y );               
        io_put_FB_PRIM_PU_SB( cntrl_fb_out.prim_pu_sb );
        io_put_FB_SEK_PU_SB( cntrl_fb_out.sek_pu_sb ); 
        
        io_put_HK_MV_Y( cntrl_hk_out.mv_y.y );               
        io_put_HK_PU_SB( cntrl_hk_out.pu_sb );

        io_put_WW_HZG_MV_Y( cntrl_ww_out.hzg_mv_y.y );                   
        io_put_WW_HZG_VV_SB( cntrl_ww_out.hzg_vv_sb );    
        io_put_WW_HZG_PU_SB( cntrl_ww_out.hzg_pu_sb );    
        io_put_WW_HZG_PU_Y( cntrl_ww_out.hzg_pu_y.y );                  
        io_put_WW_ZIRK_PU_SB( cntrl_ww_out.zirk_pu_sb );   

        io_put_KES_Tvl_Y( cntrl_kes_out.tvl_sw );          
        io_put_KES_PU_SP1_SB( cntrl_kes_out.pu_sp1_sb );
        io_put_KES_PU_SP2_SB( cntrl_kes_out.pu_sp2_sb ); 

        /* Lebenszeichen der Steuerung */
        io_put_CONTROL_AKTIV( !io_get_CONTROL_AKTIV() ); 
        /* Ausgabe des Prozessabbildes auf den K-Bus */
        KBUSUPDATE();   /*---------- Prozessabbild aktualisieren ----------*/
        MUTEX_UNLOCK();

        /*---------- TESTAUSGABE DES PROZESSABBILDES ----------*/
#ifdef __TEST__        
        printf( "CNTRL.C: TEST: ZEIT : Absenkung Fussbodenheizung: %d\n", cntrl_zeit_absenkung.FB_Zustand );
        printf( "CNTRL.C: TEST: ZEIT : Absenkung Duschzeit       : %d\n", cntrl_zeit_absenkung.Duschzeit );
        printf( "CNTRL.C: TEST: SOLAR: sp1_av_sb=%d sp2_av_sb=%u sol_pu_sb=%d\n",
                cntrl_sol_out.sp_av_sb[0], cntrl_sol_out.sp_av_sb[1], cntrl_sol_out.sol_pu_sb[0] );
        printf( "CNTRL.C: TEST: FB   : tvl_sw=%f prim_mv_y=%f prim_pu_sb=%d sek_pu_sb=%d\n",
                cntrl_fb_out.tvl_sw, cntrl_fb_out.prim_mv_y.y, cntrl_fb_out.prim_pu_sb, cntrl_fb_out.sek_pu_sb );
        printf( "CNTRL.C: TEST: HK   : tvl_sw=%f mv_y=%f pu_sb=%d\n",
                cntrl_hk_out.tvl_sw, cntrl_hk_out.mv_y.y, cntrl_hk_out.pu_sb );        
        printf( "CNTRL.C: TEST: WW   : hzg_tvl_sw=%f hzg_mv_y=%f hzg_pu_y=%f zirk_pu_sb=%d hzg_pu_sb=%d hzg_vv_sb=%d\n", 
                cntrl_ww_out.hzg_tvl_sw, cntrl_ww_out.hzg_mv_y.y, cntrl_ww_out.hzg_pu_y.y, 
                cntrl_ww_out.zirk_pu_sb, cntrl_ww_out.hzg_pu_sb, cntrl_ww_out.hzg_vv_sb );
        printf( "CNTRL.C: TEST: KES  : sp1_to_sw=%f sp2_to_sw=%f tvl_sw_sp1=%f tvl_sw_=%f \n",
                cntrl_kes_out.sp1_to_sw, cntrl_kes_out.sp2_to_sw, 
                cntrl_kes_out.tvl_sw_sp1, cntrl_kes_out.tvl_sw_sp2 );
        printf( "CNTRL.C: TEST: KES  : tvl_sw=%f pu_sp1_sb=%d pu_sp2_sb=%d\n", 
                cntrl_kes_out.tvl_sw, cntrl_kes_out.pu_sp1_sb, cntrl_kes_out.pu_sp2_sb );                
        printf( "\n" );        
#endif /* __TEST__ */
        
        /* Abtastzeit abwarten. ACHTUNG: Rechenzeit nicht beruecksichtigt.
           Muesste eigentlich ueber Timerfunktion laufen */
        SLEEP( ABTASTZEIT_USEC ); 
    }

    KBUSCLOSE();
    return( 0 );
}

