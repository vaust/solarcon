#define _WW_C_

#include "param.h"
#include "ww.h"

static void ww_MV_Steuerung( const ww_param_t *par_p, const ww_in_t *in_p, ww_out_t *out_p )
{
    out_p->hzg_tvl_sw = par_p->tww_sw + par_p->kes_sp_dt_sw/2.0;
    if( in_p->sol_sp1_to_mw > in_p->hzg_trl_mw ) {
        out_p->hzg_mv_y =
            (out_p->hzg_tvl_sw - in_p->hzg_trl_mw) * 100.0 / 
                (in_p->sol_sp1_to_mw - in_p->hzg_trl_mw)  
          + (out_p->hzg_tvl_sw - out_p->hzg_tvl_sw) * par_p->mv_korr;            
    } else
    {
        out_p->hzg_mv_y = MAX_Y_PCT;  /* dann stimmt was nicht -> Ventil voll auf */
    }
    sup_Limit( &(out_p->hzg_mv_y), MIN_Y_PCT, MAX_Y_PCT );
}

static void ww_VV_Steuerung( const ww_param_t *par_p, const ww_in_t *in_p, ww_out_t *out_p )
{
    if( in_p->tau_avg        > par_p->at_start ) {
        if( in_p->hzg_trl_mw < in_p->sol_sp2_tu_mw ) out_p->hzg_vv_sb = WW_VV_SP2;
        else                                         out_p->hzg_vv_sb = WW_VV_SP1;
    }
    else {
        if( in_p->hzg_trl_mw < in_p->hk_tvl_sw )     out_p->hzg_vv_sb = WW_VV_SP2;
        else                                         out_p->hzg_vv_sb = WW_VV_SP1;
    }
}   
 
static void ww_Schwachlast_Steuerung( const ww_param_t *par_p, ww_out_t *out_p )
{
    static u16_t    schwachlastzeit = 0;

    /* Pumpe waehrend Duschbetrieb nicht abschalten, wegen Schwingung */
    if( out_p->hzg_pu_y < par_p->hzg_pu_y_min ) {
        schwachlastzeit ++;
        if( schwachlastzeit < par_p->schwachlastzeit_max ) {
            out_p->hzg_pu_y = par_p->hzg_pu_y_min;
        }
    } /* nach 30s ununterbrochener Schwachlast darf die Pumpe abschalten */
    else {
        schwachlastzeit = 0;
    }
}
    
void ww_Init( ww_param_t *par_p, sup_digreg_coeff_t *q_hzg_pu_p )
{
    par_p->pu_reg_kp = param_ww_pu_reg_kp;
    par_p->pu_reg_tn = param_ww_pu_reg_tn;
    par_p->mv_reg_kp = -0.0;   /* Momentan nicht genutzt */
    par_p->mv_reg_tn = -0.0;   /* Momentan nicht genutzt */
    par_p->TA = ABTASTZEIT;
    par_p->kes_sp_dt_sw = param_kes_sp_dt_sw;
    par_p->frostschutz = param_all_frostschutz;
    par_p->at_start = param_all_at_start;
    par_p->mv_korr = param_ww_mv_korr;
    par_p->hzg_pu_y_min = 11.0;
    par_p->schwachlastzeit_max = 300;

    q_hzg_pu_p->q0 =  par_p->pu_reg_kp + par_p->TA/par_p->pu_reg_tn;
    q_hzg_pu_p->q1 = -par_p->pu_reg_kp;
    q_hzg_pu_p->lower_limit = MIN_Y_PCT;
    q_hzg_pu_p->upper_limit = MAX_Y_PCT;
}    

void ww_Run( const ww_param_t         *par_p, 
             const sup_digreg_coeff_t *q_hzg_pu_p, 
             const ww_in_t            *in_p, 
                   ww_out_t           *out_p )
{

    /* WW Heizungspumpe immer ein! */
    out_p->hzg_pu_sb = IO_EIN;

    /* Zirkulationspumpe ansteuern */
    if( (in_p->zirkzustand == zEin) || (in_p->tau_mw < par_p->frostschutz) ) 
        out_p->zirk_pu_sb = IO_EIN;
    else 
        out_p->zirk_pu_sb = IO_AUS;
    
    /* PI-Regler fuer WW Heizungspumpe */
    sup_DigRegler( q_hzg_pu_p, par_p->tww_sw, in_p->tww_mw, &(out_p->hzg_pu_y) );

    /* Berechnung von WW_HZG_MV_Y aus den Temperaturen von Speicher und Rücklauf */
    ww_MV_Steuerung( par_p, in_p, out_p );
    
    /* Schwachlast Steuerung */
    ww_Schwachlast_Steuerung( par_p, out_p );
    
    /* Kriterium fuer Warmwasser Heizungsverteilventil */
    ww_VV_Steuerung( par_p, in_p, out_p );
}


