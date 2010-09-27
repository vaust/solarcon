#define _TELNET_C_

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#ifdef __REENTRANT__
#include <pthread.h>    /* Fuer Threadfunktionalitaet */
#include <semaphore.h>
#define MUTEX_LOCK()    pthread_mutex_lock( &mutex )
#define MUTEX_UNLOCK()  pthread_mutex_unlock( &mutex )
#else
#define MUTEX_LOCK()
#define MUTEX_UNLOCK()
#endif

#include "gen_types.h"
#include "param.h"      /* Parametrisierun aus INI-Dateien */
#include "io.h"         /* Ein- und Ausgabe auf der PLC    */
#include "cntrl.h"      /* Systemzustandsvariablen         */
#include "zeit.h"
#include "task.h"
#include "server.h"

#define BFLN        96
#define BFLSH()     write( fdesc, bufout, strlen( bufout ) )

const parse_set_t telnet_fb_Vars[] =
{
    { "fb_par.reg_kp",         &(cntrl_fb_par.reg_kp),         "%f" }, 
    { "fb_par.reg_tn",         &(cntrl_fb_par.reg_tn),         "%f" },
    { "fb_par.TA",             &(cntrl_fb_par.TA),             "%f" },
    { "fb_par.tvl_absenk",     &(cntrl_fb_par.tvl_absenk),     "%f" },
    { "fb_par.tvl_steigung",   &(cntrl_fb_par.tvl_steigung),   "%f" },
    { "fb_par.tvl_niveau",     &(cntrl_fb_par.tvl_niveau),     "%f" },
    { "fb_par.tvl_min",        &(cntrl_fb_par.tvl_min),        "%f" },
    { "fb_par.tvl_max",        &(cntrl_fb_par.tvl_max),        "%f" },
    { "fb_par.at_start",       &(cntrl_fb_par.at_start),       "%f" },
    { "fb_par.frostschutz",    &(cntrl_fb_par.frostschutz),    "%f" },
    { "fb_par.tr_sw",          &(cntrl_fb_par.tr_sw),          "%f" },

    
    { "fb_in.tau_mw",          &(cntrl_fb_in.tau_mw),          "%f" },
    { "fb_in.sek_tvl_mw",      &(cntrl_fb_in.sek_tvl_mw),      "%f" },
    { "fb_in.zustand",         &(cntrl_fb_in.zustand),         "%d" },
    { "fb_in.partytime_flg",   &(cntrl_fb_in.partytime_flg),   "%d" },
     
    { "fb_out.tvl_sw",         &(cntrl_fb_out.tvl_sw),         "%f" },
    { "fb_out.prim_mv_y.y",    &(cntrl_fb_out.prim_mv_y.y),    "%f" },
    { "fb_out.prim_mv_y.y_1",  &(cntrl_fb_out.prim_mv_y.y_1),  "%f" },
    { "fb_out.prim_mv_y.xd_1", &(cntrl_fb_out.prim_mv_y.xd_1), "%f" },
    { "fb_out.prim_pu_sb",     &(cntrl_fb_out.prim_pu_sb),     "%d" },
    { "fb_out.sek_pu_sb",      &(cntrl_fb_out.sek_pu_sb),      "%d" }
};

const parse_set_t telnet_hk_Vars[] =
{
    { "hk_par.reg_kp",         &(cntrl_hk_par.reg_kp),         "%f" }, 
    { "hk_par.reg_tn",         &(cntrl_hk_par.reg_tn),         "%f" },
    { "hk_par.TA",             &(cntrl_hk_par.TA),             "%f" },
    { "hk_par.tvl_absenk",     &(cntrl_hk_par.tvl_absenk),     "%f" },
    { "hk_par.tvl_steigung",   &(cntrl_hk_par.tvl_steigung),   "%f" },
    { "hk_par.tvl_niveau",     &(cntrl_hk_par.tvl_niveau),     "%f" },
    { "hk_par.tvl_min",        &(cntrl_hk_par.tvl_min),        "%f" },
    { "hk_par.tvl_max",        &(cntrl_hk_par.tvl_max),        "%f" },
    { "hk_par.at_start",       &(cntrl_hk_par.at_start),       "%f" },
    { "hk_par.frostschutz",    &(cntrl_hk_par.frostschutz),    "%f" },
    { "hk_par.tr_sw",          &(cntrl_hk_par.tr_sw),          "%f" },

    { "hk_in.tau_mw",          &(cntrl_hk_in.tau_mw),          "%f" },
    { "hk_in.tau_avg",         &(cntrl_hk_in.tau_avg),         "%f" },
    { "hk_in.tvl_mw",          &(cntrl_hk_in.tvl_mw),          "%f" },
    { "hk_in.zustand",         &(cntrl_hk_in.zustand),         "%d" },
    { "hk_in.partytime_flg",   &(cntrl_hk_in.partytime_flg),   "%d" },
     
    { "hk_out.tvl_sw",         &(cntrl_hk_out.tvl_sw),         "%f" },
    { "hk_out.mv_y.y",         &(cntrl_hk_out.mv_y.y),         "%f" },
    { "hk_out.mv_y.y_1",       &(cntrl_hk_out.mv_y.y_1),       "%f" },
    { "hk_out.mv_y.xd_1",      &(cntrl_hk_out.mv_y.xd_1),      "%f" },
    { "hk_out.pu_sb",          &(cntrl_hk_out.pu_sb),          "%d" }
};

