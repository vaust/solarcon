#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/*---------------------------------------------------------
Funktion:       server_thread
                Server Threads die mit dem Client
                (Telnet, Heizungsregler oder Visualisierung)
                kommunizieren
Parameter:      Client Socket Descriptor
Rueckgabewert:  Status
----------------------------------------------------------*/
void *telnet_thread( void *arg )
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
                printf( "DEBUG: END Befehl erhalten\n" );
                next_thread--;
                close( fdesc );
                pthread_exit( NULL );
            }
            else if( strncasecmp( "GET", token, 3 ) == 0 ) {
                printf( "DEBUG: GET Befehl erhalten\n" );
                pthread_mutex_lock( &mutex );
                telnet_parseGet( fdesc, bufout );
                pthread_mutex_unlock( &mutex );
            }
            else if( strncasecmp( "PUT", token, 3 ) == 0 ) {
                printf( "DEBUG: PUT Befehl erhalten\n" );
            }
            else if( strncasecmp( "INIT", token, 4 ) == 0 ) {
                printf( "DEBUG: INIT Befehl erhalten\n" );
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

int telnet_parseGet( int fdesc, char *bufout )
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
