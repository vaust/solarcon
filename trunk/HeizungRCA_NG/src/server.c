#define _SERVER_C_

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <sys/types.h>      /* Fuer Netzwerkfunktionalitaet */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <pthread.h>        /* Fuer Threadfunktionalitaet */
#include <semaphore.h>

#include <string.h>

#include "server.h"
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"

void *main_thread( void *arg );
int parseGet( int fdesc, char *bufout );


/*-----------------------------------------------
Funktion:       create_server_sock
                Socket zur Kommunikation erzeugen
Parameter:      int port: Portnummer fuer Socket
Rueckgabewert:  Filedescriptor fuer Zugriff
------------------------------------------------*/
int create_server_sock( int port )
{
    int                 sock_fd, socklen;
    struct sockaddr_in  server;

    /* Socket anlegen: */
    // protocol = getprotobyname( "TCP" );
    if( (sock_fd = socket( AF_INET, SOCK_STREAM, 0 )) < 0 ) {
        perror( "Socket konnte nicht geoeffnet werden" );
        exit( -1 );
    }

    /* Socket Port zuordnen: */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( port );
    socklen = sizeof( server );
    if( bind( sock_fd, (struct sockaddr *)&server, socklen ) < 0 ) {
        perror( "Socket konnte nicht verbunden werden" );
        exit( -1 );
    }

    /* Portnummer ermitteln und mitteilen: */
    if( getsockname( sock_fd, (struct sockaddr *)&server, &socklen ) < 0 ) {
        perror( "Portnummer konnte nicht ermittelt werden" );
        exit( -1 );
    }
    printf( "zugewiesene Portnummer: %hu\n", ntohs( server.sin_port ) );

    /* Verbindungsanforderungen akzeptieren */
    if( listen( sock_fd, MAX_CON ) < 0 ) {
        perror( "Verbindungsanforderung schlug fehl" );
        exit( -1 );
    }
    return( sock_fd );
}

/*---------------------------------------------------------
Funktion:       terminate
                Server gezielt auf Signal beenden
Parameter:      keine
Rueckgabewert:  keine
----------------------------------------------------------*/
void terminate( int sig )
{
    shutdown( client_sock_fd, SHUT_RDWR );
    shutdown( server_sock_fd, SHUT_RDWR );
    close( client_sock_fd );
    close( server_sock_fd );
    printf( "Server durch Signal %d beendet\n", sig );
    signal( SIGINT, SIG_DFL );
    exit( sig );
}

