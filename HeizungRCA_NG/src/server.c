/*
 *  SOLARCON Modular Solar Supported Home Heating Controller
 *  Copyright (C) 2011  Volker Stegmann
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file server.c
 *  @brief Controller Task zyklisch ausführen und Telnet Task in Endlosschleife laufen lassen.
 *  Code aus Buch Linux Systemprogrammierung.
 *  @author Volker Stegmann
 */

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
#include <sys/time.h>       /* Fuer Timerintervalle */
#include <semaphore.h>

#include <string.h>
#include "param.h"
#include "cntrl.h"
#include "telnet.h"
#include "server.h"

/* Versionstring */
const char* SERVER_C_SVNVersion = "$Revision$";

/**
 * \brief Erzeugen eines Telnet Server Sockets.
 * \param port[in] Portnummer fuer Socket
 * \return Filedescriptor fuer Zugriff
 */
static
int create_server_sock( int port )
{
    int                 sock_fd;
    socklen_t           socklen;
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
    printf( "SERVER.C: zugewiesene Portnummer: %hu\n", ntohs( server.sin_port ) );

    /* Verbindungsanforderungen akzeptieren */
    if( listen( sock_fd, MAX_CON ) < 0 ) {
        perror( "Verbindungsanforderung schlug fehl" );
        // exit( -1 );
    }
    return( sock_fd );
}

/**
 * \brief Terminiere System.
 * Server gezielt auf Signal beenden
 * \param keine
 * \return kein
 */
void terminate( int sig )
{
    cntrl_close();
    
    shutdown( client_sock_fd, SHUT_RDWR );
    shutdown( server_sock_fd, SHUT_RDWR );
    close( client_sock_fd );
    close( server_sock_fd );
    printf( "SERVER.C: Server durch Signal %d beendet\n", sig );
    signal( SIGINT, SIG_DFL );
    exit( sig );
}

/**
 * @brief system Timer fuer Steuerungsprozess initialisieren.
 *
 * Dieses API funktioniert auf dem momentanen WAGO uCLinux nur bis herab zu 500ms.
 * Kleinere Timerwerte führen immer zu 500ms Zykluszeit.
 *
 * @param zykluszeit Zykluszeit in Millisekunden
 * @return kein
 */
void systimer_init( u32_t zykluszeit )
{
    struct itimerval   timer;

    timer.it_value.tv_sec     = zykluszeit / 1000L;
    timer.it_value.tv_usec    = (zykluszeit % 1000L) * 1000L;
    timer.it_interval.tv_sec  = zykluszeit / 1000L;
    timer.it_interval.tv_usec = (zykluszeit % 1000L) * 1000L;
    setitimer( ITIMER_REAL, &timer, NULL );
}

/**
 * @brief Main (internes Betriebssystem).
 * Hier wird der Intervalltimer fuer das zyklische Aufrufen der Steuerung
 * gestartet, der Mutex fuer das parallele Zugreifen auf globale Variablen erzeugt und
 * in der Endlosschleife auf eine Telnetverbindung gewartet.
 */
int main( void )
{
    next_thread = 0;

    /* Initialisierung der Regler */
    cntrl_open();
    
    signal( SIGINT, terminate );
    
    signal( SIGALRM, cntrl_run );
    systimer_init( param_sys_zykluszeit );

    server_sock_fd = create_server_sock( TCP_PORT );

    if( pthread_attr_init( &threadattr ) != 0 ) {
        perror( "SERVER.C: Thread Attribute konnten nicht erzeugt werden" );
        exit( -1 );
    }
    else if( pthread_attr_setdetachstate( &threadattr, PTHREAD_CREATE_DETACHED ) != 0 ) {
        perror( "SERVER.C: Attribut Detached konnte nicht gesetzt werden" );
        exit( -1 );
    }

    /* Ein Mutex erzeugen */
    if( pthread_mutex_init( &mutex, NULL ) != 0 ) {
        perror( "SERVER.C: Mutex konnte nicht initialisiert werden" );
        exit( -1 );
    }

    while( 1 ) {
        /* Auf Verbindung mit Client warten */
        if( (client_sock_fd = accept( server_sock_fd, NULL, NULL )) < 0 ) {
            perror( "SERVER.C: Verbindungsanforderung abgelehnt" );
        }
        else {
            thread_args[0] = client_sock_fd;
            thread_args[1] = next_thread++;
            if( (pthread_create( &thread, &threadattr, telnet_Task, (void *)thread_args ) ) != 0 ) {
                perror( "SERVER.C: Threaderzeugung telnet_Task schlug fehl" );
                close( server_sock_fd );
                exit( -1 );
            }
            else {
                printf( "SERVER.C: Neuen Telnet Thread gestartet\n");
            }
        }
    }
    return 0;
}
