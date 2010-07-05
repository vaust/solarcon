#include <stdio.h>
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* Speicher 1 = Warmwasser und Heizkoerper
   Speicher 2 = Fussbodenheizung            */

void cntrl_Speicher( void )
{
    /* Berechne Solltemperatur Speicher 1: */
    if( (z_Duschzeit == zJa) && (hk_Tvl_SW_f < ww_tww_sw + kes_sp_dt_sw/2.0) )
        sol_SP1_To_SW_f = ww_tww_sw + kes_sp_dt_sw/2.0;
    else
        sol_SP1_To_SW_f = hk_Tvl_SW_f + kes_sp_dt_sw/2.0;

    /* Berechne Solltemperatur Speicher 2: */
    sol_SP2_To_SW_f = fb_Tvl_SW_f + kes_sp_dt_sw/2.0;


    /********************************************
     * Schaltkriterium fuer Speicherladepumpe 1
     ********************************************/
    if( SOL_SP1_To_MW < sol_SP1_To_SW_f ) {
        kes_Tvl_SW_Sp1_f = sol_SP1_To_SW_f + kes_sp_dt_sw;
        if( (KES_BR_BM == IO_EIN) || (KES_Tvl_MW > SOL_SP1_To_MW) ) KES_PU_SP1_SB = IO_EIN;
        /* Wenn Sp.-pumpe 1 ein, Sp.-pumpe 2 immer aus! */
        KES_PU_SP2_SB = IO_AUS;
    }
    else if( SOL_SP1_To_MW >= (sol_SP1_To_SW_f + kes_sp_dt_sw/2.0) ) {
        kes_Tvl_SW_Sp1_f = 0.0;   /* Kessel AUS */
        KES_PU_SP1_SB = IO_AUS;
    }


    /********************************************
     * Schaltkriterium fuer Speicherladepumpe 2
     ********************************************/
    if( KES_PU_SP1_SB == IO_AUS ) {
        /* Sp.-pumpe 2 nur einschalten, wenn Sp.-pumpe 1 aus ist! */
        if( SOL_SP2_To_MW < sol_SP2_To_SW_f ) {
            kes_Tvl_SW_Sp2_f = sol_SP2_To_SW_f + kes_sp_dt_sw;
            if( (KES_BR_BM == IO_EIN) || (KES_Tvl_MW > SOL_SP2_To_MW) ) KES_PU_SP2_SB = IO_EIN;
        }
        else if( SOL_SP2_To_MW >= (sol_SP2_To_SW_f + kes_sp_dt_sw/2.0) ) {
            kes_Tvl_SW_Sp2_f = 0.0;  /* Kessel AUS */
            KES_PU_SP2_SB = IO_AUS;
        }
    }
    else /* if( KES_PU_SP1_SB == IO_EIN ) */ {
        KES_PU_SP2_SB = IO_AUS;
    }

    /*
     * Notfall in dem Sp.-pumpe 2 immer laufen soll:
     */
    if( SOL_SP2_To_MW < fb_Tvl_SW_f - kes_sp_dt_sw/2.0 ) {
        if( KES_BR_BM == IO_EIN ) KES_PU_SP2_SB = IO_EIN;
    }
}

