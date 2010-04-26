#include <stdio.h>
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* Prototypen */
float toGradCelsius( temp10_pt1000_t messstelle );

void cntrl_Speicher2( void )
{
#ifdef __DEBUG__
    printf( "DEBUG: kes_Tvl_SW_Sp2_f = %5.2f\n", kes_Tvl_SW_Sp2_f );
    printf( "DEBUG: SOL_SP2_To_MW = %d\n", SOL_SP2_To_MW );
#endif

    kes_Tvl_SW_Sp2_f = fb_Tvl_SW_f + toGradCelsius(kes_sp_dt_sw);
    printf( "DEBUG: kes_Tvl_SW_Sp2_f = %5.2f\n", kes_Tvl_SW_Sp2_f );

    if( toGradCelsius(SOL_SP2_To_MW) < fb_Tvl_SW_f ) {
        KES_PU_SP2_SB = IO_EIN;
#ifdef __DEBUG__
        printf( "DEBUG: Pumpe SP 2 EIN!\n" );
#endif
    }
    else if( toGradCelsius(SOL_SP2_To_MW) >= (fb_Tvl_SW_f + toGradCelsius(kes_sp_dt_sw)) ) {
        KES_PU_SP2_SB = IO_AUS;
#ifdef __DEBUG__
        printf( "DEBUG: Pumpe SP 2 AUS!\n" );
#endif
    }
}