const parse_set_t telnet_ww_Vars[] =
{
    { "ww_par.pu_reg_kp",           &(cntrl_ww_par.pu_reg_kp),           "%f" }, 
    { "ww_par.pu_reg_tn",           &(cntrl_ww_par.pu_reg_tn),           "%f" },
    { "ww_par.TA",                  &(cntrl_ww_par.TA),                  "%f" },
    { "ww_par.kes_sp_dt_sw",        &(cntrl_ww_par.kes_sp_dt_sw),        "%f" },
    { "ww_par.tww_sw",              &(cntrl_ww_par.tww_sw),              "%f" },
    { "ww_par.frostschutz",         &(cntrl_ww_par.frostschutz),         "%f" },
    { "ww_par.at_start",            &(cntrl_ww_par.at_start),            "%f" },
    { "ww_par.mv_korr",             &(cntrl_ww_par.mv_korr),             "%f" },
    { "ww_par.hzg_pu_y_min",        &(cntrl_ww_par.hzg_pu_y_min),        "%f" },
    { "ww_par.schwachlastzeit_max", &(cntrl_ww_par.schwachlastzeit_max), "%d" },
    
    { "ww_in.tww_mw",          &(cntrl_ww_in.tww_mw),          "%f" },
    { "ww_in.tau_mw",          &(cntrl_ww_in.tau_mw),          "%f" },
    { "ww_in.tau_avg",         &(cntrl_ww_in.tau_avg),         "%f" },
    { "ww_in.hzg_tvl_mw",      &(cntrl_ww_in.hzg_tvl_mw),      "%f" },
    { "ww_in.hzg_trl_mw",      &(cntrl_ww_in.hzg_trl_mw),      "%f" },
    { "ww_in.hk_tvl_sw",       &(cntrl_ww_in.hk_tvl_sw),       "%f" },
    { "ww_in.sp1_to_mw",       &(cntrl_ww_in.sp1_to_mw),       "%f" },
    { "ww_in.sp2_tu_mw",       &(cntrl_ww_in.sp2_tu_mw),       "%f" },
    { "ww_in.zirkzustand",     &(cntrl_ww_in.zirkzustand),     "%d" },
     
    { "ww_out.hzg_tvl_sw",     &(cntrl_ww_out.hzg_tvl_sw),     "%f" },
    { "ww_out.hzg_mv_y.y",     &(cntrl_ww_out.hzg_mv_y.y),     "%f" },
    { "ww_out.hzg_mv_y.y_1",   &(cntrl_ww_out.hzg_mv_y.y_1),   "%f" },
    { "ww_out.hzg_mv_y.xd_1",  &(cntrl_ww_out.hzg_mv_y.xd_1),  "%f" },
    { "ww_out.hzg_pu_y.y",     &(cntrl_ww_out.hzg_pu_y.y),     "%f" },
    { "ww_out.hzg_pu_y.y_1",   &(cntrl_ww_out.hzg_pu_y.y_1),   "%f" },
    { "ww_out.hzg_pu_y.xd_1",  &(cntrl_ww_out.hzg_pu_y.xd_1),  "%f" },
    { "ww_out.hzg_pu_sb",      &(cntrl_ww_out.hzg_pu_sb),      "%d" },
    { "ww_out.hzg_vv_sb",      &(cntrl_ww_out.hzg_vv_sb),      "%d" }
};

const parse_set_t telnet_sol_Vars[] =
{
    { "sol_par.sp_t_max",       &(cntrl_sol_par.sp_t_max),       "%f" }, 
    { "sol_par.dt_ein_sw",      &(cntrl_sol_par.dt_ein_sw),      "%f" },
    { "sol_par.dt_aus_sw",      &(cntrl_sol_par.dt_aus_sw),      "%f" },
    
    { "sol_in.koll_t_mw[KO1]",  &(cntrl_sol_in.koll_t_mw[KO1]),  "%f" },
    { "sol_in.t_sp[SP1].to_mw", &(cntrl_sol_in.t_sp[SP1].to_mw), "%f" },
    { "sol_in.t_sp[SP1].tu_mw", &(cntrl_sol_in.t_sp[SP1].tu_mw), "%f" },
    { "sol_in.t_sp[SP2].to_mw", &(cntrl_sol_in.t_sp[SP2].to_mw), "%f" },
    { "sol_in.t_sp[SP2].tu_mw", &(cntrl_sol_in.t_sp[SP2].tu_mw), "%f" },
     
    { "sol_out.av_sb[SP1]",     &(cntrl_sol_out.av_sb[SP1]),     "%d" },
    { "sol_out.av_sb[SP2]",     &(cntrl_sol_out.av_sb[SP2]),     "%d" },
    { "sol_out.pu_sb[KO1]",     &(cntrl_sol_out.pu_sb[SP1]),     "%d" }
};

