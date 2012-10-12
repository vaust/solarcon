#define _TEST_C_

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "gen_types.h"
#include "io_ll.h"
#include "io_hl.h"
#include "test.h"
#include "block.h"


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
 * @brief Interfacefunktionen
 */

std_ret_t test_block_read_u( block_in_t *u )
{
    di_bitbyte_t a, b, c;

    (void) io_ll_read_DigitalIn1( &a ); // a = DigitalIn1
    (void) io_ll_read_DigitalIn2( &b ); // b = DigitalIn2
    (void) io_ll_read_DigitalIn3( &c ); // c = DigitalIn3

    u->a = 4*((int)a) + 2*((int)b) + ((int)c);
    u->b = 0;
    u->c = 0;

    return E_OK;
}

std_ret_t test_block_write_y( block_out_t *y )
{
    di_bitbyte_t d, e, f;

    // todo
}

/**
 * @brief Steuerung initialisieren.
 */

void test_init( void )
{
    block_Init( &Block1, test_block_read_u, test_block_write_y ); // Beschreibt eine Netzliste
}

void test_open( void )
{
    std_ret_t ret;

    KBUSOPEN();
    KBUSUPDATE();
    sleep(1);
    
    MUTEX_lock {
        ret = io_hl_InitZaehlerKanal1();
        if( ret == E_OK ) printf( "TEST.C: Zaehler initialisiert.\n" );
        else              printf( "TEST.C: FEHLER beim Initialisieren des Zaehlers.\n" );
    } MUTEX_unlock();

    KBUSUPDATE();
    sleep(1);
}

/**
 * @brief eigentlicher Steuerungsprozess.
 *
 * test_run() wird zyklisch ueber einen Systemtimer in \ref main.c aufgerufen.
 * @param sig enthaelt das ausloesende Signal. Dieser Parameter wird aber nicht benoetigt.
 * @return kein
 */
void test_run( int sig )
{
    u8_t            data_u8;
    u16_t			data_u16;
    temperatur_t    data_temperatur;

    MUTEX_lock {
        /* Eine RTE Funktion aufrufen */
        (void) io_ll_read_Zaehler1( &data_u16 );
        /* Eine hoeher angesiedelte Block Run Funktion mit Inferfaces aufrufen */
        (void) Block1.Run( &Block1 );

        printf( "TEST.C: Zaehler 1 = %5d (16bit Wert)\n", data_u16 );
/*
        (void) io_ll_read_Zaehler2( &data_u16 );
        printf( "TEST.C: Zaehler 2 = %5d (16bit Wert)\n", data_u16 );

        (void) io_ll_read_Temperatur1( &data_temperatur );
        printf( "TEST.C: Temperaturmesswert 1 = %6.2f\n", data_temperatur );
        (void) io_ll_read_Temperatur2( &data_temperatur );
        printf( "TEST.C: Temperaturmesswert 2 = %6.2f\n", data_temperatur );
        (void) io_ll_read_Temperatur3( &data_temperatur );
        printf( "TEST.C: Temperaturmesswert 3 = %6.2f\n", data_temperatur );
        (void) io_ll_read_Temperatur4( &data_temperatur );
        printf( "TEST.C: Temperaturmesswert 4 = %6.2f\n", data_temperatur );
*/
        KBUSUPDATE();
    } MUTEX_unlock();
}

/**
 * \brief Steuerungsprozess beenden.
 * Diese Funktion duerfte im laufenden Prozess nie gerufen werden.
 */
void test_close( void )
{
    KBUSCLOSE();
}
