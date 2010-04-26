#define _MAIN_C_

#include <unistd.h>
#ifdef __WAGO__
#include <asm/types.h>
#include "kbusapi.h"
#endif

#include "io.h"
#include "vorgabe.h"
#include "variablen.h"

/* importierte Prototypen */
int init_parameters( void );
int init_zeitprogramm( void );
void init_variables( void );

void cntrl_task( void );
void cntrl_initAverageTau( temp10_pt1000_t currTau );

#ifdef _REENTRANT
void *main_thread( void *arg )
#else
void main( void )
#endif
{
    int prog_state_toggle = IO_AUS;
    int cnt;

    init_parameters();
    init_variables();
    init_zeitprogramm();
#ifdef __WAGO__
    KbusOpen();
    KbusUpdate();
#endif
    cntrl_initAverageTau( ALL_Tau_MW );

    /*  Hauptschleife (endlos) */
    while( 1 ) {
        if( prog_state_toggle == IO_AUS ) prog_state_toggle = IO_EIN;
        else                              prog_state_toggle = IO_AUS;
        CONTROL_AKTIV = prog_state_toggle;

        /* Sammeltask mit allen Reglerfunktionen aufrufen */
        cntrl_task();
#ifdef __DEBUG__
        printf( "DEBUG: Hauptschleifenzaehler = %d\n", cnt++ );
#endif
        /* Sleep() funktioniert nur unter UNIX/Linux, nicht unter Windows */
        sleep(1);
    }
#ifdef __WAGO__
    KbusClose();
#endif
}
