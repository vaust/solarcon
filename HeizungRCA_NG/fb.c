#include "fb.h"
#include "vorgabe.h"
#include "variablen.h"
#include "io.h"
#include "sup.h"

void fb_Init( fb_param_t *par_p, digreg_coeff_t *q, fb_out_t *out_p )
{
    q->q0 =  par_p->reg_kp + par_p->TA/par_p->reg_tn;
    q->q1 = -par_p->reg_kp;
    q->lower_limit = MIN_Y_PCT;
    q->upper_limit = MAX_Y_PCT;
}

void fb_Run( const fb_param_t *par_p, const sup_digreg_coeff_t *q_p, const fb_in_t *in_p, fb_out_t *out_p )
{
    /* Vorlauftemperatursollwert im Floatformat berechnen  */
    out_p->tvl_sw =  (in_p->tr_sw - in_p->tau_mw) * par_p->tvl_steigung
                    + in_p->tr_sw + par_p->tvl_niveau;
    if( (in_p->zustand == zAbgesenkt) && (in_p->partytime_flg == RESET) ) {
        out_p->tvl_sw -= par_p->tvl_absenk;
    }
    sup_Limit( &(out_p->tvl_sw), par_p->tvl_min, par_p->tvl_max );

    /* Mischventil PI-Regleralgorithmus */
    sup_DigRegler( q_p, out_p->tvl_sw, in_p->sek_tvl_mw, &(out_p->prim_mv_y) );

    if(   (in_p->tau_avg <  par_p->at_start) && /* Die mittlere Aussentemperatur liegt unter der Betriebsschwelle */
          (out_p->tvl_sw >  20.0           )    /* Der berechnete Vorlauftemperatursollwert liegt unter 20°C      */
        ) {
        out_p->prim_pu_sb = IO_EIN;
        out_p->sek_pu_sb  = IO_EIN;
    }
    else if( in_p->tau_avg > (par_p->at_start+1.0) ) {
        out_p->prim_pu_sb = IO_AUS;
        out_p->sek_pu_sb  = IO_AUS;
    }
    else if( in_p->tau_mw < par_p->frostschutz ) {
        out_p->prim_pu_sb = IO_EIN;
        out_p->sek_pu_sb  = IO_EIN;
    }
}
