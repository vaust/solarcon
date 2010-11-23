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
#include "param.h"      /* Parametrisierung aus INI-Dateien */
#include "io.h"         /* Ein- und Ausgabe auf der PLC     */
#include "cntrl.h"      /* Systemzustandsvariablen          */
#include "zeit.h"
#include "task.h"
#include "version.h"    /* Versionsstring */
#include "server.h"
#include "telnet.h"

#define BFLN        96
#define BFLSH()     write( fdesc, bufout, strlen( bufout ) )

#include "telnet_vars.h"

/**
  * \brief server_thread.
  * Server Threads die mit dem Client (Telnet, Heizungsregler oder Visualisierung)
  * kommunizieren
  * \param Client Socket Descriptor
  * \return Status
  */
void *telnet_thread( void *arg )
{
    char    bufin[BFLN], bufout[BFLN], *token;
    int     fdesc, *arglist;

    arglist = (int *) arg;
    fdesc = arglist[0];

    snprintf( bufout, BFLN, "\tRCA Heizungssteuerung Version " );                                         BFLSH();
    snprintf( bufout, BFLN, VERSIONSTRING );                                                              BFLSH();
    snprintf( bufout, BFLN, "\tAndreas Stegmann\n\tVolker Stegmann\n\n" );                                BFLSH();
    snprintf( bufout, BFLN, "\tERR-Modul nicht aktiv. Bitte bei Bedarf mit \"AUTO ERR\" einschalten\n" ); BFLSH();
    snprintf( bufout, BFLN, "\tServer Prozess %d\n\n", arglist[1]+1 );                                    BFLSH();
    telnet_writeHelp( fdesc, bufout );

    while( 1 ) {
        if( read( fdesc, bufin, BFLN-1 ) == 0 ) {
            next_thread--;
            close( fdesc );
            pthread_exit( NULL );
        }
        else {
            MUTEX_LOCK();
            token = strtok( bufin, "\n\r " );
            if( NULL != token ) {
                if     ( strncasecmp( "END",     token, 3 ) == 0 ) {
                    printf( "TELNET.C: END Befehl erhalten\n" );
                    next_thread--;
                    close( fdesc );
                    MUTEX_UNLOCK();
                    pthread_exit( NULL );
                }
                else if( strncasecmp( "HELP",    token, 3 ) == 0 ) {
                    printf( "TELNET.C: HELP Befehl erhalten\n" );
                    telnet_writeHelp( fdesc, bufout );
                }
                else if( strncasecmp( "VERSION", token, 4 ) == 0 ) {
                    printf( "TELNET.C: VERSION Befehl erhalten\n" );
                    snprintf( bufout, BFLN, "\tRCA Heizungssteuerung\n\tVersion " ); BFLSH();
                    snprintf( bufout, BFLN, VERSIONSTRING ); BFLSH();
                    snprintf( bufout, BFLN, "\tEntwicklungszweig: " ); BFLSH();
                    snprintf( bufout, BFLN, VERSIONDEVPATH ); BFLSH();                    
                    snprintf( bufout, BFLN, "\tAndreas Stegmann\n\tVolker Stegmann\n" ); BFLSH();
                }
                else if( strncasecmp( "GET",     token, 3 ) == 0 ) {
                    printf( "TELNET.C: GET Befehl erhalten\n" );
                    telnet_parseGet( fdesc, bufout );
                }
                else if( strncasecmp( "MODULE",  token, 3 ) == 0 ) {
                    printf( "TELNET.C: MODULE Befehl erhalten\n" );
                    telnet_writeModuls( fdesc, bufout );
                }
                else if( strncasecmp( "HAND",    token, 4 ) == 0 ) {
                    printf( "TELNET.C: HAND Befehl erhalten\n" );
                    token = strtok( NULL, "\n\r " );
                    if( NULL != token ) {
                        if     ( strncasecmp( token, "SOL", 3 ) == 0 ) {
                            cntrl_mdl_aktiv.sol_aktiv = RESET;
                            snprintf( bufout, BFLN, "\tSOL-Modul auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "FB", 2 ) == 0 ) {
                            cntrl_mdl_aktiv.fb_aktiv  = RESET;
                            snprintf( bufout, BFLN, "\tFB-Modul auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "HK", 2 ) == 0 ) {
                            cntrl_mdl_aktiv.hk_aktiv  = RESET;
                            snprintf( bufout, BFLN, "\tHK-Modul auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "WW", 2 ) == 0 ) {
                            cntrl_mdl_aktiv.ww_aktiv  = RESET;
                            snprintf( bufout, BFLN, "\tWW-Modul auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "KES", 3 ) == 0 ) {
                            cntrl_mdl_aktiv.kes_aktiv = RESET;
                            snprintf( bufout, BFLN, "\tKES-Modul auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "ERR", 3 ) == 0 ) {
                            cntrl_mdl_aktiv.err_aktiv = RESET;
                            snprintf( bufout, BFLN, "\tERR-Modul auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                        /* Eingabe sperren */
                        else if( strncasecmp( token, "INSOL", 5 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_sol_aktiv = RESET;
                            snprintf( bufout, BFLN, "\tSOL-Eingabe auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "INFB", 4 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_fb_aktiv = RESET;
                            snprintf( bufout, BFLN, "\tFB-Eingabe auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "INHK", 4 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_hk_aktiv = RESET;
                            snprintf( bufout, BFLN, "\tHK-Eingabe auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "INWW", 4 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_ww_aktiv = RESET;
                            snprintf( bufout, BFLN, "\tWW-Eingabe auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "INKES", 5 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_kes_aktiv = RESET;
                            snprintf( bufout, BFLN, "\tKES-Eingabe auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "INERR", 5 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_err_aktiv = RESET;
                            snprintf( bufout, BFLN, "\tERR-Eingabe auf HAND Betrieb (Open Loop)\n" ); BFLSH();
                        }
                    }
                }
                else if( strncasecmp( "AUTO",    token, 4 ) == 0 ) {
                    printf( "TELNET.C: AUTO Befehl erhalten\n" );
                    token = strtok( NULL, "\n\r " );
                    if( NULL != token ) {
                        if     ( strncasecmp( token, "SOL", 3 ) == 0 ) {
                            cntrl_mdl_aktiv.sol_aktiv = SET;
                            snprintf( bufout, BFLN, "\tSOL-Modul auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "FB", 2 ) == 0 ) {
                            cntrl_mdl_aktiv.fb_aktiv  = SET;
                            snprintf( bufout, BFLN, "\tFB Modul auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "HK", 2 ) == 0 ) {
                            cntrl_mdl_aktiv.hk_aktiv  = SET;
                            snprintf( bufout, BFLN, "\tHK Modul auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "WW", 2 ) == 0 ) {
                            cntrl_mdl_aktiv.ww_aktiv  = SET;
                            snprintf( bufout, BFLN, "\tWW Modul auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "KES", 3 ) == 0 ) {
                            cntrl_mdl_aktiv.kes_aktiv = SET;
                            snprintf( bufout, BFLN, "\tKES Modul auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "ERR", 3 ) == 0 ) {
                            cntrl_mdl_aktiv.err_aktiv = SET;
                            snprintf( bufout, BFLN, "\tERR Modul auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        /* Eingabe auf Autmatik */
                        if     ( strncasecmp( token, "INSOL", 5 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_sol_aktiv = SET;
                            snprintf( bufout, BFLN, "\tSOL-Eingabe auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "INFB", 4 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_fb_aktiv  = SET;
                            snprintf( bufout, BFLN, "\tFB-Eingabe auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "INHK", 4 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_hk_aktiv  = SET;
                            snprintf( bufout, BFLN, "\tHK-Eingabe auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "INWW", 4 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_ww_aktiv  = SET;
                            snprintf( bufout, BFLN, "\tWW-Eingabe auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "INKES", 5 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_kes_aktiv = SET;
                            snprintf( bufout, BFLN, "\tKES-Eingabe auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "INERR", 3 ) == 0 ) {
                            cntrl_mdl_aktiv.inp_err_aktiv = SET;
                            snprintf( bufout, BFLN, "\tERR-Eingabe auf AUTOMATIK Betrieb (Closed Loop)\n" ); BFLSH();
                        }
                        else if( strncasecmp( token, "ALL", 3 ) == 0 ) {
                            cntrl_mdl_aktiv.sol_aktiv     = SET;
                            cntrl_mdl_aktiv.fb_aktiv      = SET;
                            cntrl_mdl_aktiv.hk_aktiv      = SET;
                            cntrl_mdl_aktiv.ww_aktiv      = SET;
                            cntrl_mdl_aktiv.kes_aktiv     = SET;
                            cntrl_mdl_aktiv.err_aktiv     = SET;
                            cntrl_mdl_aktiv.inp_sol_aktiv = SET;
                            cntrl_mdl_aktiv.inp_fb_aktiv  = SET;
                            cntrl_mdl_aktiv.inp_hk_aktiv  = SET;
                            cntrl_mdl_aktiv.inp_ww_aktiv  = SET;
                            cntrl_mdl_aktiv.inp_kes_aktiv = SET;
                            snprintf( bufout, BFLN, "\tAlle Module und Eingaben auf AUTOMATIK Betrieb!\n" ); BFLSH();
                        }
                    }
                }
                else if( strncasecmp( "PUT",     token, 3 ) == 0 ) {
                    token = strtok( NULL, "0123456789 " );
                    if( NULL != token ) {
                        if( strncasecmp( token, "VSOL", 4 ) == 0 ) {
                            telnet_putVars( telnet_sol_Vars, sizeof(telnet_sol_Vars)/sizeof(parse_set_t), fdesc, bufout );
                            printf( "TELNET.C: PUT VSOL Befehl erhalten\n" );
                        }
                        else if( strncasecmp( token, "VFB", 3 ) == 0 ) {
                            telnet_putVars( telnet_fb_Vars, sizeof(telnet_fb_Vars)/sizeof(parse_set_t), fdesc, bufout );
                            printf( "TELNET.C: PUT VFB Befehl erhalten\n" );
                        }
                        else if( strncasecmp( token, "VHK", 3 ) == 0 ) {
                            telnet_putVars( telnet_hk_Vars, sizeof(telnet_hk_Vars)/sizeof(parse_set_t), fdesc, bufout );
                            printf( "TELNET.C: PUT VHK Befehl erhalten\n" );
                        }
                        else if( strncasecmp( token, "VWW", 3 ) == 0 ) {
                            telnet_putVars( telnet_ww_Vars, sizeof(telnet_ww_Vars)/sizeof(parse_set_t), fdesc, bufout );
                            printf( "TELNET.C: PUT VWW Befehl erhalten\n" );
                        }
                        else if( strncasecmp( token, "VKES", 4 ) == 0 ) {
                            telnet_putVars( telnet_kes_Vars, sizeof(telnet_kes_Vars)/sizeof(parse_set_t), fdesc, bufout );
                            printf( "TELNET.C: PUT VKES Befehl erhalten\n" );
                        }
                        else if( strncasecmp( token, "VERR", 4 ) == 0 ) {
                            telnet_putVars( telnet_err_Vars, sizeof(telnet_err_Vars)/sizeof(parse_set_t), fdesc, bufout );
                            printf( "TELNET.C: PUT VERR Befehl erhalten\n" );
                        }
                        else if( strncasecmp( token, "VDBG", 4 ) == 0 ) {
                            telnet_putVars( telnet_err_Vars, sizeof(telnet_dbg_Vars)/sizeof(parse_set_t), fdesc, bufout );
                            printf( "TELNET.C: PUT VDBG Befehl erhalten\n" );
                        }
                    }
                }
                else if( strncasecmp( "INIT",    token, 4 ) == 0 ) {
                    printf( "TELNET.C: INIT Befehl erhalten\n" );
                    param_Init();
                    zeit_Init( &cntrl_zeit_absenkung, &cntrl_zeit_event );
                    task_Init( &cntrl_tau, io_get_ALL_Tau_MW() );
                    sol_Init( &cntrl_sol_par );
                    fb_Init( &cntrl_fb_par, &cntrl_fb_q, &cntrl_fb_out );
                    hk_Init( &cntrl_hk_par, &cntrl_hk_q, &cntrl_hk_out );
                    ww_Init( &cntrl_ww_par, &cntrl_ww_q, &cntrl_ww_out );
                    kes_Init( &cntrl_kes_par, &cntrl_kes_out );
                    snprintf( bufout, BFLN, "\tParameter und Zeitprogramm initialisiert!\n\n" ); BFLSH();
                }
            }
            MUTEX_UNLOCK();
        }
    }
}

static inline
void telnet_write_Auto_Hand( u8_t flag, int fdesc, char *bufout )
{
    if( flag == SET ) {
        snprintf( bufout, BFLN, "AUTO Betrieb (Closed Loop)\n" ); BFLSH();
    }
    else {
        snprintf( bufout, BFLN, "HAND Betrieb (Open Loop)\n" ); BFLSH();
    }
}

static
void telnet_writeModuls( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "\tSOL-Modul   auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.sol_aktiv, fdesc, bufout );
    snprintf( bufout, BFLN, "\tSOL-Eingabe auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.inp_sol_aktiv, fdesc, bufout );

    snprintf( bufout, BFLN, "\tFB-Modul    auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.fb_aktiv, fdesc, bufout );
    snprintf( bufout, BFLN, "\tFB-Eingabe  auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.inp_fb_aktiv, fdesc, bufout );

    snprintf( bufout, BFLN, "\tHK-Modul    auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.hk_aktiv, fdesc, bufout );
    snprintf( bufout, BFLN, "\tHK-Eingabe  auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.inp_hk_aktiv, fdesc, bufout );

    snprintf( bufout, BFLN, "\tWW-Modul    auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.ww_aktiv, fdesc, bufout );
    snprintf( bufout, BFLN, "\tWW-Eingabe  auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.inp_ww_aktiv, fdesc, bufout );

    snprintf( bufout, BFLN, "\tKES-Modul   auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.kes_aktiv, fdesc, bufout );
    snprintf( bufout, BFLN, "\tKES-Eingabe auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.inp_kes_aktiv, fdesc, bufout );

    snprintf( bufout, BFLN, "\tERR-Modul   auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.err_aktiv, fdesc, bufout );
    snprintf( bufout, BFLN, "\tERR-Eingabe auf " ); BFLSH();
    telnet_write_Auto_Hand( cntrl_mdl_aktiv.inp_err_aktiv, fdesc, bufout );
}

static
void telnet_writeHelp( int fdesc, char *bufout )
{
    int n;
    for( n=0; n<sizeof(telnet_help_text)/sizeof(char*); n++ ) {
        snprintf( bufout, BFLN, telnet_help_text[n] ); BFLSH();
    }
 }

static
void telnet_parseGet( int fdesc, char *bufout )
{
    char *token;

    token = strtok( NULL, "\n\r " );
    if( NULL != token ) {
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
        else if( strncasecmp( token, "VKES", 4 ) == 0 ) {
            telnet_writeVars( telnet_kes_Vars, sizeof(telnet_kes_Vars)/sizeof(parse_set_t), fdesc, bufout );
        }
        else if( strncasecmp( token, "VERR", 4 ) == 0 ) {
            telnet_writeVars( telnet_err_Vars, sizeof(telnet_err_Vars)/sizeof(parse_set_t), fdesc, bufout );
        }
        else if( strncasecmp( token, "VDBG", 4 ) == 0 ) {
            telnet_writeVars( telnet_dbg_Vars, sizeof(telnet_dbg_Vars)/sizeof(parse_set_t), fdesc, bufout );
        }
    }   
}

static
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

static
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

static
void telnet_writeSchaltzeiten( int fdesc, char *bufout )
{
    s16_t n;
    s16_t d_ein, h_ein, m_ein;
    s16_t d_aus, h_aus, m_aus;

    for( n=0; n<hk_states; n++ ) {
        telnet_minToTime( HK_Ein_Schaltzeiten[n], &d_ein, &h_ein, &m_ein );
        telnet_minToTime( HK_Aus_Schaltzeiten[n], &d_aus, &h_aus, &m_aus );
        snprintf( bufout, BFLN, "HK_Ein[%d]    = %1d-%02d:%02d, HK_Aus[%d]    = %1d-%02d:%02d\n",
                n, d_ein, h_ein, m_ein, n, d_aus, h_aus, m_aus );
        BFLSH();
    }
    for( n=0; n<fb_states; n++ ) {
        telnet_minToTime( FB_Ein_Schaltzeiten[n], &d_ein, &h_ein, &m_ein );
        telnet_minToTime( FB_Aus_Schaltzeiten[n], &d_aus, &h_aus, &m_aus );
        snprintf( bufout, BFLN, "FB_Ein[%d]    = %1d-%02d:%02d, FB_Aus[%d]    = %1d-%02d:%02d\n",
                n, d_ein, h_ein, m_ein, n, d_aus, h_aus, m_aus );
        BFLSH();
    }
    for( n=0; n<zirk_states; n++ ) {
        telnet_minToTime( ZIRK_Ein_Schaltzeiten[n], &d_ein, &h_ein, &m_ein );
        telnet_minToTime( ZIRK_Aus_Schaltzeiten[n], &d_aus, &h_aus, &m_aus );
        snprintf( bufout, BFLN, "ZIRK_Ein[%d]  = %1d-%02d:%02d, ZIRK_Aus[%d]  = %1d-%02d:%02d\n",
                n, d_ein, h_ein, m_ein, n, d_aus, h_aus, m_aus );
        BFLSH();
    }
    for( n=0; n<dusch_states; n++ ) {
        telnet_minToTime( DUSCH_Ein_Schaltzeiten[n], &d_ein, &h_ein, &m_ein );
        telnet_minToTime( DUSCH_Aus_Schaltzeiten[n], &d_aus, &h_aus, &m_aus );
        snprintf( bufout, BFLN, "DUSCH_Ein[%d] = %1d-%02d:%02d, DUSCH_Aus[%d] = %1d-%02d:%02d\n",
                n, d_ein, h_ein, m_ein, n, d_aus, h_aus, m_aus );
        BFLSH();
    }
    snprintf( bufout, BFLN,"HOUR_OFFSET = %d\n\n", zeit_hour_offset );
    BFLSH();
}

static
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

static
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

static
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

static
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

static
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

static
void telnet_writeAO( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "KES_Tvl_Y    = %5.1f pct\n", io_get_KES_Tvl_Y() );        BFLSH();
    snprintf( bufout, BFLN, "HK_MV_Y      = %5.1f pct\n", io_get_HK_MV_Y() );          BFLSH();
    snprintf( bufout, BFLN, "FB_PRIM_MV_Y = %5.1f pct\n", io_get_FB_PRIM_MV_Y() );     BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_MV_Y  = %5.1f pct\n", io_get_WW_HZG_MV_Y() );      BFLSH();
    snprintf( bufout, BFLN, "WW_HZG_PU_Y  = %5.1f pct\n", io_get_WW_HZG_PU_Y() );      BFLSH();
}

static
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

static
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

static
void telnet_writeHK( int fdesc, char *bufout )
{
    snprintf( bufout, BFLN, "HK_Tvl_MW = %5.1f °C\n", io_get_HK_Tvl_MW() );                      BFLSH();
    snprintf( bufout, BFLN, "HK_Trl_MW = %5.1f °C\n", io_get_HK_Trl_MW() );                      BFLSH();
    snprintf( bufout, BFLN, "HK_MV_Y   = %5.1f pct\n", io_get_HK_MV_Y() );                       BFLSH();
    snprintf( bufout, BFLN, "HK_PU_SB  = %s\n", (io_get_HK_PU_SB() == IO_AUS) ? "AUS" : "EIN" ); BFLSH();
}

static
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

static
void telnet_writeVars( const parse_set_t Vars[], int len, int fdesc, char *bufout )
{
    int     n;
    char    *token;

    token = strtok( NULL, "\n\r " );
    if( NULL != token ) {
        n = atoi( token );
        if( (n >= 0) && (n < len) ) {
            snprintf( bufout, BFLN, Vars[n].VarName ); BFLSH();
            snprintf( bufout, BFLN, " = " ); BFLSH();
            switch ( Vars[n].format[1] ) {
                case 'd':
                    snprintf( bufout, BFLN, Vars[n].format, *(s16_t *)Vars[n].VarPointer ); BFLSH();
                    break;
                case 'x':
                    snprintf( bufout, BFLN, Vars[n].format, *(u8_t *)Vars[n].VarPointer ); BFLSH();
                    break;
                case 'f':
                default:
                    snprintf( bufout, BFLN, "%8.3f", *(float *)Vars[n].VarPointer ); BFLSH();
                    break;
            }
            snprintf( bufout, BFLN, "\n" ); BFLSH();
        }
        else if( n < 0 ) {
            for( n=0; n<len; n++ ) {
                snprintf( bufout, BFLN, "(%02d) ", n ); BFLSH();
                snprintf( bufout, BFLN, Vars[n].VarName ); BFLSH();
                snprintf( bufout, BFLN, " = " ); BFLSH();
                switch ( Vars[n].format[1] ) {
                    case 'd':
                        snprintf( bufout, BFLN, Vars[n].format, *(s16_t *)Vars[n].VarPointer ); BFLSH();
                        break;
                    case 'x':
                        snprintf( bufout, BFLN, Vars[n].format, *(u8_t *)Vars[n].VarPointer ); BFLSH();
                        break;
                    case 'f':
                    default:
                        snprintf( bufout, BFLN, "%8.3f", *(float *)Vars[n].VarPointer ); BFLSH();
                        break;
                }
                snprintf( bufout, BFLN, "\n" ); BFLSH();
            }
        }
        else {
            snprintf( bufout, BFLN, "FEHLER: n nicht plausibel\n" ); BFLSH();        
        }
    }
}

static
void telnet_putVars( const parse_set_t Vars[], int len, int fdesc, char *bufout )
{
    char    *token;
    int     var_no;
    int     value_i;
    float   value_f;

    token = strtok( NULL, "= " );
    if( NULL != token ) {
        var_no = atoi( token );
        // printf( "TELNET.C PUT (%d) = \n", var_no);
        if( var_no < len ) {
            token = strtok( NULL, "\n\r" );
            if( NULL != token ) {
                switch ( Vars[var_no].format[1] ) {
                    case 'd':
                        value_i = atoi( token );
                        *(s16_t *)Vars[var_no].VarPointer = value_i;
                        snprintf( bufout, BFLN, Vars[var_no].VarName ); BFLSH();
                        snprintf( bufout, BFLN, " = " ); BFLSH();
                        snprintf( bufout, BFLN, Vars[var_no].format, *(s16_t *)Vars[var_no].VarPointer ); BFLSH();
                        snprintf( bufout, BFLN, "\n" );  BFLSH();
                        break;
                    case 'f':
                        value_f = atof( token );
                        *(float *)Vars[var_no].VarPointer = value_f;
                        snprintf( bufout, BFLN, Vars[var_no].VarName ); BFLSH();
                        snprintf( bufout, BFLN, " = " ); BFLSH();
                        snprintf( bufout, BFLN, "%8.3f", *(float *)Vars[var_no].VarPointer ); BFLSH();
                        snprintf( bufout, BFLN, "\n" );  BFLSH();
                        break;
                    case 'x':
                    default :
                        value_i = atoi( token );
                        *(u8_t *)Vars[var_no].VarPointer = (u8_t) value_i;
                        snprintf( bufout, BFLN, Vars[var_no].VarName ); BFLSH();
                        snprintf( bufout, BFLN, " = " ); BFLSH();
                        snprintf( bufout, BFLN, Vars[var_no].format, *(u8_t *)Vars[var_no].VarPointer ); BFLSH();
                        snprintf( bufout, BFLN, "\n" );  BFLSH();
                        break;
                }
            }
        }
        else {
            snprintf( bufout, BFLN, "FEHLER bei der Befehlsauswertung!\n" ); BFLSH();
        }
    }
}


