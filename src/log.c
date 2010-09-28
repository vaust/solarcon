#include <stdio.h>
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* Prototypen */

/* Logging aller Messwerte und wichtigen Parameter in eine Datei */
void log_variables( FILE *fp )
{
    time_t  aktZeit;
    char    *time_str;

    time( &aktZeit );
    time_str = asctime( localtime( &aktZeit ) );
    fprintf( fp, "%24s  ALL_Tau_MW    = %5.1f C\n", time_str,  ALL_Tau_MW    );
    fprintf( fp, "%24s  SOL_KOLL_T_MW = %5.1f C\n", time_str,  SOL_KOLL_T_MW );
    fprintf( fp, "%24s  SOL_SP1_Tu_MW = %5.1f C\n", time_str,  SOL_SP1_Tu_MW );
    fprintf( fp, "%24s  SOL_SP1_To_MW = %5.1f C\n", time_str,  SOL_SP1_To_MW );
    fprintf( fp, "%24s  SOL_SP2_Tu_MW = %5.1f C\n", time_str,  SOL_SP2_Tu_MW );
    fprintf( fp, "%24s  SOL_SP2_To_MW = %5.1f C\n", time_str,  SOL_SP2_To_MW );
    fprintf( fp, "%24s  KES_Tvl_MW    = %5.1f C\n", time_str,  KES_Tvl_MW );
    fprintf( fp, "%24s  KES_Trl_MW    = %5.1f C\n", time_str,  KES_Trl_MW );
    fprintf( fp, "%24s  HK_Tvl_MW     = %5.1f C\n", time_str,  HK_Tvl_MW  );
    fprintf( fp, "%24s  HK_Trl_MW     = %5.1f C\n", time_str,  HK_Trl_MW  );
    fprintf( fp, "%24s  WW_HZG_Tvl_MW = %5.1f C\n", time_str,  WW_HZG_Tvl_MW );
    fprintf( fp, "%24s  WW_HZG_Trl_MW = %5.1f C\n", time_str,  WW_HZG_Trl_MW );
    fprintf( fp, "%24s  WW_Tww_MW     = %5.1f C\n", time_str,  WW_Tww_MW );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  FB_PRIM_Trl_MW = %5.1f C\n", time_str,  FB_PRIM_Trl_MW );
    fprintf( fp, "%24s  FB_SEK_Tvl_MW  = %5.1f C\n", time_str,  FB_SEK_Tvl_MW );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  all_Partyzeit_i  = %d\n", time_str, all_Partyzeit_i );
    fprintf( fp, "%24s  kes_Tvl_SW_Sp1_f = %5.1f C\n", time_str, kes_Tvl_SW_Sp1_f );
    fprintf( fp, "%24s  kes_Tvl_SW_Sp2_f = %5.1f C\n", time_str, kes_Tvl_SW_Sp2_f );
    fprintf( fp, "%24s  hk_Tvl_SW_f      = %5.1f C\n", time_str, hk_Tvl_SW_f );
    fprintf( fp, "%24s  fb_Tvl_SW_f      = %5.1f C\n", time_str, hk_Tvl_SW_f );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  Tau_1h_mittel_f  = %6.2f C\n", time_str, Tau_1h_mittel_f );
    fprintf( fp, "%24s  Tau_36h_mittel_f = %6.2f C\n", time_str, Tau_36h_mittel_f );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  KES_PU_SP1_SB = %d \n", time_str, KES_PU_SP1_SB );
    fprintf( fp, "%24s  KES_PU_SP2_SB = %d \n", time_str, KES_PU_SP2_SB );
    fprintf( fp, "%24s  KES_Tvl_Y = %d \n", time_str, KES_Tvl_Y );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  FB_PRIM_MV_Y = %d \n", time_str,  FB_PRIM_MV_Y  );
    fprintf( fp, "%24s  FB_PRIM_PU_SB = %d \n", time_str, FB_PRIM_PU_SB  );
    fprintf( fp, "%24s  FB_SEK_PU_SB = %d \n", time_str, FB_SEK_PU_SB  );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  WW_HZG_MV_Y = %d \n", time_str, WW_HZG_MV_Y  );
    fprintf( fp, "%24s  WW_HZG_VV_SB = %d \n", time_str, WW_HZG_VV_SB );
    fprintf( fp, "%24s  WW_HZG_PU_SB = %d \n", time_str, WW_HZG_PU_SB );
    fprintf( fp, "%24s  WW_ZIRK_PU_SB = %d \n", time_str, WW_ZIRK_PU_SB );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  HK_PU_SB = %d \n", time_str, HK_PU_SB );
    fprintf( fp, "%24s  HK_MV_Y = %d \n", time_str,  HK_MV_Y );
    fprintf( fp, "%24s  hk_Tvl_SW_f = %f \n", time_str, hk_Tvl_SW_f );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  WW_PARTY = %d \n", time_str, WW_PARTY );
    fprintf( fp, "%24s  STOERUNG = %d \n", time_str,  STOERUNG );
    fprintf( fp, "%24s  CONTROL_AKTIV = %d \n", time_str, CONTROL_AKTIV );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  KES_SSM = %d \n", time_str, KES_SSM );
    fprintf( fp, "%24s  KES_BR_BM = %d \n", time_str, KES_BR_BM );
    fprintf( fp, "\n" );
}
