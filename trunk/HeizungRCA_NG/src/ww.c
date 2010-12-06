#define _WW_C_

#include "param.h"
#include "ww.h"

// #define __SCHWACHLAST__

/** 
  * Steuert die Stellung des Mischventils, das die Vorlauftemperatur fuer den Warmwasser-
  * Waermetauscher.
  * \param par_p Pointer auf Struktur mit Parametern
  * \param in_p  Pointer auf Struktur mit den Eingangsgroessen
  * \param out_p Pointer auf Struktur mit der Ausgangsgroesse Stellwert  
  * \return kein
  */
static 
void ww_MV_Steuerung( const ww_param_t *par_p,
                      const ww_in_t    *in_p,
                            ww_out_t   *out_p )
{
    out_p->hzg_tvl_sw = par_p->tww_sw + par_p->kes_sp_dt_sw;
    if( in_p->sp1_to_mw > in_p->hzg_trl_mw ) {
        out_p->hzg_mv_y.y =
            (out_p->hzg_tvl_sw - in_p->hzg_trl_mw) * 100.0 /
                (in_p->sp1_to_mw - in_p->hzg_trl_mw)
          + (out_p->hzg_tvl_sw - in_p->hzg_tvl_mw) * par_p->mv_korr;
    } else
    {
        out_p->hzg_mv_y.y = MAX_Y_PCT;  /* dann stimmt was nicht -> Ventil voll auf */
    }
    sup_Limit( &(out_p->hzg_mv_y.y), MIN_Y_PCT, MAX_Y_PCT );
}

/** 
  * Verteilventil zwischen den Speichern 1 und 2 entsprechend der Speichertemperaturen
  * einstellen.
  * \param par_p Pointer auf Struktur mit Parametern
  * \param in_p  Pointer auf Struktur mit den Eingangsgroessen
  * \param out_p Pointer auf Struktur mit der Ausgangsgroesse Stellwert  
  * \return kein
  */
static 
void ww_VV_Steuerung( const ww_param_t *par_p,
                      const ww_in_t    *in_p,
                            ww_out_t   *out_p )
{
    if( in_p->tau_avg        > par_p->at_start ) {
        if( in_p->hzg_trl_mw < in_p->sp2_tu_mw ) out_p->hzg_vv_sb = WW_VV_SP2;
        else                                     out_p->hzg_vv_sb = WW_VV_SP1;
    }
    else {
        if( in_p->hzg_trl_mw < in_p->hk_tvl_sw ) out_p->hzg_vv_sb = WW_VV_SP2;
        else                                     out_p->hzg_vv_sb = WW_VV_SP1;
    }
}

#ifdef __SCHWACHLAST__
/** 
  * Schwachlaststeuerung soll eingreifen, wenn nur wenig Warmwasser gebraucht wird und 10% 
  * Pumpenleistung fuer den Waermetauscher bereits zu viel Leistung bringt
  * \param par_p Pointer auf Struktur mit Parametern
  * \param out_p Pointer auf Struktur mit der Ausgangsgroesse Stellwert  
  * \return kein
  */
static 
void ww_Schwachlast_Steuerung( const ww_param_t *par_p,
                                     ww_out_t   *out_p )
{
    static u16_t    schwachlastzeit = 0;

    /* Pumpe waehrend Duschbetrieb nicht abschalten, wegen Schwingung */
    if( out_p->hzg_pu_y.y < par_p->hzg_pu_y_min ) {
        schwachlastzeit ++;
        if( schwachlastzeit < par_p->schwachlastzeit_max ) {
            out_p->hzg_pu_y.y = par_p->hzg_pu_y_min;
        }
    } /* nach 30s ununterbrochener Schwachlast darf die Pumpe abschalten */
    else {
        schwachlastzeit = 0;
    }
}
#endif

/**
  * \brief Initialisierung der ww-Task.
  * Die minimale Pumpenleistung wird bei 11% Stellgroesse erreicht. Unter 10% ist die 
  * Pumpe aus. Der PI-Regler der fuer die wird hier mit initialisiert.
  * \param par_p Pointer auf Struktur mit Parametern
  * \param out_p Pointer auf Struktur mit der Ausgangsgroesse Stellwert  
  * \param q_hzg_pu_p Pointer auf Struktur mit den PI-Regler-Parametern
  * \return kein
  */
void ww_Init( ww_param_t         *par_p,
              sup_digreg_coeff_t *q_hzg_pu_p,
              ww_out_t           *out_p )
{
    par_p->pu_reg_kp           = param_ww_pu_reg_kp;
    par_p->pu_reg_ki           = param_ww_pu_reg_ki;
    par_p->TA                  = USEC2SEC(param_sys_zykluszeit);
    par_p->kes_sp_dt_sw        = param_kes_sp_dt_sw;
    par_p->tww_sw              = param_ww_tww_sw;
    par_p->frostschutz         = param_all_frostschutz;
    par_p->at_start            = param_all_at_start;
    par_p->mv_korr             = param_ww_mv_korr;
    par_p->hzg_pu_y_min        = 11.0;
    par_p->schwachlastzeit_max = 300;

    sup_DigRegInit( q_hzg_pu_p, &(out_p->hzg_pu_y), USEC2SEC(param_sys_zykluszeit),
                    par_p->pu_reg_kp, par_p->pu_reg_ki, MIN_Y_PCT, MAX_Y_PCT );
}

/**
  * \brief Eigentlicher Warmwasser Task
  * \param par_p Pointer auf Struktur mit Parametern
  * \param q_hzg_pu_p Pointer auf Struktur mit den PI-Regler-Parametern der Pumpe
  * \param in_p  Pointer auf Struktur mit den Eingangsgroessen fuer WW
  * \param out_p Pointer auf Struktur mit allen Ausgangsgroessen fuer WW
  * \return kein  
  */
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

    /* Berechnung von WW_HZG_MV_Y aus den Temperaturen von Speicher und Ruecklauf */
    ww_MV_Steuerung( par_p, in_p, out_p );

    /* Schwachlast Steuerung */
#ifdef __SCHWACHLAST__
    ww_Schwachlast_Steuerung( par_p, out_p );
#endif
    /* Kriterium fuer Warmwasser Heizungsverteilventil */
    ww_VV_Steuerung( par_p, in_p, out_p );
}

/**
 * \brief Befuellen des Eingangsvektors
 */
void ww_WriteInp(           ww_in_t    *in_p,
                      const float       tww_mw,
                      const float       tau_mw,
                      const float       tau_avg,
                      const u32_t       wz_mw,
                      const float       hzg_tvl_mw,
                      const float       hzg_trl_mw,
                      const float       hk_tvl_sw,
                      const float       sp1_to_mw,
                      const float       sp2_tu_mw,
                      const ein_aus_t   zirkzustand,
                      const nutzzeit_t  duschzeit    )
{
    in_p->tww_mw       = tww_mw;
    in_p->tau_mw       = tau_mw;
    in_p->tau_avg      = tau_avg;
    in_p->wz_mw        = wz_mw,
    in_p->hzg_tvl_mw   = hzg_tvl_mw;
    in_p->hzg_trl_mw   = hzg_trl_mw;
    in_p->hk_tvl_sw    = hk_tvl_sw;
    in_p->sp1_to_mw    = sp1_to_mw;
    in_p->sp2_tu_mw    = sp2_tu_mw,
    in_p->zirkzustand  = zirkzustand;
    in_p->duschzeit    = duschzeit;
}

