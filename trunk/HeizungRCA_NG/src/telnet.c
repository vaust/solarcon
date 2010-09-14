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

#include "param.h"
#include "io.h"
#include "cntrl.h"

#define BFLN        64
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

    snprintf( bufout, BFLN, "RCA Heizungssteuerung Version 0.6.1\n" );                 BFLSH();
    snprintf( bufout, BFLN, "Andreas und Volker Stegmann\n\n" );                       BFLSH();
    snprintf( bufout, BFLN, "Server Prozess %d\n\n", arglist[1]+1 );                   BFLSH();
    snprintf( bufout, BFLN, "\n Mögliche Befehle: \n\n" );                             BFLSH();
    snprintf( bufout, BFLN, "\t GET T (alle Temperaturmesswerte)\n" );                 BFLSH();
    snprintf( bufout, BFLN, "\t GET SW    (Sollwerte)\n" );                            BFLSH();
    snprintf( bufout, BFLN, "\t GET AO    (alle Analog-Ausgaenge)\n" );                BFLSH();
    snprintf( bufout, BFLN, "\t GET DI    (alle Digital-Eingaenge)\n" );               BFLSH();
    snprintf( bufout, BFLN, "\t GET DO    (alle Digital-Ausgaenge)\n" );               BFLSH();
    snprintf( bufout, BFLN, "\t GET FB    (Daten zu FB-Heizung)\n" );                  BFLSH();
    snprintf( bufout, BFLN, "\t GET WW    (Daten zu Warmwasserbereitung)\n" );         BFLSH();
    snprintf( bufout, BFLN, "\t GET SOL   (Daten zu Solarbeheizung)\n" );              BFLSH();
    snprintf( bufout, BFLN, "\t GET HK    (Daten zu Heizkörper-Heizkreis)\n" );        BFLSH();
    snprintf( bufout, BFLN, "\t INIT      (Initialisierungsdateien neu einlesen)\n" ); BFLSH();
    snprintf( bufout, BFLN, "\t END       (Datenabfrage beenden)\n" );                 BFLSH();

    while( 1 ) {
        if( read( fdesc, bufin, BFLN-1 ) == 0 ) {
            next_thread--;
            close( fdesc );
            pthread_exit( NULL );
        }
        else {
            token = strtok( bufin, "\n\r " );
            if( strncasecmp( "END", token, 3 ) == 0 ) {
                printf( "TELNET: END Befehl erhalten\n" );
                next_thread--;
                close( fdesc );
                pthread_exit( NULL );
            }
            else if( strncasecmp( "GET", token, 3 ) == 0 ) {
                printf( "TELNET: GET Befehl erhalten\n" );
                MUTEX_LOCK();
                telnet_parseGet( fdesc, bufout );
                MUTEX_UNLOCK();
            }
            else if( strncasecmp( "PUT", token, 3 ) == 0 ) {
                printf( "TELNET: PUT Befehl erhalten\n" );
            }
            else if( strncasecmp( "INIT", token, 4 ) == 0 ) {
                printf( "TELNET: INIT Befehl erhalten\n" );
                MUTEX_LOCK();
                param_Init();
                zeit_Init( &cntrl_zeit_absenkung, &cntrl_zeit_event );
                MUTEX_UNLOCK();
                snprintf( bufout, BFLN, "Parameter, Variablen und Zeitprogramm initialisiert!\n\n" ); BFLSH();
            }
        }
    }
}

void telnet_writeTemp( void )
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
    snprintf( bufout, BFLN, "Tau_1h_mittel_f  = %6.2f °C\n", cntrl_tau.t_1h_mittel );   BFLSH();
    snprintf( bufout, BFLN, "Tau_36h_mittel_f = %6.2f °C\n", cntrl_tau.t_36h_mittel );  BFLSH();
}    

