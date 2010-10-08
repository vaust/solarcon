#define _FB_C_

#include "gen_types.h"
#include "fb.h"
#include "sup.h"
#include "param.h"

/** \brief Fussbodenheizung Initialisierung.
    \param par_p Pointer auf die Struktur mit allen relevanten Parametern
    \param q_p Pointer auf reglerspezifische Parameter fuer den Mischventilregler
    \param out_p Pointer auf Ausgangsgroessen
    \return kein
*/
void fb_Init( fb_param_t *par_p, sup_digreg_coeff_t *q_p, fb_out_t *out_p )
{
    /* Vorgaben aus Parametrierung */
    par_p->frostschutz  = param_all_frostschutz;
    par_p->at_start     = param_all_at_start;
    par_p->reg_kp       = param_fb_reg_kp;
    par_p->reg_ki       = param_fb_reg_ki;
    par_p->reg_tn       = param_fb_reg_tn;
    par_p->TA           = ABTASTZEIT;
    par_p->tvl_absenk   = param_fb_tvl_absenk;
    par_p->tvl_max      = param_fb_tvl_max;
    par_p->tvl_min      = param_fb_tvl_min;
    par_p->tvl_niveau   = param_fb_tvl_niveau;
    par_p->tvl_steigung = param_fb_tvl_steigung;
    par_p->tr_sw        = param_fb_tr_sw;

    sup_DigRegInit( q_p, &(out_p->prim_mv_y), ABTASTZEIT, par_p->reg_kp, par_p->reg_ki, MIN_Y_PCT, MAX_Y_PCT );
    
    out_p->prim_pu_sb = IO_AUS;
    out_p->sek_pu_sb = IO_AUS;
}

/** \brief Fussbodenheizung Reglerfunktion
    \param par_p[in] Pointer auf die Struktur mit allen relevanten Parametern
    \param q_p[in] Pointer auf reglerspezifische Parameter fuer den Mischventilregler
    \param in_p[in] Pointer auf Struktur mit allen Eingabegroessen
    \param out_p[out] Pointer auf Struktur mit allen Ausgangsgroessen
    \return kein
*/
void fb_Run( const fb_param_t *par_p, 
             const sup_digreg_coeff_t *q_p, 
             const fb_in_t *in_p, 
                   fb_out_t *out_p )
{
    /* Vorlauftemperatursollwert im Floatformat berechnen  */
    out_p->tvl_sw =  (par_p->tr_sw - in_p->tau_mw) * par_p->tvl_steigung
                    + par_p->tr_sw + par_p->tvl_niveau;
    if( (in_p->zustand == zAbgesenkt) && (in_p->partytime_flg == RESET) ) {
        out_p->tvl_sw -= par_p->tvl_absenk;
    }
    sup_Limit( &(out_p->tvl_sw), par_p->tvl_min, par_p->tvl_max );

    /* Mischventil PI-Regleralgorithmus mit Anti Windup */
    sup_DigRegler( q_p, out_p->tvl_sw, in_p->sek_tvl_mw, &(out_p->prim_mv_y) );

    if(   (in_p->tau_avg <  par_p->at_start) && /* Die mittlere Aussentemperatur liegt unter der Betriebsschwelle */
          (out_p->tvl_sw >  20.0           )    /* Der berechnete Vorlauftemperatursollwert liegt unter 20 Grad C */
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
