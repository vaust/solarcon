#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "sup.h"

void ww_Init( hk_param_t *par_p, sup_digreg_coeff_t *q_p, hk_out_t *out_p )
{
    q_p->q0 =  par_p->pu_reg_kp + par_p->TA/par_p->pu_reg_tn;
    q_p->q1 = -par_p->pu_reg_kp;
    q_p->lower_limit = MIN_Y_PCT;
    q_p->upper_limit = MAX_Y_PCT;
}    

void cntrl_WW_Heizkreis( void )
{
//  static int      old_ww_wz_mw = IO_AUS; /* Merker fuer vorhergehenden Status Wasserzaehlerimpuls */
//  static long     old_ww_Zaehler_l = 0;  /* Merker für vorhergehenden Wasserzaehlerstand */

    float           xd_pu;                 /* Regelabweichung Soll - Ist */
    static float    xd_pu_alt = 0;
    float           xd_mv;                 /* Regelabw. fuer Mischer */
    static float    xd_mv_alt = 0;

    float           ww_hzg_mv_y_f;
    static float    ww_hzg_mv_y_alt_f = 50.0; /* % */
    float           ww_hzg_pu_y_f;
    static float    ww_hzg_pu_y_alt_f = 11.0; /* 11% ist Zirkulationsgrundwert */
    float           q0, q1;
    const float     TA = 1.0;    /* Abtastzeit in sec                          */

    static int      schwachlastzeit = 0;


    /* WW Heizungspumpe immer ein! */
    WW_HZG_PU_SB = IO_EIN;

    /* Zirkulationspumpe ansteuern */
    if( (z_Zirk_Zustand == zEin) || (ALL_Tau_MW < all_frostschutz) ) {
        WW_ZIRK_PU_SB = IO_EIN;
    }
    else {
        WW_ZIRK_PU_SB = IO_AUS;
    }
    
    /* PI-Regler fuer WW Heizungspumpe */
    sup_DigRegler( q_p, ww_tww_sw, WW_Tww_MW, &ww_hzg_pu_y_f );

    /* Pumpe waehrend Duschbetrieb nicht abschalten, wegen Schwingung */
    if( ww_hzg_pu_y_f < 11.0 ) {
        schwachlastzeit ++;
        if( schwachlastzeit < 300 ) {
            ww_hzg_pu_y_f = 11.0;
        }
    } /* nach 30s ununterbrochener Schwachlast darf die Pumpe abschalten */
    else {
        schwachlastzeit = 0;
    }

    sup_Limit( &(ww_hzg_pu_y_f),     MIN_Y_PCT, MAX_Y_PCT );
    sup_Limit( &(ww_hzg_pu_y_alt_f), MIN_Y_PCT, MAX_Y_PCT );
    

    // ProzentToAnalogOut( ww_hzg_pu_y_f, (ao_0_10V_t *) &WW_HZG_PU_Y );


    /* Berechnung von WW_HZG_MV_Y aus den Temperaturen von Speicher und Rücklauf */

    ww_HZG_Tvl_SW_f = ww_tww_sw + kes_sp_dt_sw/2.0;
    if( SOL_SP1_To_MW > WW_HZG_Trl_MW )
        ww_hzg_mv_y_f =
            (ww_HZG_Tvl_SW_f - WW_HZG_Trl_MW) / (SOL_SP1_To_MW - WW_HZG_Trl_MW) * 100.0 
            + ( ww_HZG_Tvl_SW_f - WW_HZG_Tvl_MW) * ww_mv_korr;
            
    else
        ww_hzg_mv_y_f = 100.0;  /* dann stimmt was nicht -> Ventil voll auf */

    sup_Limit( &(ww_hzg_mv_y_f),     MIN_Y_PCT, MAX_Y_PCT );
    sup_Limit( &(ww_hzg_mv_y_alt_f), MIN_Y_PCT, MAX_Y_PCT );


    // ProzentToAnalogOut( ww_hzg_mv_y_f, (ao_0_10V_t *) &WW_HZG_MV_Y );


/* #define IO_VV_SP1       0x00
   #define IO_VV_SP2       0x01
*/
    /************************************************
     * Kriterium fuer Warmwasser Heizungsverteilventil
     ************************************************/
    if( Tau_36h_mittel_f > all_at_start ) {
        if( WW_HZG_Trl_MW < SOL_SP2_Tu_MW )     WW_HZG_VV_SB = IO_VV_SP2;
        else                                    WW_HZG_VV_SB = IO_VV_SP1;
    }
    else {
        if( WW_HZG_Trl_MW < hk_Tvl_SW_f )       WW_HZG_VV_SB = IO_VV_SP2;
        else                                    WW_HZG_VV_SB = IO_VV_SP1;
    }
}
