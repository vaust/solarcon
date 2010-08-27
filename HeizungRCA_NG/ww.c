#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "ww.h"
#include "sup.h"

void ww_Init( ww_param_t *par_p, sup_digreg_coeff_t *q_hzg_pu_p, ww_out_t *out_p )
{
    q_hzg_pu_p->q0 =  par_p->pu_reg_kp + par_p->TA/par_p->pu_reg_tn;
    q_hzg_pu_p->q1 = -par_p->pu_reg_kp;
    q_hzg_pu_p->lower_limit = 11.0;
    q_hzg_pu_p->upper_limit = MAX_Y_PCT;
}    

void ww_Run( const ww_param_t         *par_p, 
             const sup_digreg_coeff_t *q_hzg_pu_p, 
             const ww_in_t            *in_p, 
                   ww_out_t           *out_p )
{
//  static int      old_ww_wz_mw = IO_AUS; /* Merker fuer vorhergehenden Status Wasserzaehlerimpuls */
//  static long     old_ww_Zaehler_l = 0;  /* Merker für vorhergehenden Wasserzaehlerstand */
    static int      schwachlastzeit = 0;


    /* WW Heizungspumpe immer ein! */
    out_p->hzg_pu_sb = IO_EIN;

    /* Zirkulationspumpe ansteuern */
    if( (z_Zirk_Zustand == zEin) || (ALL_Tau_MW < all_frostschutz) ) {
        out_p->zirk_pu_sb = IO_EIN;
    }
    else {
        out_p->zirk_pu_sb = IO_AUS;
    }
    
    /* PI-Regler fuer WW Heizungspumpe */
    sup_DigRegler( q_hzg_pu_p, in_p->tww_sw, in_p->tww_mw, &(out_p->hzg_pu_y) );

    /* Pumpe waehrend Duschbetrieb nicht abschalten, wegen Schwingung */
    if( out_p->hzg_pu_y < 11.0 ) {
        schwachlastzeit ++;
        if( schwachlastzeit < 300 ) {
            out_p->hzg_pu_y = 11.0;
        }
    } /* nach 30s ununterbrochener Schwachlast darf die Pumpe abschalten */
    else {
        schwachlastzeit = 0;
    }

    /* Berechnung von WW_HZG_MV_Y aus den Temperaturen von Speicher und Rücklauf */

    out_p->hzg_tvl_sw = in_p->tww_sw + par_p->kes_sp_dt_sw/2.0;
    if( SOL_SP1_To_MW > WW_HZG_Trl_MW ) {
        out_p->hzg_mv_y =
            (out_p->hzg_tvl_sw - in_p->hzg_trl_mw) * 100.0 / 
                (in_p->sol_sp1_to_mw - in_p->hzg_trl_mw)  
          + (out_p->hzg_tvl_sw - out_p->hzg_tvl_sw) * par_p->mv_korr;            
    } else
    {
        out_p->hzg_mv_y = MAX_Y_PCT;  /* dann stimmt was nicht -> Ventil voll auf */
    }
    sup_Limit( &(out_p->hzg_mv_y), MIN_Y_PCT, MAX_Y_PCT );

    
/* #define IO_VV_SP1       0x00
   #define IO_VV_SP2       0x01
*/
    /************************************************
     * Kriterium fuer Warmwasser Heizungsverteilventil
     ************************************************/
    /* TODO: Wohin mit diesem Code ???

    if( Tau_36h_mittel_f > all_at_start ) {
        if( in_p->hzg_trl_mw < SOL_SP2_Tu_MW )     WW_HZG_VV_SB = IO_VV_SP2;
        else                                    WW_HZG_VV_SB = IO_VV_SP1;
    }
    else {
        if( in_p->hzg_trl_mw < hk_Tvl_SW_f )       WW_HZG_VV_SB = IO_VV_SP2;
        else                                    WW_HZG_VV_SB = IO_VV_SP1;
    }
    */
}
