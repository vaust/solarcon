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

    snprintf( bufout, BFLN, "\tRCA Heizungssteuerung Version 0.6.2\n" ); BFLSH();
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
    snprintf( bufout, BFLN, "\t HELP      (Diesen Hilfetext ausgeben)\n" );            BFLSH();
    snprintf( bufout, BFLN, "\t END       (Datenabfrage beenden)\n" );                 BFLSH();
}

void telnet_parseGet( int fdesc, char *bufout )
{
    char *token;

    token = strtok( NULL, "\n\r " );
    if( strncasecmp( token, "T", 1 ) == 0 ) {
        telnet_writeT( fdesc, bufout );
    }
    else if( strncasecmp( token, "SW", 2 ) == 0 ) {
        // telnet_writeSW();
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
        // telnet_writeWW();
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

// void telnet_writeSW( void )
// {
    // snprintf( bufout, BFLN, "kes_Tvl_SW_Sp2_f = %5.1f °C\t sol_SP2_To_SW_f= %5.1f °C\n", 
              // kes_Tvl_SW_Sp2_f, sol_SP2_To_SW_f ); 
    // BFLSH();
    // if( z_FB_Zustand == zAbgesenkt )
        // snprintf( bufout, BFLN, "fb_Tvl_SW_f = %5.1f °C (abgesenkt um %5.1f °C)\n", fb_Tvl_SW_f, fb_tvl_absenk );
        // else
        // snprintf( bufout, BFLN, "fb_Tvl_SW_f = %5.1f °C (Normalbetrieb)\n", fb_Tvl_SW_f );
    // BFLSH();

    // if( z_HK_Zustand == zAbgesenkt )
        // snprintf( bufout, BFLN, "hk_Tvl_SW_f = %5.1f °C (abgesenkt um %5.1f °C)\n", hk_Tvl_SW_f, hk_tvl_absenk );
    // else
        // snprintf( bufout, BFLN, "hk_Tvl_SW_f = %5.1f °C (Normalbetrieb)\n", hk_Tvl_SW_f);
    // BFLSH();

    // snprintf( bufout, BFLN, "kes_Tvl_SW_Sp1_f = %5.1f °C\t sol_SP1_To_SW_f= %5.1f °C\n", kes_Tvl_SW_Sp1_f, sol_SP1_To_SW_f );
    // BFLSH();

    // if( z_Duschzeit == zNein )
        // snprintf( bufout, BFLN, "ww_tww_sw   = %5.1f °C (keine Duschzeit)\n",  ww_tww_sw );
    // else
        // snprintf( bufout, BFLN, "ww_tww_sw   = %5.1f °C (Duschzeit)\n",  ww_tww_sw );
    // BFLSH();
// }

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
    // snprintf( bufout, BFLN, "kes_Tvl_SW_Sp1_f = %5.1f °C\t sol_SP1_To_SW_f= %5.1f °C\n", kes_Tvl_SW_Sp1_f, sol_SP1_To_SW_f ); BFLSH();
    snprintf( bufout, BFLN, "SOL_SP1_To_MW    = %5.1f °C\n", io_get_SOL_SP1_To_MW() );  BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_Tvl_MW    = %5.1f °C\n", io_get_WW_HZG_Tvl_MW() );  BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_Trl_MW    = %5.1f °C\n", io_get_WW_HZG_Trl_MW() );  BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_VV_SB     = %s\n", (io_get_WW_HZG_VV_SB() == IO_ZU) ? "ZU" : "AUF" );  BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_PU_SB     = %s\n", (io_get_WW_HZG_PU_SB() == IO_AUS) ? "AUS" : "EIN" ); BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_MV_Y      = %5.1f pct\n", io_get_WW_HZG_MV_Y() );   BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_PU_Y      = %5.1f pct\n", io_get_WW_HZG_PU_Y() );   BFLSH();
    snprintf( bufout, BFLN, "WW_PARTY = %s", (io_get_WW_PARTY() == IO_AUS) ? "AUS\n" : "EIN" );    BFLSH();
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


