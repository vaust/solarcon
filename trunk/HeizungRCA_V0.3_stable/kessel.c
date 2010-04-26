#include <stdio.h>
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* importierte Prototypen */
void ProzentToAnalogOut( float scale ,ao_0_10V_t *ausgang );

void cntrl_Kessel( void )
{
    /* Sollwertvorgabe für den Kessel:
     * %-Zahl entspricht Vorlauftemperatur in °C
     * 100% entspr. 100°C
     * 10%  entpsr.  10°C
     * Werte kleiner 10%: Kessel ist abgeschaltet
     */

    if( KES_PU_SP1_SB >= IO_EIN ) {
#ifdef __DEBUG__
        printf( "DEBUG: Kessel auf %5.1f gestellt\n", kes_Tvl_SW_Sp1_f  );
#endif
        ProzentToAnalogOut( kes_Tvl_SW_Sp1_f, (ao_0_10V_t*) &KES_Tvl_Y );
    }
    else if( KES_PU_SP2_SB >= IO_EIN ) {
#ifdef __DEBUG__
       printf( "DEBUG: Kessel auf %5.1f gestellt\n", kes_Tvl_SW_Sp2_f  );
#endif
       ProzentToAnalogOut( kes_Tvl_SW_Sp2_f, (ao_0_10V_t*) &KES_Tvl_Y );
    }
    else {
#ifdef __DEBUG__
        printf( "DEBUG: Kessel auf 0 gestellt\n" );
#endif
        ProzentToAnalogOut( 0.0, (ao_0_10V_t*) &KES_Tvl_Y );
    }
}