/**
server_thread.
Server Threads die mit dem Client (Telnet, Heizungsregler oder Visualisierung)
kommunizieren
\param Client Socket Descriptor
\return Status
*/
void *telnet_thread( void *arg )
{
    char    bufin[BFLN], bufout[BFLN], *token;
    int     fdesc, *arglist;

    arglist = (int *) arg;
    fdesc = arglist[0];

    snprintf( bufout, BFLN, "\tRCA Heizungssteuerung Version 0.6.3\n" ); BFLSH();
    snprintf( bufout, BFLN, "\tAndreas und Volker Stegmann\n\n" );       BFLSH();
    snprintf( bufout, BFLN, "\tServer Prozess %d\n\n", arglist[1]+1 );   BFLSH();
    telnet_writeHelp( fdesc, bufout );

    while( 1 ) {
        if( read( fdesc, bufin, BFLN-1 ) == 0 ) {
            next_thread--;
            close( fdesc );
            pthread_exit( NULL );
        }
        else {
            token = strtok( bufin, "\n\r " );
            if( strncasecmp( "END", token, 3 ) == 0 ) {
                printf( "TELNET.C: END Befehl erhalten\n" );
                next_thread--;
                close( fdesc );
                pthread_exit( NULL );
            }
            if( strncasecmp( "HELP", token, 3 ) == 0 ) {
                printf( "TELNET.C: HELP Befehl erhalten\n" );
                telnet_writeHelp( fdesc, bufout );
            }
            else if( strncasecmp( "GET", token, 3 ) == 0 ) {
                printf( "TELNET.C: GET Befehl erhalten\n" );
                MUTEX_LOCK();
                telnet_parseGet( fdesc, bufout );
                MUTEX_UNLOCK();
            }
            else if( strncasecmp( "PUT", token, 3 ) == 0 ) {
                printf( "TELNET.C: PUT Befehl erhalten\n" );
                MUTEX_LOCK();
                telnet_parsePut( fdesc, bufout );
                MUTEX_UNLOCK();
            }
            else if( strncasecmp( "INIT", token, 4 ) == 0 ) {
                printf( "TELNET.C: INIT Befehl erhalten\n" );
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
                snprintf( bufout, BFLN, "TELNET: Parameter und Zeitprogramm initialisiert!\n\n" ); BFLSH();
            }
        }
    }
}

void telnet_writeHelp( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "\n Mögliche Befehle: \n\n" );                             BFLSH();
    snprintf( bufout, BFLN, "\t GET T     (alle Temperaturmesswerte)\n" );             BFLSH();
    snprintf( bufout, BFLN, "\t GET SW    (Sollwerte)\n" );                            BFLSH();
    snprintf( bufout, BFLN, "\t GET AO    (alle Analog-Ausgaenge)\n" );                BFLSH();
    snprintf( bufout, BFLN, "\t GET DI    (alle Digital-Eingaenge)\n" );               BFLSH();
    snprintf( bufout, BFLN, "\t GET DO    (alle Digital-Ausgaenge)\n" );               BFLSH();
    snprintf( bufout, BFLN, "\t GET FB    (Daten zu FB-Heizung)\n" );                  BFLSH();
    snprintf( bufout, BFLN, "\t GET WW    (Daten zu Warmwasserbereitung)\n" );         BFLSH();
    snprintf( bufout, BFLN, "\t GET SOL   (Daten zu Solarbeheizung)\n" );              BFLSH();
    snprintf( bufout, BFLN, "\t GET HK    (Daten zu Heizkörper-Heizkreis)\n" );        BFLSH();
    snprintf( bufout, BFLN, "\t INIT      (Initialisierungsdateien neu einlesen)\n" ); BFLSH();
    snprintf( bufout, BFLN, "\t GET PAR   (Eingelesene Parameter ausgeben)\n" );       BFLSH();
    snprintf( bufout, BFLN, "\t GET ZEIT  (Eingelesenes Zeitprogramm ausgeben)\n" );   BFLSH();
    snprintf( bufout, BFLN, "\t GET ABS   (Absenkungen ausgeben)\n" );                 BFLSH();
    snprintf( bufout, BFLN, "\t HELP      (Diesen Hilfetext ausgeben)\n" );            BFLSH();
    snprintf( bufout, BFLN, "\n\t GET VFB   (FB Modul: Parameter-, Eingangs- und Ausgangsvariablen)\n" ); BFLSH();
    snprintf( bufout, BFLN, "\t GET VHK   (HK Modul: Parameter-, Eingangs- und Ausgangsvariablen)\n" ); BFLSH();
    snprintf( bufout, BFLN, "\t GET VWW   (WW Modul: Parameter-, Eingangs- und Ausgangsvariablen)\n" ); BFLSH();
    snprintf( bufout, BFLN, "\t GET VSOL  (SOL Modul: Parameter-, Eingangs- und Ausgangsvariablen)\n" ); BFLSH();
    snprintf( bufout, BFLN, "\n\t END       (Datenabfrage beenden)\n" );                 BFLSH();
}

