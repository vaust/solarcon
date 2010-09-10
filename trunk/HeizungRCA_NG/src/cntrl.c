#define _CNTRL_C_
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
#include "io.h"
#include "cntrl.h"

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
    MUTEX_LOCK();
    param_Init();
    zeit_Init( &cntrl_zeit_absenkung, &cntrl_zeit_event );
    task_Init( &cntrl_tau, ALL_Tau_MW );
    solar_Init( &cntrl_sol_par );
    fb_Init( &cntrl_fb_par, &cntrl_fb_q, &cntrl_fb_out );
    hk_Init( &cntrl_hk_par, &cntrl_hk_q, &cntrl_hk_out );
    ww_Init( &cntrl_ww_par, &cntrl_ww_q, &cntrl_ww_out );
    kes_Init( &cntrl_kes_par, &cntrl_kes_out );
    MUTEX_UNLOCK();

#ifdef __TEST__
    zeit_TEST_Schaltzeiten();
    param_TEST_Vorgaben();
#endif

    KBUSOPEN();
    while( 1  ) {
        KBUSUPDATE();

        MUTEX_LOCK();
        /* alles was im Sekunden-, Minuten- und Stundenraster ablaufen muss und *
         * Aussentemperaturmittelwerte ermitteln                                */
        task_Run( param_all_partydauer, ALL_PARTY, WW_PARTY, ALL_Tau_MW, &cntrl_tau, &cntrl_zeit_event, &cntrl_zeit_party );
        /* Absenkzeiten ermitteln */
        zeit_Run( &cntrl_zeit_absenkung, &cntrl_zeit_event );

        cntrl_sol_in_Sp1.koll_t_mw = cntrl_sol_in_Sp2.koll_t_mw                          = 35.0;  // = SOL_KOLL_T_MW;
        cntrl_sol_in_Sp1.sp_to_mw  = cntrl_ww_in.sol_sp1_to_mw  = cntrl_kes_in.sp1_to_mw = 67.9;  // = SOL_SP1_To_MW; 
        cntrl_sol_in_Sp1.sp_tu_mw                               = cntrl_kes_in.sp1_tu_mw = 34.0;  // = SOL_SP1_Tu_MW;  
        cntrl_sol_in_Sp2.sp_to_mw                               = cntrl_kes_in.sp2_to_mw = 37.0;  // = SOL_SP2_To_MW; 
        cntrl_sol_in_Sp2.sp_tu_mw  = cntrl_ww_in.sol_sp2_tu_mw  = cntrl_kes_in.sp2_tu_mw = 33.0;  // = SOL_SP2_Tu_MW;                     

        cntrl_fb_in.tau_mw         = cntrl_hk_in.tau_mw         = cntrl_ww_in.tau_mw     = 11.0;  // = ALL_Tau_MW;
        cntrl_fb_in.tau_avg        = cntrl_hk_in.tau_avg        = cntrl_ww_in.tau_avg    = 13.4;  // = tau.t_36h_mittel;
        cntrl_fb_in.sek_tvl_mw                                                           = 27.0;  // = FB_SEK_Tvl_MW;
        cntrl_fb_in.zustand        = cntrl_zeit_absenkung.FB_Zustand;
        cntrl_fb_in.partytime_flg  = cntrl_hk_in.partytime_flg  = cntrl_zeit_party.all_partytime_flg;

        cntrl_hk_in.tvl_mw         = cntrl_ww_in.hzg_tvl_mw     = 45.0;   // = HK_Tvl_MW;
        cntrl_hk_in.zustand        = cntrl_zeit_absenkung.HK_Zustand;

        cntrl_ww_in.tww_mw         = 23.4;   // = WW_Tww_MW;
        cntrl_ww_in.hzg_trl_mw     = 31.0;   // = HK_Trl_MW;

        cntrl_kes_in.tvl_mw        = 25.0;   // = KES_Tvl_MW;
        cntrl_kes_in.duschzeit     = cntrl_zeit_absenkung.Duschzeit; 
        cntrl_kes_in.partytime_flg = cntrl_zeit_party.ww_partytime_flg;

        /* solar_Run(), fb_Run() und hk_Run() sind unabhaengig von einander */
        solar_Run( &cntrl_sol_par, &cntrl_sol_in_Sp1, 
                   &cntrl_sol_in_Sp2, &cntrl_sol_sp1_av_sb, 
                   &cntrl_sol_sp2_av_sb, &cntrl_sol_pu_sb );
        fb_Run( &cntrl_fb_par, &cntrl_fb_q, &cntrl_fb_in, &cntrl_fb_out );
        hk_Run( &cntrl_hk_par, &cntrl_fb_q, &cntrl_hk_in, &cntrl_hk_out );

        /* ww_Run() Eingabewerte sind abhaengig von Ausgabewerten von hk_Run() */
        cntrl_ww_in.hk_tvl_sw  = cntrl_hk_out.tvl_sw;
        ww_Run( &cntrl_ww_par, &cntrl_ww_q, &cntrl_ww_in, &cntrl_ww_out );
        
        /* kes_Run() Eingabewerte abhaengig von Ausgabewerten von hk_Run(), fb_Run() */
        cntrl_kes_in.hk_tvl_sw = cntrl_hk_out.tvl_sw;
        cntrl_kes_in.fb_tvl_sw = cntrl_fb_out.tvl_sw;
        kes_Run( &cntrl_kes_par, &cntrl_kes_in, &cntrl_kes_out );
 
        /* Ab hier Ausgabe des Prozessabbildes */
#ifdef __TEST__        
        printf( "CNTRL.C: TEST: ZEIT : Absenkung Fussbodenheizung: %d\n", cntrl_zeit_absenkung.FB_Zustand );
        printf( "CNTRL.C: TEST: ZEIT : Absenkung Duschzeit       : %d\n", cntrl_zeit_absenkung.Duschzeit );
        printf( "CNTRL.C: TEST: SOLAR: sp1_av_sb=%d sp2_av_sb=%u sol_pu_sb=%d\n",
                cntrl_sol_sp1_av_sb, cntrl_sol_sp2_av_sb, cntrl_sol_pu_sb );
        printf( "CNTRL.C: TEST: FB   : tvl_sw=%f prim_mv_y=%f prim_pu_sb=%d sek_pu_sb=%d\n",
                cntrl_fb_out.tvl_sw, cntrl_fb_out.prim_mv_y.y, cntrl_fb_out.prim_pu_sb, cntrl_fb_out.sek_pu_sb );
        printf( "CNTRL.C: TEST: HK   : tvl_sw=%f mv_y=%f pu_sb=%d\n",
                cntrl_hk_out.tvl_sw, cntrl_hk_out.mv_y.y, cntrl_hk_out.pu_sb );        
        printf( "CNTRL.C: TEST: WW   : hzg_tvl_sw=%f hzg_mv_y=%f hzg_pu_y=%f zirk_pu_sb=%d hzg_pu_sb=%d hzg_vv_sb=%d\n", 
                cntrl_ww_out.hzg_tvl_sw, cntrl_ww_out.hzg_mv_y.y, cntrl_ww_out.hzg_pu_y.y, 
                cntrl_ww_out.zirk_pu_sb, cntrl_ww_out.hzg_pu_sb, cntrl_ww_out.hzg_vv_sb );
        printf( "CNTRL.C: TEST: KES  : sp1_to_sw=%f sp2_to_sw=%f tvl_sw_sp1=%f tvl_sw_sp2=%f \n",
                cntrl_kes_out.sp1_to_sw, cntrl_kes_out.sp2_to_sw, 
                cntrl_kes_out.tvl_sw_sp1, cntrl_kes_out.tvl_sw_sp2 );
        printf( "CNTRL.C: TEST: KES  : tvl_sw=%f pu_sp1_sb=%d pu_sp2_sb=%d\n", 
                cntrl_kes_out.tvl_sw, cntrl_kes_out.pu_sp1_sb, cntrl_kes_out.pu_sp2_sb );
                printf( "\n" );        
#endif /* __TEST__ */

        /* Lebenszeichen der Steuerung */
        CONTROL_AKTIV = !CONTROL_AKTIV; 

        KBUSUPDATE();
        MUTEX_UNLOCK();
        
        /* Abtastzeit abwarten. ACHTUNG: Rechenzeit nicht beruecksichtigt */
        SLEEP( ABTASTZEIT_USEC ); 
    }
    KBUSCLOSE();
    return( 0 );
}