#define TLNT_PRINT( buf, 
/*---------------------------------------------------------
Funktion:       server_thread
                Server Threads die mit dem Client
                (Telnet, Heizungsregler oder Visualisierung)
                kommunizieren
Parameter:      Client Socket Descriptor
Rueckgabewert:  Status
----------------------------------------------------------*/
void *server_thread( void *arg )
{
    char    bufin[64], bufout[64], *token;
    int     fdesc, *arglist;

    arglist = (int *) arg;
    fdesc = arglist[0];

    snprintf( bufout, 64, "RCA Heizungssteuerung Version 0.4.9\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "Andreas und Volker Stegmann\n\n" );
    write( fdesc, bufout, strlen( bufout ) );

    snprintf( bufout, 64, "Server Prozess %d\n\n", arglist[1]+1 );
    write( fdesc, bufout, strlen( bufout ) );

    snprintf( bufout, 64, "\n Mögliche Befehle: \n\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "\t GET T (alle Temperaturmesswerte)\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "\t GET SW    (Sollwerte)\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "\t GET AO    (alle Analog-Ausgaenge)\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "\t GET DI    (alle Digital-Eingaenge)\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "\t GET DO    (alle Digital-Ausgaenge)\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "\t GET FB    (Daten zu FB-Heizung)\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "\t GET WW    (Daten zu Warmwasserbereitung)\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "\t GET SOL   (Daten zu Solarbeheizung)\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "\t GET HK    (Daten zu Heizkörper-Heizkreis)\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "\t INIT      (Initialisierungsdateien neu einlesen)\n" );
    write( fdesc, bufout, strlen( bufout ) );
    snprintf( bufout, 64, "\t END       (Datenabfrage beenden)\n" );
    write( fdesc, bufout, strlen( bufout ) );

    while( 1 ) {
        if( read( fdesc, bufin, 63 ) == 0 ) {
            next_thread--;
            close( fdesc );
            pthread_exit( NULL );
        }
        else {
            token = strtok( bufin, "\n\r " );
            if( strncasecmp( "END", token, 3 ) == 0 ) {
#ifdef __DEBUG__
                printf( "END Befehl erhalten\n" );
#endif
                next_thread--;
                close( fdesc );
                pthread_exit( NULL );
            }
            else if( strncasecmp( "GET", token, 3 ) == 0 ) {
#ifdef __DEBUG__
                printf( "GET Befehl erhalten\n" );
#endif
                pthread_mutex_lock( &mutex );
                parseGet( fdesc, bufout );
                pthread_mutex_unlock( &mutex );
            }
            else if( strncasecmp( "PUT", token, 3 ) == 0 ) {
#ifdef __DEBUG__
                printf( "PUT Befehl erhalten\n" );
#endif
            }
            else if( strncasecmp( "INIT", token, 4 ) == 0 ) {
#ifdef __DEBUG__
                printf( "INIT Befehl erhalten\n" );
#endif
                pthread_mutex_lock( &mutex );
                init_parameters();
                init_zeitprogramm();
                pthread_mutex_unlock( &mutex );

                snprintf( bufout, 64, "Parameter, Variablen und Zeitprogramm initialisiert!\n\n" );
                write( fdesc, bufout, strlen( bufout ) );
            }
        }
    }
}

int parseGet( int fdesc, char *bufout )
{
    char *token;

    token = strtok( NULL, "\n\r " );
    if( strncasecmp( token, "T", 1 ) == 0 ) {
        snprintf( bufout, 64, "ALL_Tau_MW     = %5.1f °C\n", ALL_Tau_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_KOLL_T_MW  = %5.1f °C\n", SOL_KOLL_T_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_SP1_To_MW  = %5.1f °C\n", SOL_SP1_To_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_SP1_Tu_MW  = %5.1f °C\n", SOL_SP1_Tu_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_SP2_To_MW  = %5.1f °C\n", SOL_SP2_To_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_SP2_Tu_MW  = %5.1f °C\n", SOL_SP2_Tu_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "KES_Tvl_MW     = %5.1f °C\n", KES_Tvl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "KES_Trl_MW     = %5.1f °C\n", KES_Trl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "HK_Tvl_MW      = %5.1f °C\n", HK_Tvl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "HK_Trl_MW      = %5.1f °C\n", HK_Trl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "FB_PRIM_Trl_MW = %5.1f °C\n", FB_PRIM_Trl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "FB_SEK_Tvl_MW  = %5.1f °C\n", FB_SEK_Tvl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_HZG_Tvl_MW  = %5.1f °C\n", WW_HZG_Tvl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_HZG_Trl_MW  = %5.1f °C\n", WW_HZG_Trl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_Tww_MW      = %5.1f °C\n", WW_Tww_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "Tau_1h_mittel_f  = %6.2f °C\n", Tau_1h_mittel_f );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "Tau_36h_mittel_f = %6.2f °C\n", Tau_36h_mittel_f );
        write( fdesc, bufout, strlen( bufout ) );
    }
    else if( strncasecmp( token, "SW", 2 ) == 0 ) {

        snprintf( bufout, 64, "kes_Tvl_SW_Sp2_f = %5.1f °C\t sol_SP2_To_SW_f= %5.1f °C\n", kes_Tvl_SW_Sp2_f, sol_SP2_To_SW_f );
        write( fdesc, bufout, strlen( bufout ) );

        if( z_FB_Zustand == zAbgesenkt )
            snprintf( bufout, 64, "fb_Tvl_SW_f = %5.1f °C (abgesenkt um %5.1f °C)\n", fb_Tvl_SW_f, fb_tvl_absenk );
        else
            snprintf( bufout, 64, "fb_Tvl_SW_f = %5.1f °C (Normalbetrieb)\n", fb_Tvl_SW_f );
        write( fdesc, bufout, strlen( bufout ) );

        if( z_HK_Zustand == zAbgesenkt )
            snprintf( bufout, 64, "hk_Tvl_SW_f = %5.1f °C (abgesenkt um %5.1f °C)\n", hk_Tvl_SW_f, hk_tvl_absenk );
        else
            snprintf( bufout, 64, "hk_Tvl_SW_f = %5.1f °C (Normalbetrieb)\n", hk_Tvl_SW_f);
        write( fdesc, bufout, strlen( bufout ) );

        snprintf( bufout, 64, "kes_Tvl_SW_Sp1_f = %5.1f °C\t sol_SP1_To_SW_f= %5.1f °C\n", kes_Tvl_SW_Sp1_f, sol_SP1_To_SW_f );
        write( fdesc, bufout, strlen( bufout ) );
        if( z_Duschzeit == zNein )
            snprintf( bufout, 64, "ww_tww_sw   = %5.1f °C (keine Duschzeit)\n",  ww_tww_sw );
        else
            snprintf( bufout, 64, "ww_tww_sw   = %5.1f °C (Duschzeit)\n",  ww_tww_sw );
        write( fdesc, bufout, strlen( bufout ) );
    }
    else if( strncasecmp( token, "DI", 2 ) == 0 ) {
        /* Allgemeiner Partyschalter */
        snprintf( bufout, 64, "ALL_PARTY = %s", (ALL_PARTY == 0x00) ? "AUS\n" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        if (ALL_PARTY != 0x00) {
            snprintf( bufout, 64, "\t seit %d min, noch %d min aktiv\n",
            all_partydauer - all_party_restzeit_min, all_party_restzeit_min );
            write( fdesc, bufout, strlen( bufout ) );
        }
        /* Warmwasser Partyschalter */
        snprintf( bufout, 64, "WW_PARTY = %s", (WW_PARTY == 0x00) ? "AUS\n" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        if (WW_PARTY != 0x00) {
            snprintf( bufout, 64, "\t seit %d min, noch %d min aktiv\n",
            all_partydauer - ww_party_restzeit_min, ww_party_restzeit_min );
            write( fdesc, bufout, strlen( bufout ) );
        }
        /* Kesselstörmeldung */
        snprintf( bufout, 64, "KES_SSM = %s\n", (KES_SSM == 0x00) ? "NORMAL (0)" : "STÖRUNG (1)" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Kessel Brennerbetriebsmeldung */
        snprintf( bufout, 64, "KES_BR_BM = %s\n", (KES_BR_BM == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Fußbodenheizung Sekundärseite Sicherheitstemperaturbegrenzer */
        snprintf( bufout, 64, "FB_SEK_TW = %s\n", (FB_SEK_TW == 0x00) ?  "STÖRUNG (0)" : "NORMAL (1)" );
        write( fdesc, bufout, strlen( bufout ) );
    }
    else if( strncasecmp( token, "DO", 2 ) == 0 ) {
        /* Solarkreispumpe */
        snprintf( bufout, 64, "SOL_PU_SB = %s\n", (SOL_PU_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Solarabsperrventil Speicher 1 */
        snprintf( bufout, 64, "SOL_SP1_AV_SB = %s\n", (SOL_SP1_AV_SB == 0x00) ? "ZU" : "AUF" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Solarabsperrventil Speicher 2 */
        snprintf( bufout, 64, "SOL_SP2_AV_SB = %s\n", (SOL_SP2_AV_SB == 0x00) ? "ZU" : "AUF" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Kessel Ladepumpe Speicher 1 */
        snprintf( bufout, 64, "KES_PU_SP1_SB = %s\n", (KES_PU_SP1_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Kessel Ladepumpe Speicher 2 */
        snprintf( bufout, 64, "KES_PU_SP2_SB = %s\n", (KES_PU_SP2_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Heizkoeerperheizkreispumpe */
        snprintf( bufout, 64, "HK_PU_SB = %s\n", (HK_PU_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Fußbodenheizung Wärmetauscher Primärkreispumpe */
        snprintf( bufout, 64, "FB_PRIM_PU_SB = %s\n", (FB_PRIM_PU_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Fußbodenheizung Wärmetauscher Sekundärkreispumpe */
        snprintf( bufout, 64, "FB_SEK_PU_SB = %s\n", (FB_SEK_PU_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Warmwasser / Heizung Verteilventil für Energiemanagement */
        snprintf( bufout, 64, "WW_HZG_VV_SB = %s\n", (WW_HZG_VV_SB == 0x00) ? "ZU" : "AUF" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Warmwasserheizungspumpe */
        snprintf( bufout, 64, "WW_HZG_PU_SB = %s\n", (WW_HZG_PU_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        /* Zirkulationspumpe */
        snprintf( bufout, 64, "WW_ZIRK_PU_SB = %s\n", (WW_ZIRK_PU_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
    }
    else if( strncasecmp( token, "AO", 2 ) == 0 ) {
        snprintf( bufout, 64, "KES_Tvl_Y    = %5d pct\n", KES_Tvl_Y/328 );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "HK_MV_Y      = %5d pct\n", HK_MV_Y/328 );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "FB_PRIM_MV_Y = %5d pct\n", FB_PRIM_MV_Y/328 );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_HZG_MV_Y  = %5d pct\n", WW_HZG_MV_Y/328 );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_HZG_PU_Y  = %5d pct\n", WW_HZG_PU_Y/328 );
        write( fdesc, bufout, strlen( bufout ) );
    }
    else if( strncasecmp( token, "FB", 2 ) == 0 ) {
        snprintf( bufout, 64, "FB_PRIM_Trl_MW = %5.1f °C\n", FB_PRIM_Trl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "FB_SEK_Tvl_MW  = %5.1f °C\n", FB_SEK_Tvl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "FB_PRIM_MV_Y   = %5d pct\n", FB_PRIM_MV_Y/328 );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "FB_PRIM_PU_SB  = %s\n", (FB_PRIM_PU_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "FB_SEK_PU_SB   = %s\n", (FB_SEK_PU_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "ALL_PARTY = %s", (ALL_PARTY == 0x00) ? "AUS\n" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        if (ALL_PARTY != 0x00) {
            snprintf( bufout, 64, "\t seit %d min, noch %d min aktiv\n",
            all_partydauer - all_party_restzeit_min, all_party_restzeit_min );
            write( fdesc, bufout, strlen( bufout ) );
        }
    }
    else if( strncasecmp( token, "WW", 2 ) == 0 ) {

        if( z_Duschzeit == zNein )
            snprintf( bufout, 64, "ww_tww_sw   = %5.1f °C (keine Duschzeit)\n",  ww_tww_sw );
        else
            snprintf( bufout, 64, "ww_tww_sw   = %5.1f °C (Duschzeit)\n",  ww_tww_sw );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_Tww_MW     = %5.1f °C\n", WW_Tww_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_HZG_Tvl_MW = %5.1f °C\n", WW_HZG_Tvl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "kes_Tvl_SW_Sp1_f = %5.1f °C\t sol_SP1_To_SW_f= %5.1f °C\n", kes_Tvl_SW_Sp1_f, sol_SP1_To_SW_f );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_SP1_To_MW  = %5.1f °C\n", SOL_SP1_To_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_HZG_Tvl_MW = %5.1f °C\n", WW_HZG_Tvl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_HZG_Trl_MW = %5.1f °C\n", WW_HZG_Trl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_HZG_VV_SB = %s\n", (WW_HZG_VV_SB == 0x00) ? "ZU" : "AUF" );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_HZG_PU_SB = %s\n", (WW_HZG_PU_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_HZG_MV_Y  = %5d pct\n", WW_HZG_MV_Y/328 );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_HZG_PU_Y  = %5d pct\n", WW_HZG_PU_Y/328 );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "WW_PARTY = %s", (WW_PARTY == 0x00) ? "AUS\n" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        if (WW_PARTY != 0x00) {
            snprintf( bufout, 64, "\t seit %d min, noch %d min aktiv\n",
            all_partydauer - ww_party_restzeit_min, ww_party_restzeit_min );
            write( fdesc, bufout, strlen( bufout ) );
        }
    }
    else if( strncasecmp( token, "HK", 2 ) == 0 ) {
        snprintf( bufout, 64, "HK_Tvl_MW = %5.1f °C\n", HK_Tvl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "HK_Trl_MW = %5.1f °C\n", HK_Trl_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "HK_MV_Y   = %5d pct\n", HK_MV_Y/328 );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "HK_PU_SB  = %s\n", (HK_PU_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
    }
    else if( strncasecmp( token, "SOL", 3 ) == 0 ) {
        snprintf( bufout, 64, "SOL_KOLL_T_MW = %5.1f °C\n", SOL_KOLL_T_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_SP1_To_MW = %5.1f °C\n", SOL_SP1_To_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_SP1_Tu_MW = %5.1f °C\n", SOL_SP1_Tu_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_SP2_To_MW = %5.1f °C\n", SOL_SP2_To_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_SP2_Tu_MW = %5.1f °C\n", SOL_SP2_Tu_MW );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_PU_SB     = %s\n", (SOL_PU_SB == 0x00) ? "AUS" : "EIN" );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_SP1_AV_SB = %s\n", (SOL_SP1_AV_SB == 0x00) ? "ZU" : "AUF" );
        write( fdesc, bufout, strlen( bufout ) );
        snprintf( bufout, 64, "SOL_SP2_AV_SB = %s\n", (SOL_SP2_AV_SB == 0x00) ? "ZU" : "AUF" );
        write( fdesc, bufout, strlen( bufout ) );
    }
}

int main( void )
{
    void    *thread_result;

    signal( SIGINT, terminate );
    server_sock_fd = create_server_sock( TCP_PORT );

    if( pthread_attr_init( &threadattr ) != 0 ) {
        perror( "Thread Attribute konnten nicht erzeugt werden" );
        exit( -1 );
    }
    else if( pthread_attr_setdetachstate( &threadattr, PTHREAD_CREATE_DETACHED ) != 0 ) {
        perror( "Attribut Detached konnte nicht gesetzt werden" );
        exit( -1 );
    }

/* Ein Mutex erzeugen */
    if( pthread_mutex_init( &mutex, NULL ) != 0 ) {
        perror( "Mutex konnte nicht initialisiert werden" );
        exit( -1 );
    }

    /* Main Thread erzeugen */
    if( (pthread_create( &(threadlist[next_thread]), &threadattr,
                         main_thread, (void *)thread_args ) ) != 0 ) {
        perror( "Threaderzeugung schlug fehl" );
        exit( -1 );
    }

    while( 1 ) {
        /* Auf Verbindung mit Client warten */
        if( (client_sock_fd = accept( server_sock_fd, NULL, NULL )) < 0 ) {
            perror( "Verbindungsanforderung abgelehnt" );
        }
        thread_args[0] = client_sock_fd;
        thread_args[1] = next_thread++;
        if( (pthread_create( &(threadlist[next_thread]), &threadattr,
                             server_thread, (void *)thread_args ) ) != 0 ) {
            perror( "Threaderzeugung schlug fehl" );
            close( server_sock_fd );
            exit( -1 );
        }
    }
    shutdown( client_sock_fd, SHUT_RDWR );
    shutdown( server_sock_fd, SHUT_RDWR );
    close( client_sock_fd );
    close( server_sock_fd );
}
