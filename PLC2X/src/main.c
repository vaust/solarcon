/**
 * @file server.c
 *  @brief Controller Task zyklisch ausfÃ¼hren und Telnet Task in Endlosschleife laufen lassen.
 *  Code aus Buch Linux Systemprogrammierung.
 *  @author Volker Stegmann
 */

#define _MAIN_C_

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
#include "test.h"
#include "main.h"

/**
 * \brief Terminiere System.
 * Server gezielt auf Signal beenden
 * \param keine
 * \return kein
 */
void terminate( int sig )
{
    test_close();
    
    printf( "MAIN.C: durch Signal %d beendet\n", sig );
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
    struct itimerval timer;

    timer.it_value.tv_sec     = zykluszeit / 1000L;
    timer.it_value.tv_usec    = (zykluszeit % 1000L) * 1000L;
    timer.it_interval.tv_sec  = zykluszeit / 1000L;
    timer.it_interval.tv_usec = (zykluszeit % 1000L) * 1000L;
    setitimer( ITIMER_REAL, &timer, NULL );
}

int main( void )
{
    /* Initialisierung der Regler */
    test_init();
    test_open();
    
    signal( SIGINT, terminate );
    
    signal( SIGALRM, test_run );
    systimer_init( 1000 );
    // sigalarm( 1, test_run );

    printf( "MAIN.C: Endlosschleife wird gestartet\n");
    for(;;) {
    }
    return 0;
}
