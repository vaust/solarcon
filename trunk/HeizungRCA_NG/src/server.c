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
#include "server.h"

/*-----------------------------------------------
Funktion:       create_server_sock
                Socket zur Kommunikation erzeugen
Parameter:      int port: Portnummer fuer Socket
Rueckgabewert:  Filedescriptor fuer Zugriff
------------------------------------------------*/
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
    cntrl_close();
    
    shutdown( client_sock_fd, SHUT_RDWR );
    shutdown( server_sock_fd, SHUT_RDWR );
    close( client_sock_fd );
    close( server_sock_fd );
    printf( "SERVER.C: Server durch Signal %d beendet\n", sig );
    signal( SIGINT, SIG_DFL );
    exit( sig );
}

int main( void )
{
    cntrl_open();
    
    signal( SIGINT, terminate );
    signal( SIGALRM, cntrl_main );
    
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 500000L;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 500000L;
    setitimer( ITIMER_REAL, &timer, NULL );

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
        thread_args[0] = client_sock_fd;
        thread_args[1] = next_thread++;
        if( (pthread_create( &(threadlist[next_thread]), &threadattr,
                             telnet_thread, (void *)thread_args ) ) != 0 ) {
            perror( "SERVER.C: Threaderzeugung schlug fehl" );
            close( server_sock_fd );
            exit( -1 );
        }
    }
}