void telnet_parseGet( int fdesc, char *bufout )
{
    char *token;

    token = strtok( NULL, "\n\r " );
    if( strncasecmp( token, "T", 1 ) == 0 ) {
        telnet_writeT( fdesc, bufout );
    }
    else if( strncasecmp( token, "SW", 2 ) == 0 ) {
        telnet_writeSW( fdesc, bufout );
    }
    else if( strncasecmp( token, "DI", 2 ) == 0 ) {
        telnet_writeDI( fdesc, bufout );
    }
    else if( strncasecmp( token, "DO", 2 ) == 0 ) {
        telnet_writeDO( fdesc, bufout );
    }
    else if( strncasecmp( token, "AO", 2 ) == 0 ) {
        telnet_writeAO( fdesc, bufout );
    }
    else if( strncasecmp( token, "FB", 2 ) == 0 ) {
        telnet_writeFB( fdesc, bufout );
    }
    else if( strncasecmp( token, "WW", 2 ) == 0 ) {
        telnet_writeWW( fdesc, bufout );
    }
    else if( strncasecmp( token, "HK", 2 ) == 0 ) {
        telnet_writeHK( fdesc, bufout );
    }
    else if( strncasecmp( token, "SOL", 3 ) == 0 ) {
        telnet_writeSOL( fdesc, bufout );
    }
    else if( strncasecmp( token, "PAR", 3 ) == 0 ) {
        telnet_writeVorgabenparameter( fdesc, bufout );
    }
    else if( strncasecmp( token, "ZEIT", 4 ) == 0 ) {
        telnet_writeSchaltzeiten( fdesc, bufout );
    }
    else if( strncasecmp( token, "ABS", 3 ) == 0 ) {
        telnet_writeAbsenk( fdesc, bufout );
    }
    else if( strncasecmp( token, "VFB", 3 ) == 0 ) {
        telnet_writeVars( telnet_fb_Vars, sizeof(telnet_fb_Vars)/sizeof(parse_set_t), fdesc, bufout );
    }
    else if( strncasecmp( token, "VHK", 3 ) == 0 ) {
        telnet_writeVars( telnet_hk_Vars, sizeof(telnet_hk_Vars)/sizeof(parse_set_t), fdesc, bufout );
    }
    else if( strncasecmp( token, "VWW", 3 ) == 0 ) {
        telnet_writeVars( telnet_ww_Vars, sizeof(telnet_ww_Vars)/sizeof(parse_set_t), fdesc, bufout );
    }
    else if( strncasecmp( token, "VSOL", 4 ) == 0 ) {
        telnet_writeVars( telnet_sol_Vars, sizeof(telnet_sol_Vars)/sizeof(parse_set_t), fdesc, bufout );
    }
}
 
void telnet_parsePut( int fdesc, char *bufout )
{
    char *token;

    token = strtok( NULL, "\n\r " );
    if( strncasecmp( token, "PAR", 3 ) == 0 ) {
        // todo
    }
}

void telnet_writeVorgabenparameter( int fdesc, char *bufout )
{
    int n;
    
    for( n=0; n<param_Vorgaben_len; n++ ) {
        snprintf( bufout, BFLN, param_Vorgaben[n].VarName ); BFLSH();
        snprintf( bufout, BFLN, " = " ); BFLSH();
        switch ( param_Vorgaben[n].format[1] ) {
            case 'd':
                snprintf( bufout, BFLN, param_Vorgaben[n].format, *(int *)param_Vorgaben[n].VarPointer ); BFLSH();
                break;
            case 'f':
            default:
                snprintf( bufout, BFLN, param_Vorgaben[n].format, *(float *)param_Vorgaben[n].VarPointer ); BFLSH();
                break;
        }
        snprintf( bufout, BFLN, "\n" ); BFLSH();
    }
}

void telnet_minToTime( s16_t t, s16_t *d, s16_t *h, s16_t *m )
{
    s16_t tmp;
    
    tmp  = t;
    *m   = tmp % 60;
    tmp  /= 60;
    *h   = tmp % 24;
    tmp  /= 24;
    *d = tmp % 7;
}    
        
