#define _WW_C_

#include "param.h"
#include "ww.h"

// #define __SCHWACHLAST__

/** 
  * \brief Steuerung des Mischventils.
  *
  * Steuert die Stellung des Mischventils, das die Vorlauftemperatur
  * fuer den Warmwasser-Waermetauscher einstellt.
  * \param self Pointer auf Instanz der Klasse ww_class_t
  * \return kein
  */
static 
void ww_MV_Steuerung( ww_class_t *self )
{
    self->o.hzg_tvl_sw = self->p.tww_sw + self->p.kes_sp_dt_sw;
    if( self->i.sp1_to_mw > self->i.hzg_trl_mw ) {
        self->o.hzg_mv_y =
            (self->o.hzg_tvl_sw - self->i.hzg_trl_mw) * 100.0 /
                (self->i.sp1_to_mw - self->i.hzg_trl_mw)
          + (self->o.hzg_tvl_sw - self->i.hzg_tvl_mw) * self->p.mv_korr;
    }
    else {
        self->o.hzg_mv_y = MAX_Y_PCT;  /* dann stimmt was nicht -> Ventil voll auf */
    }
    self->o.hzg_mv_y = reg_Limit( self->o.hzg_mv_y, MIN_Y_PCT, MAX_Y_PCT );
}

/** 
  * \brief Verteilventilsteuerung.
  *
  * Verteilventil zwischen den Speichern 1 und 2 entsprechend der Speichertemperaturen
  * einstellen.
  * \param self Pointer auf Instanz der Klasse ww_class_t
  * \return kein
  */
static 
void ww_VV_Steuerung( ww_class_t *self )
{
    if( self->i.tau_avg        > self->p.at_start ) {
        if( self->i.hzg_trl_mw < self->i.sp2_tu_mw ) self->o.hzg_vv_sb = WW_VV_SP2;
        else                                         self->o.hzg_vv_sb = WW_VV_SP1;
    }
    else {
        if( self->i.hzg_trl_mw < self->i.hk_tvl_sw ) self->o.hzg_vv_sb = WW_VV_SP2;
        else                                         self->o.hzg_vv_sb = WW_VV_SP1;
    }
}

// #ifdef __SCHWACHLAST__
/** 
  * Schwachlaststeuerung soll eingreifen, wenn nur wenig Warmwasser gebraucht wird und 10% 
  * Pumpenleistung fuer den Waermetauscher bereits zu viel Leistung bringt
  * \param self Pointer auf Instanz der Klasse ww_class_t
  * \return kein
  */
static 
void ww_Schwachlast_Steuerung( ww_class_t *self )
{
    static u16_t    schwachlastzeit = 0;

    /* Pumpe waehrend Duschbetrieb nicht abschalten, wegen Schwingung */
    if( self->o.hzg_pu_y < self->p.hzg_pu_y_min ) {
        schwachlastzeit ++;
        if( schwachlastzeit < self->p.schwachlastzeit_max ) {
            self->o.hzg_pu_y = self->p.hzg_pu_y_min;
        }
    } /* nach 30s ununterbrochener Schwachlast darf die Pumpe abschalten */
    else {
        schwachlastzeit = 0;
    }
}
// #endif

/**
  * \brief Initialisierung der ww-Task.
  *
  * Die minimale Pumpenleistung wird bei 11% Stellgroesse erreicht. Unter 10% ist die 
  * Pumpe aus. Der PI-Regler der fuer die wird hier mit initialisiert.
  * \param self Pointer auf Instanz der Klasse ww_class_t
  * \return kein
  */
void ww_Init( ww_class_t *self, const param_satz_t * const param )
{
    self->p.kes_sp_dt_sw        = param->kes.sp_dt_sw;
    self->p.tww_sw              = param->ww.tww_sw;
    self->p.frostschutz         = param->all.frostschutz;
    self->p.at_start            = param->all.at_start;
    self->p.mv_korr             = param->ww.mv_korr;
    self->p.hzg_pu_y_min        = 11.0;
    self->p.schwachlastzeit_max = 300;

    reg_PI_Init( &(self->reg_pu), USEC2SEC(param->sys.zykluszeit),
                                  param->ww.pu_reg.kp,
                                  param->ww.pu_reg.ki,
                                  param->ww.pu_reg.ap,
                                  MIN_Y_PCT,
                                  MAX_Y_PCT,
                                  &(self->o.hzg_pu_y),
                                  &(self->p.tww_sw),
                                  &(self->i.tww_mw)    );
}

/**
  * \brief Eigentlicher Warmwasser Task.
  *
  * \param par_p Pointer auf Struktur mit Parametern
  * \return kein  
  */
void ww_Run( ww_class_t *self )
{
    /* WW Heizungspumpe immer ein! */
    self->o.hzg_pu_sb = IO_EIN;

    /* Zirkulationspumpe ansteuern */
    if( (self->i.zirkzustand == zEin) || (self->i.tau_mw < self->p.frostschutz) )
        self->o.zirk_pu_sb = IO_EIN;
    else
        self->o.zirk_pu_sb = IO_AUS;

    /* PI-Regler fuer WW Heizungspumpe */
    reg_PI_Run( &(self->reg_pu) );

    /* Berechnung von WW_HZG_MV_Y aus den Temperaturen von Speicher und Ruecklauf */
    ww_MV_Steuerung( self );

    /* Schwachlast Steuerung */
#ifdef __SCHWACHLAST__
    ww_Schwachlast_Steuerung( self );
#endif
    /* Kriterium fuer Warmwasser Heizungsverteilventil */
    ww_VV_Steuerung( self );
}

/**
 * \brief Befuellen des Eingangsvektors.
 */
void ww_WriteInp(           ww_class_t *self,
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
    self->i.tww_mw       = tww_mw;
    self->i.tau_mw       = tau_mw;
    self->i.tau_avg      = tau_avg;
    self->i.wz_mw        = wz_mw,
    self->i.hzg_tvl_mw   = hzg_tvl_mw;
    self->i.hzg_trl_mw   = hzg_trl_mw;
    self->i.hk_tvl_sw    = hk_tvl_sw;
    self->i.sp1_to_mw    = sp1_to_mw;
    self->i.sp2_tu_mw    = sp2_tu_mw,
    self->i.zirkzustand  = zirkzustand;
    self->i.duschzeit    = duschzeit;
}
