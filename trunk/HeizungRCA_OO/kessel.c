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

    if( kes_Tvl_SW_Sp1_f >= kes_Tvl_SW_Sp2_f ) {
        ProzentToAnalogOut( kes_Tvl_SW_Sp1_f, (ao_0_10V_t*) &KES_Tvl_Y );
    }
    else {
        ProzentToAnalogOut( kes_Tvl_SW_Sp2_f, (ao_0_10V_t*) &KES_Tvl_Y );
    }
}