void telnet_writeSchaltzeiten( int fdesc, char *bufout )
{
    s16_t n;
    s16_t d_ein, h_ein, m_ein;
    s16_t d_aus, h_aus, m_aus;
   
    for( n=0; n<hk_states; n++ ) {
        telnet_minToTime( HK_Ein_Schaltzeiten[n], &d_ein, &h_ein, &m_ein );
        telnet_minToTime( HK_Aus_Schaltzeiten[n], &d_aus, &h_aus, &m_aus );
        snprintf( bufout, BFLN, "HK_Ein_Schaltzeiten[%d]    = %1d-%02d:%02d, HK_Aus_Schaltzeiten[%d]    = %1d-%02d:%02d\n",
                n, d_ein, h_ein, m_ein, n, d_aus, h_aus, m_aus );
        BFLSH();
    }
    for( n=0; n<fb_states; n++ ) {
        telnet_minToTime( FB_Ein_Schaltzeiten[n], &d_ein, &h_ein, &m_ein );
        telnet_minToTime( FB_Aus_Schaltzeiten[n], &d_aus, &h_aus, &m_aus );
        snprintf( bufout, BFLN, "FB_Ein_Schaltzeiten[%d]    = %1d-%02d:%02d, FB_Aus_Schaltzeiten[%d]    = %1d-%02d:%02d\n",
                n, d_ein, h_ein, m_ein, n, d_aus, h_aus, m_aus );
        BFLSH();
    }
    for( n=0; n<zirk_states; n++ ) {
        telnet_minToTime( ZIRK_Ein_Schaltzeiten[n], &d_ein, &h_ein, &m_ein );
        telnet_minToTime( ZIRK_Aus_Schaltzeiten[n], &d_aus, &h_aus, &m_aus );
        snprintf( bufout, BFLN, "ZIRK_Ein_Schaltzeiten[%d]  = %1d-%02d:%02d, ZIRK_Aus_Schaltzeiten[%d]  = %1d-%02d:%02d\n",
                n, d_ein, h_ein, m_ein, n, d_aus, h_aus, m_aus );
        BFLSH();
    }
    for( n=0; n<dusch_states; n++ ) {
        telnet_minToTime( DUSCH_Ein_Schaltzeiten[n], &d_ein, &h_ein, &m_ein );
        telnet_minToTime( DUSCH_Aus_Schaltzeiten[n], &d_aus, &h_aus, &m_aus );
        snprintf( bufout, BFLN, "DUSCH_Ein_Schaltzeiten[%d] = %1d-%02d:%02d, DUSCH_Aus_Schaltzeiten[%d] = %1d-%02d:%02d\n",
                n, d_ein, h_ein, m_ein, n, d_aus, h_aus, m_aus );
        BFLSH();
    }
    snprintf( bufout, BFLN,"HOUR_OFFSET = %d\n\n", zeit_hour_offset );  
    BFLSH();
}

void telnet_writeT( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "ALL_Tau_MW     = %5.1f °C\n", io_get_ALL_Tau_MW() );       BFLSH();
    snprintf( bufout, BFLN, "SOL_KOLL_T_MW  = %5.1f °C\n", io_get_SOL_KOLL_T_MW() );    BFLSH();
    snprintf( bufout, BFLN, "SOL_SP1_To_MW  = %5.1f °C\n", io_get_SOL_SP1_To_MW() );    BFLSH();
    snprintf( bufout, BFLN, "SOL_SP1_Tu_MW  = %5.1f °C\n", io_get_SOL_SP1_Tu_MW() );    BFLSH();
    snprintf( bufout, BFLN, "SOL_SP2_To_MW  = %5.1f °C\n", io_get_SOL_SP2_To_MW() );    BFLSH();
    snprintf( bufout, BFLN, "SOL_SP2_Tu_MW  = %5.1f °C\n", io_get_SOL_SP2_Tu_MW() );    BFLSH();
    snprintf( bufout, BFLN, "KES_Tvl_MW     = %5.1f °C\n", io_get_KES_Tvl_MW() );       BFLSH();
    snprintf( bufout, BFLN, "KES_Trl_MW     = %5.1f °C\n", io_get_KES_Trl_MW() );       BFLSH();
    snprintf( bufout, BFLN, "HK_Tvl_MW      = %5.1f °C\n", io_get_HK_Tvl_MW() );        BFLSH();
    snprintf( bufout, BFLN, "HK_Trl_MW      = %5.1f °C\n", io_get_HK_Trl_MW() );        BFLSH();
    snprintf( bufout, BFLN, "FB_PRIM_Trl_MW = %5.1f °C\n", io_get_FB_PRIM_Trl_MW() );   BFLSH();
    snprintf( bufout, BFLN, "FB_SEK_Tvl_MW  = %5.1f °C\n", io_get_FB_SEK_Tvl_MW() );    BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_Tvl_MW  = %5.1f °C\n", io_get_WW_HZG_Tvl_MW() );    BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_Trl_MW  = %5.1f °C\n", io_get_WW_HZG_Trl_MW() );    BFLSH();
    snprintf( bufout, BFLN, "WW_Tww_MW      = %5.1f °C\n", io_get_WW_Tww_MW() );        BFLSH();
    snprintf( bufout, BFLN, "Tau_1h_mittel  = %6.2f °C\n", cntrl_tau.t_1h_mittel );     BFLSH();
    snprintf( bufout, BFLN, "Tau_36h_mittel = %6.2f °C\n", cntrl_tau.t_36h_mittel );    BFLSH();
}    

