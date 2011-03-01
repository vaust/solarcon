#define _CNTRL_C_

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

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
#include "io_v2.h"
#include "err.h"
#include "cntrl.h"

#include "DEBUG.h"

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
#define MUTEX_lock      pthread_mutex_lock( &mutex );
#define MUTEX_unlock()  pthread_mutex_unlock( &mutex )
extern pthread_mutex_t  mutex;
#else
#define MUTEX_lock
#define MUTEX_unlock()
#endif


/**
 * \brief Steuerung initialisieren.
 */
void cntrl_open( void )
{
    cntrl_cnt            = 0;
    cntrl_TaskFlag_cnt   = 0;
    cntrl_Heartbeat      = 0x00;
    cntrl_Stoerungslampe = 0x00;
    Debug                = 0;
    
    KBUSOPEN();
    KBUSUPDATE();
    
    MUTEX_lock {
        io_Init();

        err_Init( &cntrl_err_par, &cntrl_err_in, &cntrl_err_out );
        cntrl_err_in.common_errcnt += param_Init();
        zeit_Init( &cntrl_zeit_absenkung, &cntrl_zeit_event );
        if( io_Normal != io_ReadT( &io_ALL_Tau_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;
        task_Init( &cntrl_tau, io_ALL_Tau_MW.messwert );
        sol_Init( &cntrl_sol );
        fb_Init( &cntrl_fb );
        hk_Init( &cntrl_hk );
        ww_Init( &cntrl_ww );
        kes_Init( &cntrl_kes );

        /*----- Module aktivieren ----*/
        cntrl_mdl_aktiv.sol_aktiv     = SET;
        cntrl_mdl_aktiv.fb_aktiv      = SET;
        cntrl_mdl_aktiv.hk_aktiv      = SET;
        cntrl_mdl_aktiv.ww_aktiv      = SET;
        cntrl_mdl_aktiv.kes_aktiv     = SET;
        cntrl_mdl_aktiv.err_aktiv     = RESET; /* Default erst einmal AUS! */
        cntrl_mdl_aktiv.inp_sol_aktiv = SET;
        cntrl_mdl_aktiv.inp_fb_aktiv  = SET;
        cntrl_mdl_aktiv.inp_hk_aktiv  = SET;
        cntrl_mdl_aktiv.inp_ww_aktiv  = SET;
        cntrl_mdl_aktiv.inp_kes_aktiv = SET;
        cntrl_mdl_aktiv.inp_err_aktiv = SET;
    } MUTEX_unlock();

    KBUSUPDATE();
}

/**
 * \brief eigentlicher Steuerungsprozess.
 *
 * cntrl_run() wird zyklisch ueber einen Systemtimer \ref server.c aufgerufen.
 * \param sig enthaelt das ausloesende Signal. Dieser Parameter wird aber nicht benoetigt.
 * \return kein
 */
void cntrl_run( int sig )
{
    MUTEX_lock {
        /* Prozessabbild aktualisieren */
        KBUSUPDATE();

        /* alles was im Sekunden-, Minuten- und Stundenraster ablaufen muss und *
         * Aussentemperaturmittelwerte ermitteln                                */
        if( io_Normal != io_ReadT( &io_ALL_Tau_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;
        task_Run( param_all_partydauer,
                  io_get_ALL_PARTY(),
                  io_get_WW_PARTY(),
                  io_ALL_Tau_MW.messwert,
                  &cntrl_tau, &cntrl_zeit_event, &cntrl_zeit_party );
        /* Absenkzeiten ermitteln */
        zeit_Run( &cntrl_zeit_absenkung, &cntrl_zeit_event );

        /* Prozessdaten fuer Solarregler */
        if( SET == cntrl_mdl_aktiv.inp_sol_aktiv ) {
            if( io_Normal != io_ReadT( &io_SOL_KOLL_T_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_SOL_SP1_To_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_SOL_SP1_Tu_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_SOL_SP2_To_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_SOL_SP2_Tu_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;

            sol_WriteInp( &cntrl_sol, io_SOL_KOLL_T_MW.messwert,
                                      io_SOL_SP1_To_MW.messwert,
                                      io_SOL_SP1_Tu_MW.messwert,
                                      io_SOL_SP2_To_MW.messwert,
                                      io_SOL_SP2_Tu_MW.messwert );
        }
        /* Solarregler Task */
        if( SET == cntrl_mdl_aktiv.sol_aktiv ) {
            cntrl_err_in.sol_errcnt += sol_Run( &cntrl_sol );
        }

        /* Prozessdaten fuer Fussbodenheizungsregelung */
        if( SET == cntrl_mdl_aktiv.inp_fb_aktiv ) {
            if( io_Normal != io_ReadT( &io_ALL_Tau_MW,    NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_FB_SEK_Tvl_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;

            fb_WriteInp( &cntrl_fb, io_ALL_Tau_MW.messwert,
                                    cntrl_tau.t_36h_mittel,
                                    io_FB_SEK_Tvl_MW.messwert,
                                    cntrl_zeit_absenkung.FB_Zustand,
                                    cntrl_zeit_party.all.partytime_flg );
        }
        /* Fussbodenheizungsregelung Task */
        if( SET == cntrl_mdl_aktiv.fb_aktiv ) {
            fb_Run( &cntrl_fb );
        }

        /* Prozessdaten fuer Heizkoerperheizkreisregelung */
        if( SET == cntrl_mdl_aktiv.inp_hk_aktiv ) {
            if( io_Normal != io_ReadT( &io_ALL_Tau_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_HK_Tvl_MW,  NULL ) ) cntrl_err_in.tempsens_errcnt --;

            hk_WriteInp( &cntrl_hk, io_ALL_Tau_MW.messwert,
                                    cntrl_tau.t_36h_mittel,
                                    io_HK_Tvl_MW.messwert,
                                    cntrl_zeit_absenkung.HK_Zustand,
                                    cntrl_zeit_party.all.partytime_flg );
        }
        /* Heizkoerperheizkreisregelung Task */
        if( SET == cntrl_mdl_aktiv.hk_aktiv ) {
            hk_Run( &cntrl_hk );
        }

        /* Prozessdaten fuer Warmwasserheizkreisregelung */
        if( SET == cntrl_mdl_aktiv.inp_ww_aktiv ) {
            if( io_Normal != io_ReadT( &io_ALL_Tau_MW,    NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_WW_Tww_MW,     NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_HK_Tvl_MW,     NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_HK_Trl_MW,     NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_SOL_SP1_To_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_SOL_SP2_Tu_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;

            ww_WriteInp( &cntrl_ww, io_WW_Tww_MW.messwert,
                                    io_ALL_Tau_MW.messwert,
                                    cntrl_tau.t_36h_mittel,
                                    0,  /* Wasserzaehler ist noch nicht genutzt */
                                    io_HK_Tvl_MW.messwert,
                                    io_HK_Trl_MW.messwert,
                                    cntrl_hk.o.tvl_sw, /* ww_Run() abhaengig von Ausgabe hk_Run() */
                                    io_SOL_SP1_To_MW.messwert,
                                    io_SOL_SP2_Tu_MW.messwert,
                                    cntrl_zeit_absenkung.Zirk_Zustand,
                                    cntrl_zeit_absenkung.Duschzeit     );
        }
        /* Warmwasserheizkreisregelung Task */
        if( SET == cntrl_mdl_aktiv.ww_aktiv ) {
            ww_Run( &cntrl_ww );
        }

        /* Prozessdaten fuer Kesselsteuerung */
        if( SET == cntrl_mdl_aktiv.inp_kes_aktiv ) {
            if( io_Normal != io_ReadT( &io_SOL_SP1_To_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_SOL_SP2_Tu_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;
            if( io_Normal != io_ReadT( &io_KES_Tvl_MW,    NULL ) ) cntrl_err_in.tempsens_errcnt --;

            kes_WriteInp( &cntrl_kes, io_SOL_SP1_To_MW.messwert,
                                      io_SOL_SP2_To_MW.messwert,
                                      io_KES_Tvl_MW.messwert,
                                      0,  /* Gaszaehler noch nicht genutzt */
                                      cntrl_hk.o.tvl_sw,    /* kes_Run() abhaengig von Ausgabe hk_Run() */
                                      cntrl_fb.o.tvl_sw,    /* kes_Run() abhaengig von Ausgabe fb_Run() */
                                      cntrl_fb.o.prim_mv_y, /* neu */
                                      cntrl_zeit_absenkung.Duschzeit,
                                      io_get_KES_BR_BM()              );
        }
        /* Kesselsteuerung Task */
        if( SET == cntrl_mdl_aktiv.kes_aktiv ) {
            kes_Run( &cntrl_kes );
        }

        /* Prozessdaten fuer Sammelstoermeldung */
        if( SET == cntrl_mdl_aktiv.inp_err_aktiv ) {
            if( io_Normal != io_ReadT( &io_KES_Tvl_MW, NULL ) ) cntrl_err_in.tempsens_errcnt --;
            cntrl_err_in.br_RueckMeldung      = io_get_KES_BR_BM();
            cntrl_err_in.br_StoerMeldung      = io_get_KES_SSM();
            cntrl_err_in.kes_tvl_mw           = io_KES_Tvl_MW.messwert;
            cntrl_err_in.stb_Fussbodenheizung = io_get_FB_SEK_TW();
            cntrl_err_in.kes_tvl_sw           = cntrl_kes.o.tvl_sw;
        }
        /* Sammelstoermeldung bedienen */
        if( SET == cntrl_mdl_aktiv.err_aktiv ) {
            err_Run( &cntrl_err_par, &cntrl_err_in, &cntrl_err_out );
        }

        /* Ausgabe des Prozessabbildes */
        io_put_SOL_PU_SB( cntrl_sol.o.pu_sb[KO1] );
        io_put_SOL_SP1_AV_SB( cntrl_sol.o.av_sb[SP1] );
        io_put_SOL_SP2_AV_SB( cntrl_sol.o.av_sb[SP2] );

        if( io_Normal != io_WriteY( &io_FB_PRIM_MV_Y, cntrl_fb.o.prim_mv_y ) ) cntrl_err_in.ao_errcnt --;
        io_put_FB_PRIM_PU_SB( cntrl_fb.o.prim_pu_sb );
        io_put_FB_SEK_PU_SB( cntrl_fb.o.sek_pu_sb );

        if( io_Normal != io_WriteY( &io_HK_MV_Y, cntrl_hk.o.mv_y ) ) cntrl_err_in.ao_errcnt --;
        io_put_HK_PU_SB( cntrl_hk.o.pu_sb );

        if( io_Normal != io_WriteY( &io_WW_HZG_MV_Y, cntrl_ww.o.hzg_mv_y ) ) cntrl_err_in.ao_errcnt --;
        io_put_WW_HZG_VV_SB( cntrl_ww.o.hzg_vv_sb );
        io_put_WW_HZG_PU_SB( cntrl_ww.o.hzg_pu_sb );
        if( io_Normal != io_WriteY( &io_WW_HZG_PU_Y, cntrl_ww.o.hzg_pu_y ) ) cntrl_err_in.ao_errcnt --;
        io_put_WW_ZIRK_PU_SB( cntrl_ww.o.zirk_pu_sb );

        if( io_Normal != io_WriteY( &io_KES_Tvl_Y, cntrl_kes.o.tvl_sw ) ) cntrl_err_in.ao_errcnt --;
        io_put_KES_PU_SP1_SB( cntrl_kes.o.pu_sp1_sb );
        io_put_KES_PU_SP2_SB( cntrl_kes.o.pu_sp2_sb );

        /* Lebenszeichen der Steuerung */
        io_put_CONTROL_AKTIV( cntrl_Heartbeat );
        cntrl_Heartbeat = !cntrl_Heartbeat;

        if( cntrl_err_out.Sammelstoermeldung == RESET ) {
            io_put_STOERUNG( IO_AUS );              /* Stoermeldung AUS */
        }
        else {
            io_put_STOERUNG( cntrl_Stoerungslampe );  /* Stoermeldung blinken lassen */
            cntrl_Stoerungslampe = !cntrl_Stoerungslampe;
        }

        /* Prozessabbild aktualisieren */
        KBUSUPDATE();
    } MUTEX_unlock();
    
    cntrl_cnt ++; /* Aufrufzaehler inkrementieren */
}

/**
 * \brief Steuerungsprozess beenden.
 * Diese Funktion duerfte im laufenden Prozess nie gerufen werden.
 */
void cntrl_close( void )
{
    KBUSCLOSE();
}
