#include <stdio.h>
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* Prototypen */
float toGradCelsius( temp10_pt1000_t messstelle );

void cntrl_Speicher1( void )
{
    kes_Tvl_SW_Sp1_f = toGradCelsius(sol_sp1_t_min + kes_sp_dt_sw);

#ifdef __DEBUG__
    printf( "DEBUG: kes_Tvl_SW_Sp1_f = %5.2f\n", kes_Tvl_SW_Sp1_f );
    printf( "DEBUG: SOL_SP1_To_MW = %d\n", SOL_SP1_To_MW );
    printf( "DEBUG: partytime_flg = %d\n", partytime_flg );
    printf( "DEBUG: sol_sp1_t_min = %d\n", sol_sp1_t_min );
#endif

    if( SOL_SP1_To_MW < sol_sp1_t_min ) {
        if( (z_Duschzeit == zJa) || (partytime_flg == SET) ) {
#ifdef __DEBUG__
            printf( "DEBUG: Pumpe Sp1 EIN!\n" );
#endif
            KES_PU_SP1_SB = IO_EIN;
        }
        else {
#ifdef __DEBUG__
            printf( "DEBUG: Pumpe Sp1 AUS!\n" );
#endif
            KES_PU_SP1_SB = IO_AUS;
        }
    }
    else {  /* if( SOL_SP1_To_MW >= sol_sp1_t_min ) { */
#ifdef __DEBUG__
        printf( "DEBUG: Pumpe Sp1 AUS!\n" );
#endif
        KES_PU_SP1_SB = IO_AUS;
    }

    if( hk_mv_y_f > 95.0 ) { /* Wenn HK Mischventil > 95% */
        /* Problem wenn Heizkreis zu hohe Anforderung hat */
#ifdef __DEBUG__
        printf( "DEBUG: Pumpe Sp1 EIN wegen hk_mv_y_f > 95.0 !\n" );
#endif
        KES_PU_SP1_SB = IO_EIN;
    }
}