void telnet_writeSW( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "kes_out.tvl_sw_sp1 = %5.1f °C\t kes_out.sp1_to_sw = %5.1f °C\n", 
              cntrl_kes_out.tvl_sw_sp1, cntrl_kes_out.sp1_to_sw ); 
    BFLSH();
    snprintf( bufout, BFLN, "kes_out.tvl_sw_sp2 = %5.1f °C\t kes_out.sp2_to_sw = %5.1f °C\n", 
              cntrl_kes_out.tvl_sw_sp2, cntrl_kes_out.sp2_to_sw ); 
    BFLSH();

    snprintf( bufout, BFLN, "fb_out.tvl_sw = %5.1f °C ", cntrl_fb_out.tvl_sw ); BFLSH();
    if( cntrl_zeit_absenkung.FB_Zustand == zAbgesenkt )
        snprintf( bufout, BFLN, "(abgesenkt um %5.1f °C)\n", cntrl_fb_par.tvl_absenk );
    else
        snprintf( bufout, BFLN, "(Normalbetrieb)\n" );
    BFLSH();

    snprintf( bufout, BFLN, "hk_out.tvl_sw = %5.1f °C ", cntrl_hk_out.tvl_sw ); BFLSH();
    if( cntrl_zeit_absenkung.HK_Zustand == zAbgesenkt )
        snprintf( bufout, BFLN, "(abgesenkt um %5.1f °C)\n", cntrl_hk_par.tvl_absenk );
    else
        snprintf( bufout, BFLN, "(Normalbetrieb)\n" );
    BFLSH();
    
    snprintf( bufout, BFLN, "ww_par.tww_sw = %5.1f °C ", cntrl_ww_par.tww_sw ); BFLSH();
    if( cntrl_zeit_absenkung.Duschzeit == zNein )
        snprintf( bufout, BFLN, "(keine Duschzeit)\n" );
    else
        snprintf( bufout, BFLN, "(Duschzeit)\n" );
    BFLSH();
}

void telnet_writeAbsenk( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "HK_Zustand       = %s\n",
              (cntrl_zeit_absenkung.HK_Zustand == zAbgesenkt) ? "Abgesenkt" : "Normal" );     BFLSH();
    snprintf( bufout, BFLN, "FB_Zustand       = %s\n",
              (cntrl_zeit_absenkung.FB_Zustand == zAbgesenkt) ? "Abgesenkt" : "Normal" );     BFLSH();
    snprintf( bufout, BFLN, "Zirk_Zustand     = %s\n",
              (cntrl_zeit_absenkung.Zirk_Zustand == zAus) ? "Aus" : "Ein" );                  BFLSH();
    snprintf( bufout, BFLN, "Duschzeit        = %s\n",
              (cntrl_zeit_absenkung.Duschzeit == zNein) ? "Nein" : "Ja" );                    BFLSH();
    snprintf( bufout, BFLN, "SP1_Freigabe     = %s\n",
              (cntrl_zeit_absenkung.SP1_Freigabe == zGesperrt) ? "Gesperrt" : "Freigegeben" ); BFLSH();
    snprintf( bufout, BFLN, "SP2_Freigabe     = %s\n",
              (cntrl_zeit_absenkung.SP2_Freigabe == zGesperrt) ? "Gesperrt" : "Freigegeben" ); BFLSH();
    snprintf( bufout, BFLN, "Bootshausnutzung = %s\n",
              (cntrl_zeit_absenkung.Bootshausnutzung == zNein) ? "Nein" : "Ja" );             BFLSH();
   if (io_get_WW_PARTY() != IO_AUS) {
        snprintf( bufout, BFLN, "\t seit %d min, noch %d min aktiv\n",
        param_all_partydauer - cntrl_zeit_party.ww_party_restzeit_min, cntrl_zeit_party.ww_party_restzeit_min );
        BFLSH();
    }
}
  
void telnet_writeDI( int fdesc, char *bufout )
{
    /* Allgemeiner Partyschalter */
    snprintf( bufout, BFLN, "ALL_PARTY = %s", (io_get_ALL_PARTY() == IO_AUS) ? "AUS\n" : "EIN" ); BFLSH();
    if (io_get_ALL_PARTY() != IO_AUS) {
        snprintf( bufout, BFLN, "\t seit %d min, noch %d min aktiv\n",
        param_all_partydauer - cntrl_zeit_party.all_party_restzeit_min, cntrl_zeit_party.all_party_restzeit_min );
        BFLSH();
    }
    /* Warmwasser Partyschalter */
    snprintf( bufout, BFLN, "WW_PARTY = %s", (io_get_WW_PARTY() == IO_AUS) ? "AUS\n" : "EIN" ); BFLSH();
    if (io_get_WW_PARTY() != IO_AUS) {
        snprintf( bufout, BFLN, "\t seit %d min, noch %d min aktiv\n",
        param_all_partydauer - cntrl_zeit_party.ww_party_restzeit_min, cntrl_zeit_party.ww_party_restzeit_min );
        BFLSH();
    }
    /* Kesselstörmeldung */
    snprintf( bufout, BFLN, "KES_SSM = %s\n", (io_get_KES_SSM() == IO_AUS) ? "NORMAL (0)" : "STÖRUNG (1)" ); BFLSH();
    /* Kessel Brennerbetriebsmeldung */
    snprintf( bufout, BFLN, "KES_BR_BM = %s\n", (io_get_KES_BR_BM() == IO_AUS) ? "AUS" : "EIN" ); BFLSH();
    /* Fußbodenheizung Sekundärseite Sicherheitstemperaturbegrenzer */
    snprintf( bufout, BFLN, "FB_SEK_TW = %s\n", (io_get_FB_SEK_TW() == IO_AUS) ?  "STÖRUNG (0)" : "NORMAL (1)" ); BFLSH();
}

