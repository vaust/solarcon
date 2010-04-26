#include <stdio.h>
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

void cntrl_Solarbeheizung( void )
{
    if( (SOL_SP1_To_MW < sol_sp_t_max) && (SOL_SP2_To_MW < sol_sp_t_max) ) {
        /* Die Kollektortemperatur liegt unter dem Maximalwert  */
        if( SOL_KOLL_T_MW > ( SOL_SP1_Tu_MW + sol_dt_ein_sw ) ) {
            SOL_SP1_AV_SB = IO_AUF;
#ifdef __DEBUG__
            printf( "DEBUG: Solarabsperrventil SP1 AUF.\n" );
#endif
        }
        else {
            if( SOL_KOLL_T_MW <= ( SOL_SP1_Tu_MW + sol_dt_aus_sw ) ) {
                SOL_SP1_AV_SB = IO_ZU;
#ifdef __DEBUG__
                printf( "DEBUG: Solarabsperrventil SP1 ZU.\n" );
#endif
            }
            else {
                SOL_SP1_AV_SB = IO_AUF;
#ifdef __DEBUG__
                printf( "DEBUG: Solarabsperrventil SP1 AUF.\n" );
#endif
            }
        }

        if( SOL_KOLL_T_MW > ( SOL_SP2_Tu_MW + sol_dt_ein_sw ) ) {
            SOL_SP2_AV_SB = IO_AUF;
#ifdef __DEBUG__
            printf( "DEBUG: Solarabsperrventil SP2 AUF.\n" );
#endif
        }
        else {
            if( SOL_KOLL_T_MW <= ( SOL_SP2_Tu_MW + sol_dt_aus_sw ) ) {
                SOL_SP2_AV_SB = IO_ZU;
#ifdef __DEBUG__
                printf( "DEBUG: Solarabsperrventil SP2 ZU.\n" );
#endif
            }
            else {
                SOL_SP2_AV_SB = IO_AUF;
#ifdef __DEBUG__
                printf( "DEBUG: Solarabsperrventil SP2 AUF.\n" );
#endif
            }
        }
        /* Solarpumpe läuft, wenn eines der Ventile offen ist */
        if( (SOL_SP1_AV_SB == IO_ZU) && (SOL_SP2_AV_SB == IO_ZU) ) {
            SOL_PU_SB = IO_AUS;
        }
        else {
            SOL_PU_SB = IO_EIN;
        }
    }
    else {
        SOL_PU_SB     = IO_AUS;
        SOL_SP1_AV_SB = IO_ZU;
        SOL_SP2_AV_SB = IO_ZU;
#ifdef __DEBUG__
        printf( "DEBUG: Speichermaximaltemperatur erreicht: Solarpumpe AUS.\n" );
#endif
    }
}
