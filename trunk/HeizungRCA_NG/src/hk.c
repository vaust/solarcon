#ifndef _HK_C_
#define _HK_C_
#endif

#include "gen_types.h"
#include "param.h"
#include "hk.h"
#include "sup.h"

void hk_Init( hk_param_t *par_p, sup_digreg_coeff_t *q_p, hk_out_t *out_p )
{
    /* Vorgaben aus Parametrierung */
    par_p->frostschutz  = param_all_frostschutz;
    par_p->at_start     = param_all_at_start;
    par_p->reg_kp       = param_fb_reg_kp;
    par_p->reg_tn       = param_fb_reg_tn;
    par_p->TA           = ABTASTZEIT;
    par_p->tvl_absenk   = param_fb_tvl_absenk;
    par_p->tvl_max      = param_fb_tvl_max;
    par_p->tvl_min      = param_fb_tvl_min;
    par_p->tvl_niveau   = param_fb_tvl_niveau;
    par_p->tvl_steigung = param_fb_tvl_steigung;
    par_p->tr_sw        = param_hk_tr_sw;
    
    /* abgeleitete Groessen */
    q_p->q0 =  par_p->reg_kp + par_p->TA/par_p->reg_tn;
    q_p->q1 = -par_p->reg_kp;
    q_p->lower_limit = MIN_Y_PCT;
    q_p->upper_limit = MAX_Y_PCT;
    sup_DigRegInit( q_p, &(out_p->mv_y) );
}    

/* Regler fuer den Waermetauscher, der den Heizkoerperheizkreis beheizt */
void hk_Run( const hk_param_t         *par_p, 
             const sup_digreg_coeff_t *q_p, 
             const hk_in_t            *in_p, 
                   hk_out_t           *out_p )
{
    /* Vorlauftemperatursollwert im Floatformat berechnen   */
    out_p->tvl_sw = (par_p->tr_sw - in_p->tau_mw) * par_p->tvl_steigung + par_p->tr_sw + par_p->tvl_niveau;
    if( (in_p->zustand == zAbgesenkt) && (in_p->partytime_flg == RESET) ) {
        out_p->tvl_sw -= par_p->tvl_absenk;
    }

    sup_Limit( &(out_p->tvl_sw), par_p->tvl_min, par_p->tvl_max );
    sup_DigRegler( q_p, out_p->tvl_sw, in_p->tvl_mw, &(out_p->mv_y) );

    if( (in_p->tau_avg < par_p->at_start) &&            /* mittlere AT unter Betriebsschwelle */          
        (out_p->tvl_sw > 30.0           )    )          /* VL-Temp. ab der HK wirklich heizt */ 
        out_p->pu_sb = IO_EIN;                          /* Heizkreis Pumpe einschalten */
    else if( in_p->tau_avg > (par_p->at_start+1.0) )
        out_p->pu_sb = IO_AUS;                          /* Heizkreis Pumpe ausschalten */
    else if (in_p->tau_mw < par_p->frostschutz )        /* AT unter Frostschutzmarke */
        out_p->pu_sb = IO_EIN;                          /* Heizkreis Pumpe einschalten */
}