void telnet_writeDO( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "SOL_PU_SB = %s\n", (io_get_SOL_PU_SB() == IO_AUS) ? "AUS" : "EIN" );         BFLSH();
    snprintf( bufout, BFLN, "SOL_SP1_AV_SB = %s\n", (io_get_SOL_SP1_AV_SB() == IO_AUS) ? "ZU" : "AUF" );  BFLSH();
    snprintf( bufout, BFLN, "SOL_SP2_AV_SB = %s\n", (io_get_SOL_SP2_AV_SB() == IO_AUS) ? "ZU" : "AUF" );  BFLSH();
    snprintf( bufout, BFLN, "KES_PU_SP1_SB = %s\n", (io_get_KES_PU_SP1_SB() == IO_AUS) ? "AUS" : "EIN" ); BFLSH();
    snprintf( bufout, BFLN, "KES_PU_SP2_SB = %s\n", (io_get_KES_PU_SP2_SB() == IO_AUS) ? "AUS" : "EIN" ); BFLSH();
    snprintf( bufout, BFLN, "HK_PU_SB = %s\n", (io_get_HK_PU_SB() == IO_AUS) ? "AUS" : "EIN" );           BFLSH();
    snprintf( bufout, BFLN, "FB_PRIM_PU_SB = %s\n", (io_get_FB_PRIM_PU_SB() == IO_AUS) ? "AUS" : "EIN" ); BFLSH();
    snprintf( bufout, BFLN, "FB_SEK_PU_SB = %s\n", (io_get_FB_SEK_PU_SB() == IO_AUS) ? "AUS" : "EIN" );   BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_VV_SB = %s\n", (io_get_WW_HZG_VV_SB() == IO_AUS) ? "ZU" : "AUF" );    BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_PU_SB = %s\n", (io_get_WW_HZG_PU_SB() == IO_AUS) ? "AUS" : "EIN" );   BFLSH();
    snprintf( bufout, BFLN, "WW_ZIRK_PU_SB = %s\n", (io_get_WW_ZIRK_PU_SB() == IO_AUS) ? "AUS" : "EIN" ); BFLSH();
}

void telnet_writeAO( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "KES_Tvl_Y    = %5.1f pct\n", io_get_KES_Tvl_Y() );        BFLSH();
    snprintf( bufout, BFLN, "HK_MV_Y      = %5.1f pct\n", io_get_HK_MV_Y() );          BFLSH();
    snprintf( bufout, BFLN, "FB_PRIM_MV_Y = %5.1f pct\n", io_get_FB_PRIM_MV_Y() );     BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_MV_Y  = %5.1f pct\n", io_get_WW_HZG_MV_Y() );      BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_PU_Y  = %5.1f pct\n", io_get_WW_HZG_PU_Y() );      BFLSH();
}

void telnet_writeFB( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "FB_PRIM_Trl_MW = %5.1f °C\n", io_get_FB_PRIM_Trl_MW() );                      BFLSH();
    snprintf( bufout, BFLN, "FB_SEK_Tvl_MW  = %5.1f °C\n", io_get_FB_SEK_Tvl_MW() );                       BFLSH();
    snprintf( bufout, BFLN, "FB_PRIM_MV_Y   = %5.1f pct\n", io_get_FB_PRIM_MV_Y() );                       BFLSH();
    snprintf( bufout, BFLN, "FB_PRIM_PU_SB  = %s\n", (io_get_FB_PRIM_PU_SB() == IO_AUS) ? "AUS" : "EIN" ); BFLSH();
    snprintf( bufout, BFLN, "FB_SEK_PU_SB   = %s\n", (io_get_FB_SEK_PU_SB() == IO_AUS) ? "AUS" : "EIN" );  BFLSH();
    snprintf( bufout, BFLN, "ALL_PARTY      = %s", (io_get_ALL_PARTY() == IO_AUS) ? "AUS\n" : "EIN" );     BFLSH();
    if (io_get_ALL_PARTY() != 0x00) {
        snprintf( bufout, BFLN, "\t seit %d min, noch %d min aktiv\n",
        param_all_partydauer - cntrl_zeit_party.all_party_restzeit_min, cntrl_zeit_party.all_party_restzeit_min );
        BFLSH();
    }
}

