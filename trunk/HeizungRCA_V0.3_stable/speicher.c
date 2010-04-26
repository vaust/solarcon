#include <stdio.h>
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* Prototypen */
float toGradCelsius( temp10_pt1000_t messstelle );

void cntrl_Speicher( void )
{
    /* Ausschaltverzögerung für Speicherpumpe 2 */
    static unsigned int ausverz_kes_pu_sp2 = 0;  
    
    /* Berechne Solltemperatur Speicher 1: */
    kes_Tvl_SW_Sp1_f = toGradCelsius(sol_sp1_t_min + kes_sp_dt_sw);
    /* Berechne Solltemperatur Speicher 2: */
    kes_Tvl_SW_Sp2_f = fb_Tvl_SW_f + toGradCelsius(kes_sp_dt_sw);
    
#ifdef __DEBUG__
    printf( "DEBUG: kes_Tvl_SW_Sp1_f = %5.2f\n", kes_Tvl_SW_Sp1_f );
    printf( "DEBUG: kes_Tvl_SW_Sp2_f = %5.2f\n", kes_Tvl_SW_Sp2_f );
#endif

    /********************************************
     * Einschaltkriterium für Speicherladepumpe 1 
     ********************************************/
    if( SOL_SP1_To_MW < sol_sp1_t_min ) {
        if( (z_Duschzeit == zJa) || (partytime_flg == SET) ) {
            KES_PU_SP1_SB = IO_EIN;
            /* Wenn Sp.-pumpe 1 ein, Sp.-pumpe 2 immer aus! */
            KES_PU_SP2_SB = IO_AUS; 
            ausverz_kes_pu_sp2 = 0;
        }
        else {
            KES_PU_SP1_SB = IO_AUS;
            /* Wenn Sp.-pumpe 1 aus, Sp.-pumpe 2 3 min nachlaufen lassen! */
            KES_PU_SP2_SB = IO_EIN;
            ausverz_kes_pu_sp2 = 180; /* 180 sec = 3 min */
        }
    }
    else if( SOL_SP1_To_MW >= (sol_sp1_t_min + toGradCelsius(kes_sp_dt_sw)) ) {  
        KES_PU_SP1_SB = IO_AUS;
        /* Wenn Sp.-pumpe 1 aus, Sp.-pumpe 2 3 min nachlaufen lassen! */
        KES_PU_SP2_SB = IO_EIN;
        ausverz_kes_pu_sp2 = 180; /* 180 sec = 3 min */
    }

    /*
     * Problem wenn Heizkreis zu hohe Anforderung hat 
     * ( HK Mischventil > 95% ):
     */
    if( hk_mv_y_f > 95.0 ) {
        KES_PU_SP1_SB = IO_EIN;
        /* Wenn Sp.-pumpe 1 ein, Sp.-pumpe 2 immer aus! */
        KES_PU_SP2_SB = IO_AUS; 
        ausverz_kes_pu_sp2 = 0;
#ifdef __DEBUG__
        printf( "DEBUG: Pumpe Sp1 EIN wegen hk_mv_y_f > 95.0 !\n" );
#endif
    }
    
    
    /********************************************
     * Einschaltkriterium für Speicherladepumpe 2 
     ********************************************/
    if( KES_PU_SP1_SB == IO_AUS ) { 
        /* Sp.-pumpe 2 nur einschalten, wenn Sp.-pumpe 1 aus ist! */
        if( toGradCelsius(SOL_SP2_To_MW) < fb_Tvl_SW_f ) {
            KES_PU_SP2_SB = IO_EIN;
            ausverz_kes_pu_sp2 = 180; /* Nachlaufzeit 180 sec = 3 min */
        }
        else if( toGradCelsius(SOL_SP2_To_MW) >= (fb_Tvl_SW_f + toGradCelsius(kes_sp_dt_sw)) ) {
            ausverz_kes_pu_sp2 --; /* Ausschalten Sp.-pumpe 2 vorbereiten */
        }
        else if( ausverz_kes_pu_sp2 > 0 ) {
            KES_PU_SP2_SB = IO_EIN;
            ausverz_kes_pu_sp2 --;
        } 
        else {
            KES_PU_SP2_SB = IO_AUS;
        }
    }
    else /* if( KES_PU_SP1_SB == IO_EIN ) */ {
        KES_PU_SP2_SB = IO_AUS;
    }

    /*
     * Notfall in dem Sp.-pumpe 2 immer laufen soll: 
     */
    if( toGradCelsius(SOL_SP2_To_MW) < (fb_Tvl_SW_f - toGradCelsius(kes_sp_dt_sw)) ) {
        KES_PU_SP2_SB = IO_EIN;
    }
    
#ifdef __DEBUG__
    printf( "DEBUG: KES_PU_SP1_SB = %s\n", (KES_PU_SP1_SB == 0x00) ? "AUS" : "EIN" );
    printf( "DEBUG: KES_PU_SP2_SB = %s\n", (KES_PU_SP2_SB == 0x00) ? "AUS" : "EIN" );
    printf( "DEBUG: WW_HZG_VV_SB  = %s\n", (WW_HZG_VV_SB  == 0x00) ? "AUS" : "EIN" );
#endif
}