int telnet_parseGet( int fdesc, char *bufout )
{
    char *token;

    token = strtok( NULL, "\n\r " );
    if( strncasecmp( token, "T", 1 ) == 0 ) {
        telnet_writeTemp();
    }
    else if( strncasecmp( token, "SW", 2 ) == 0 ) {

        snprintf( bufout, BFLN, "kes_Tvl_SW_Sp2_f = %5.1f °C\t sol_SP2_To_SW_f= %5.1f °C\n", kes_Tvl_SW_Sp2_f, sol_SP2_To_SW_f );        BFLSH();
        if( z_FB_Zustand == zAbgesenkt )
            snprintf( bufout, BFLN, "fb_Tvl_SW_f = %5.1f °C (abgesenkt um %5.1f °C)\n", fb_Tvl_SW_f, fb_tvl_absenk );
            else
            snprintf( bufout, BFLN, "fb_Tvl_SW_f = %5.1f °C (Normalbetrieb)\n", fb_Tvl_SW_f );
        BFLSH();

        if( z_HK_Zustand == zAbgesenkt )
            snprintf( bufout, BFLN, "hk_Tvl_SW_f = %5.1f °C (abgesenkt um %5.1f °C)\n", hk_Tvl_SW_f, hk_tvl_absenk );
        else
            snprintf( bufout, BFLN, "hk_Tvl_SW_f = %5.1f °C (Normalbetrieb)\n", hk_Tvl_SW_f);
        BFLSH();

        snprintf( bufout, BFLN, "kes_Tvl_SW_Sp1_f = %5.1f °C\t sol_SP1_To_SW_f= %5.1f °C\n", kes_Tvl_SW_Sp1_f, sol_SP1_To_SW_f );
        BFLSH();
        if( z_Duschzeit == zNein )
            snprintf( bufout, BFLN, "ww_tww_sw   = %5.1f °C (keine Duschzeit)\n",  ww_tww_sw );
        else
            snprintf( bufout, BFLN, "ww_tww_sw   = %5.1f °C (Duschzeit)\n",  ww_tww_sw );
        BFLSH();
    }
    else if( strncasecmp( token, "DI", 2 ) == 0 ) {
        /* Allgemeiner Partyschalter */
        snprintf( bufout, BFLN, "ALL_PARTY = %s", (ALL_PARTY == 0x00) ? "AUS\n" : "EIN" );
        BFLSH();
        if (ALL_PARTY != 0x00) {
            snprintf( bufout, BFLN, "\t seit %d min, noch %d min aktiv\n",
            all_partydauer - all_party_restzeit_min, all_party_restzeit_min );
            BFLSH();
        }
        /* Warmwasser Partyschalter */
        snprintf( bufout, BFLN, "WW_PARTY = %s", (WW_PARTY == 0x00) ? "AUS\n" : "EIN" );
        BFLSH();
        if (WW_PARTY != 0x00) {
            snprintf( bufout, BFLN, "\t seit %d min, noch %d min aktiv\n",
            all_partydauer - ww_party_restzeit_min, ww_party_restzeit_min );
            BFLSH();
        }
        /* Kesselstörmeldung */
        snprintf( bufout, BFLN, "KES_SSM = %s\n", (KES_SSM == 0x00) ? "NORMAL (0)" : "STÖRUNG (1)" );
        BFLSH();
        /* Kessel Brennerbetriebsmeldung */
        snprintf( bufout, BFLN, "KES_BR_BM = %s\n", (KES_BR_BM == 0x00) ? "AUS" : "EIN" );
        BFLSH();
        /* Fußbodenheizung Sekundärseite Sicherheitstemperaturbegrenzer */
        snprintf( bufout, BFLN, "FB_SEK_TW = %s\n", (FB_SEK_TW == 0x00) ?  "STÖRUNG (0)" : "NORMAL (1)" );
        BFLSH();
    }
    else if( strncasecmp( token, "DO", 2 ) == 0 ) {
        /* Solarkreispumpe */
        snprintf( bufout, BFLN, "SOL_PU_SB = %s\n", (SOL_PU_SB == 0x00) ? "AUS" : "EIN" );        BFLSH();
        /* Solarabsperrventil Speicher 1 */
        snprintf( bufout, BFLN, "SOL_SP1_AV_SB = %s\n", (SOL_SP1_AV_SB == 0x00) ? "ZU" : "AUF" );        BFLSH();
        /* Solarabsperrventil Speicher 2 */
        snprintf( bufout, BFLN, "SOL_SP2_AV_SB = %s\n", (SOL_SP2_AV_SB == 0x00) ? "ZU" : "AUF" );        BFLSH();
        /* Kessel Ladepumpe Speicher 1 */
        snprintf( bufout, BFLN, "KES_PU_SP1_SB = %s\n", (KES_PU_SP1_SB == 0x00) ? "AUS" : "EIN" );        BFLSH();
        /* Kessel Ladepumpe Speicher 2 */
        snprintf( bufout, BFLN, "KES_PU_SP2_SB = %s\n", (KES_PU_SP2_SB == 0x00) ? "AUS" : "EIN" );        BFLSH();
        /* Heizkoeerperheizkreispumpe */
        snprintf( bufout, BFLN, "HK_PU_SB = %s\n", (HK_PU_SB == 0x00) ? "AUS" : "EIN" );        BFLSH();
        /* Fußbodenheizung Wärmetauscher Primärkreispumpe */
        snprintf( bufout, BFLN, "FB_PRIM_PU_SB = %s\n", (FB_PRIM_PU_SB == 0x00) ? "AUS" : "EIN" );        BFLSH();
        /* Fußbodenheizung Wärmetauscher Sekundärkreispumpe */
        snprintf( bufout, BFLN, "FB_SEK_PU_SB = %s\n", (FB_SEK_PU_SB == 0x00) ? "AUS" : "EIN" );        BFLSH();
        /* Warmwasser / Heizung Verteilventil für Energiemanagement */
        snprintf( bufout, BFLN, "WW_HZG_VV_SB = %s\n", (WW_HZG_VV_SB == 0x00) ? "ZU" : "AUF" );        BFLSH();
        /* Warmwasserheizungspumpe */
        snprintf( bufout, BFLN, "WW_HZG_PU_SB = %s\n", (WW_HZG_PU_SB == 0x00) ? "AUS" : "EIN" );        BFLSH();
        /* Zirkulationspumpe */
        snprintf( bufout, BFLN, "WW_ZIRK_PU_SB = %s\n", (WW_ZIRK_PU_SB == 0x00) ? "AUS" : "EIN" );        BFLSH();
    }
    else if( strncasecmp( token, "AO", 2 ) == 0 ) {
        snprintf( bufout, BFLN, "KES_Tvl_Y    = %5d pct\n", KES_Tvl_Y/328 );        BFLSH();
        snprintf( bufout, BFLN, "HK_MV_Y      = %5d pct\n", HK_MV_Y/328 );        BFLSH();
        snprintf( bufout, BFLN, "FB_PRIM_MV_Y = %5d pct\n", FB_PRIM_MV_Y/328 );        BFLSH();
        snprintf( bufout, BFLN, "WW_HZG_MV_Y  = %5d pct\n", WW_HZG_MV_Y/328 );        BFLSH();
        snprintf( bufout, BFLN, "WW_HZG_PU_Y  = %5d pct\n", WW_HZG_PU_Y/328 );        BFLSH();
    }
    else if( strncasecmp( token, "FB", 2 ) == 0 ) {
        snprintf( bufout, BFLN, "FB_PRIM_Trl_MW = %5.1f °C\n", FB_PRIM_Trl_MW );        BFLSH();
        snprintf( bufout, BFLN, "FB_SEK_Tvl_MW  = %5.1f °C\n", FB_SEK_Tvl_MW );        BFLSH();
        snprintf( bufout, BFLN, "FB_PRIM_MV_Y   = %5d pct\n", FB_PRIM_MV_Y/328 );        BFLSH();
        snprintf( bufout, BFLN, "FB_PRIM_PU_SB  = %s\n", (FB_PRIM_PU_SB == 0x00) ? "AUS" : "EIN" );        BFLSH();
        snprintf( bufout, BFLN, "FB_SEK_PU_SB   = %s\n", (FB_SEK_PU_SB == 0x00) ? "AUS" : "EIN" );        BFLSH();
        snprintf( bufout, BFLN, "ALL_PARTY = %s", (ALL_PARTY == 0x00) ? "AUS\n" : "EIN" );        BFLSH();
        if (ALL_PARTY != 0x00) {
            snprintf( bufout, BFLN, "\t seit %d min, noch %d min aktiv\n",
            all_partydauer - all_party_restzeit_min, all_party_restzeit_min );
            BFLSH();
        }
    }
    else if( strncasecmp( token, "WW", 2 ) == 0 ) {

        if( z_Duschzeit == zNein )
            snprintf( bufout, BFLN, "ww_tww_sw   = %5.1f °C (keine Duschzeit)\n",  ww_tww_sw );
        else
            snprintf( bufout, BFLN, "ww_tww_sw   = %5.1f °C (Duschzeit)\n",  ww_tww_sw );
        BFLSH();
        snprintf( bufout, BFLN, "WW_Tww_MW     = %5.1f °C\n", WW_Tww_MW );
        BFLSH();
        snprintf( bufout, BFLN, "WW_HZG_Tvl_MW = %5.1f °C\n", WW_HZG_Tvl_MW );
        BFLSH();
        snprintf( bufout, BFLN, "kes_Tvl_SW_Sp1_f = %5.1f °C\t sol_SP1_To_SW_f= %5.1f °C\n", kes_Tvl_SW_Sp1_f, sol_SP1_To_SW_f );
        BFLSH();
        snprintf( bufout, BFLN, "SOL_SP1_To_MW  = %5.1f °C\n", SOL_SP1_To_MW );
        BFLSH();
        snprintf( bufout, BFLN, "WW_HZG_Tvl_MW = %5.1f °C\n", WW_HZG_Tvl_MW );
        BFLSH();
        snprintf( bufout, BFLN, "WW_HZG_Trl_MW = %5.1f °C\n", WW_HZG_Trl_MW );
        BFLSH();
        snprintf( bufout, BFLN, "WW_HZG_VV_SB = %s\n", (WW_HZG_VV_SB == 0x00) ? "ZU" : "AUF" );
        BFLSH();
        snprintf( bufout, BFLN, "WW_HZG_PU_SB = %s\n", (WW_HZG_PU_SB == 0x00) ? "AUS" : "EIN" );
        BFLSH();
        snprintf( bufout, BFLN, "WW_HZG_MV_Y  = %5d pct\n", WW_HZG_MV_Y/328 );
        BFLSH();
        snprintf( bufout, BFLN, "WW_HZG_PU_Y  = %5d pct\n", WW_HZG_PU_Y/328 );
        BFLSH();
        snprintf( bufout, BFLN, "WW_PARTY = %s", (WW_PARTY == 0x00) ? "AUS\n" : "EIN" );
        BFLSH();
        if (WW_PARTY != 0x00) {
            snprintf( bufout, BFLN, "\t seit %d min, noch %d min aktiv\n",
            all_partydauer - ww_party_restzeit_min, ww_party_restzeit_min );
            BFLSH();
        }
    }
    else if( strncasecmp( token, "HK", 2 ) == 0 ) {
        snprintf( bufout, BFLN, "HK_Tvl_MW = %5.1f °C\n", HK_Tvl_MW );
        BFLSH();
        snprintf( bufout, BFLN, "HK_Trl_MW = %5.1f °C\n", HK_Trl_MW );
        BFLSH();
        snprintf( bufout, BFLN, "HK_MV_Y   = %5d pct\n", HK_MV_Y/328 );
        BFLSH();
        snprintf( bufout, BFLN, "HK_PU_SB  = %s\n", (HK_PU_SB == 0x00) ? "AUS" : "EIN" );
        BFLSH();
    }
    else if( strncasecmp( token, "SOL", 3 ) == 0 ) {
        snprintf( bufout, BFLN, "SOL_KOLL_T_MW = %5.1f °C\n", SOL_KOLL_T_MW );        BFLSH();
        snprintf( bufout, BFLN, "SOL_SP1_To_MW = %5.1f °C\n", SOL_SP1_To_MW );        BFLSH();
        snprintf( bufout, BFLN, "SOL_SP1_Tu_MW = %5.1f °C\n", SOL_SP1_Tu_MW );        BFLSH();
        snprintf( bufout, BFLN, "SOL_SP2_To_MW = %5.1f °C\n", SOL_SP2_To_MW );        BFLSH();
        snprintf( bufout, BFLN, "SOL_SP2_Tu_MW = %5.1f °C\n", SOL_SP2_Tu_MW );        BFLSH();
        snprintf( bufout, BFLN, "SOL_PU_SB     = %s\n", (SOL_PU_SB == 0x00) ? "AUS" : "EIN" );        BFLSH();
        snprintf( bufout, BFLN, "SOL_SP1_AV_SB = %s\n", (SOL_SP1_AV_SB == 0x00) ? "ZU" : "AUF" );        BFLSH();
        snprintf( bufout, BFLN, "SOL_SP2_AV_SB = %s\n", (SOL_SP2_AV_SB == 0x00) ? "ZU" : "AUF" );        BFLSH();
    }
}