void telnet_writeWW( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "ww_tww_sw        = %5.1f °C", cntrl_ww_par.tww_sw ); BFLSH();
    if( cntrl_zeit_absenkung.Duschzeit == zNein )
        snprintf( bufout, BFLN, " (keine Duschzeit)\n" );
    else
        snprintf( bufout, BFLN, " (Duschzeit)\n" );
    BFLSH();
    snprintf( bufout, BFLN, "WW_Tww_MW        = %5.1f °C\n", io_get_WW_Tww_MW() );      BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_Tvl_MW    = %5.1f °C\n", io_get_WW_HZG_Tvl_MW() );  BFLSH();
    snprintf( bufout, BFLN, "kes_out.tvl_sw_sp1 = %5.1f °C\t kes_out.sp1_to_sw = %5.1f °C\n", 
              cntrl_kes_out.tvl_sw_sp1, cntrl_kes_out.sp1_to_sw ); BFLSH();
    snprintf( bufout, BFLN, "SOL_SP1_To_MW    = %5.1f °C\n", io_get_SOL_SP1_To_MW() );  BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_Tvl_MW    = %5.1f °C\n", io_get_WW_HZG_Tvl_MW() );  BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_Trl_MW    = %5.1f °C\n", io_get_WW_HZG_Trl_MW() );  BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_VV_SB     = %s\n", (io_get_WW_HZG_VV_SB() == IO_ZU) ? "ZU" : "AUF" );   BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_PU_SB     = %s\n", (io_get_WW_HZG_PU_SB() == IO_AUS) ? "AUS" : "EIN" ); BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_MV_Y      = %5.1f pct\n", io_get_WW_HZG_MV_Y() );   BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_PU_Y      = %5.1f pct\n", io_get_WW_HZG_PU_Y() );   BFLSH();
    snprintf( bufout, BFLN, "WW_PARTY = %s", (io_get_WW_PARTY() == IO_AUS) ? "AUS\n" : "EIN" ); BFLSH();
    if (io_get_WW_PARTY() != IO_AUS) {
        snprintf( bufout, BFLN, "\t seit %d min, noch %d min aktiv\n",
        param_all_partydauer - cntrl_zeit_party.ww_party_restzeit_min, cntrl_zeit_party.ww_party_restzeit_min );
        BFLSH();
    }
}

void telnet_writeHK( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "HK_Tvl_MW = %5.1f °C\n", io_get_HK_Tvl_MW() );                      BFLSH();
    snprintf( bufout, BFLN, "HK_Trl_MW = %5.1f °C\n", io_get_HK_Trl_MW() );                      BFLSH();
    snprintf( bufout, BFLN, "HK_MV_Y   = %5.1f pct\n", io_get_HK_MV_Y() );                       BFLSH();
    snprintf( bufout, BFLN, "HK_PU_SB  = %s\n", (io_get_HK_PU_SB() == IO_AUS) ? "AUS" : "EIN" ); BFLSH();
}

void telnet_writeSOL( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "SOL_KOLL_T_MW = %5.1f °C\n", io_get_SOL_KOLL_T_MW() );                     BFLSH();
    snprintf( bufout, BFLN, "SOL_SP1_To_MW = %5.1f °C\n", io_get_SOL_SP1_To_MW() );                     BFLSH();
    snprintf( bufout, BFLN, "SOL_SP1_Tu_MW = %5.1f °C\n", io_get_SOL_SP1_Tu_MW() );                     BFLSH();
    snprintf( bufout, BFLN, "SOL_SP2_To_MW = %5.1f °C\n", io_get_SOL_SP2_To_MW() );                     BFLSH();
    snprintf( bufout, BFLN, "SOL_SP2_Tu_MW = %5.1f °C\n", io_get_SOL_SP2_Tu_MW() );                     BFLSH();
    snprintf( bufout, BFLN, "SOL_PU_SB     = %s\n", (io_get_SOL_PU_SB() == IO_AUS) ? "AUS" : "EIN" );   BFLSH();
    snprintf( bufout, BFLN, "SOL_SP1_AV_SB = %s\n", (io_get_SOL_SP1_AV_SB() == IO_ZU) ? "ZU" : "AUF" ); BFLSH();
    snprintf( bufout, BFLN, "SOL_SP2_AV_SB = %s\n", (io_get_SOL_SP2_AV_SB() == IO_ZU) ? "ZU" : "AUF" ); BFLSH();
}

void telnet_writeVars( const parse_set_t Vars[], int len, int fdesc, char *bufout )
{
    int n;
    
    for( n=0; n<len; n++ ) {
        snprintf( bufout, BFLN, Vars[n].VarName ); BFLSH();
        snprintf( bufout, BFLN, " = " ); BFLSH();
        switch ( Vars[n].format[1] ) {
            case 'd':
                snprintf( bufout, BFLN, Vars[n].format, *(int *)Vars[n].VarPointer ); BFLSH();
                break;
            case 'f':
            default:
                snprintf( bufout, BFLN, Vars[n].format, *(float *)Vars[n].VarPointer ); BFLSH();
                break;
        }
        snprintf( bufout, BFLN, "\n" ); BFLSH();
    }
}


