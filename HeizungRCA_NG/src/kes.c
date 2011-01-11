#define _KES_C_

#include "gen_types.h"
#include "param.h"
#include "kes.h"


void kes_Init( kes_param_t *par_p, 
               kes_out_t   *out_p )
{
    par_p->sp_dt_sw     = param_kes_sp_dt_sw;       
    par_p->ww_tww_sw    = param_ww_tww_sw;

    /* Ausgaenge initialisieren: (notwendig wg. undefinierten Zustands in Hystereseschleife zum Programmstart */
    out_p->pu_sp1_sb = IO_AUS;
    out_p->pu_sp2_sb = IO_AUS;
}
/**
 * \brief Speichersolltemperaturen berechnen, Speicherpumpen ansteuern und Kesselsollvorlauftemperatur bestimmen.
 * \param[in] par_p Parametersatz fuer die Kesselansteuerung
 * \param[in] in_p  Eingangsgroessen
 * \param[out out_p Ausgangsgroessen
 */
void kes_Run( const kes_param_t *par_p, 
              const kes_in_t    *in_p,
                    kes_out_t   *out_p )
{
    /* Speicher 1 = Warmwasser und Heizkoerper  
       Speicher 2 = Fussbodenheizung            */

    /* Berechne Solltemperatur Speicher 1: */
    if( (in_p->duschzeit == zJa) && 
        (in_p->hk_tvl_sw < (par_p->ww_tww_sw + par_p->sp_dt_sw)) )
        out_p->sp1_to_sw = par_p->ww_tww_sw + par_p->sp_dt_sw;
    else
        out_p->sp1_to_sw = in_p->hk_tvl_sw + par_p->sp_dt_sw;

    /* Berechne Solltemperatur Speicher 2: */
    out_p->sp2_to_sw = in_p->fb_tvl_sw + par_p->sp_dt_sw;

    /* Schaltkriterium fuer Speicherladepumpe 1 */
    if( in_p->sp1_to_mw < out_p->sp1_to_sw ) {
        out_p->tvl_sw_sp1 = out_p->sp1_to_sw + par_p->sp_dt_sw;
        /* Einschalten der Pumpe erst wenn Brenner ein oder die Vorlauftemperatur > Speichertemperatur */
        /* if( (in_p->br_bm == IO_EIN) || (in_p->tvl_mw > in_p->sp1_to_mw) ) */
            out_p->pu_sp1_sb = IO_EIN;
        /* Wenn Sp.-pumpe 1 ein, Sp.-pumpe 2 immer aus! */
        out_p->pu_sp2_sb = IO_AUS;
    }
    else if( in_p->sp1_to_mw >= (out_p->sp1_to_sw + par_p->sp_dt_sw) ) {
        out_p->tvl_sw_sp1 = 0.0;   /* Kessel AUS */
        out_p->pu_sp1_sb = IO_AUS;
    }
    
    /* Schaltkriterium fuer Speicherladepumpe 2 */
    if( out_p->pu_sp1_sb == IO_AUS ) {
    /* Sp.-pumpe 2 nur einschalten, wenn Sp.-pumpe 1 aus ist! */
        if( in_p->sp2_to_mw < out_p->sp2_to_sw ) {
            out_p->tvl_sw_sp2 = out_p->sp2_to_sw + par_p->sp_dt_sw;
            /* Einschalten der Pumpe erst wenn Brenner ein oder die Vorlauftemperatur > Speichertemperatur */
            /* if( (in_p->br_bm == IO_EIN) || (in_p->tvl_mw > in_p->sp2_to_mw) ) */
                out_p->pu_sp2_sb = IO_EIN;
        }
        else if( in_p->sp2_to_mw >= (out_p->sp2_to_sw + par_p->sp_dt_sw/2.0) ) {
            out_p->tvl_sw_sp2 = 0.0;  /* Kessel AUS */
            out_p->pu_sp2_sb = IO_AUS;
        }
    }
    else /* if( KES_PU_SP1_SB == IO_EIN ) */ {
        out_p->tvl_sw_sp2 = 0.0;  /* Kessel AUS */
        out_p->pu_sp2_sb = IO_AUS;
    }

    /* Notfall in dem Sp.-pumpe 2 immer laufen soll: */
    /* if( in_p->sp2_to_mw < (in_p->fb_tvl_sw - par_p->sp_dt_sw) ) */
    if( in_p->fb_prim_mv_y > 95.0 ) {
        if( in_p->br_bm == IO_EIN ) out_p->pu_sp2_sb = IO_EIN;
    }
    
    /* Sollwertvorgabe fuer den Kessel:
     * %-Zahl entspricht Vorlauftemperatur in °C
     * 100% entspr. 100°C
     * 10%  entpsr.  10°C
     * Werte kleiner 10%: Kessel ist abgeschaltet
     */

    if( out_p->tvl_sw_sp1 >= out_p->tvl_sw_sp2 ) 
        out_p->tvl_sw = out_p->tvl_sw_sp1;
    else 
        out_p->tvl_sw = out_p->tvl_sw_sp2;
}



void kes_WriteInp(       kes_in_t     *in_p,
                   const float         sp1_to_mw,
                   const float         sp2_to_mw,
                   const float         tvl_mw,
                   const u32_t         gz_mw,
                   const float         hk_tvl_sw,
                   const float         fb_tvl_sw,
                   const float         fb_prim_mv_y,
                   const nutzzeit_t    duschzeit,
                   const di_bitbyte_t  br_bm      )
{
    in_p->sp1_to_mw    = sp1_to_mw;
    in_p->sp2_to_mw    = sp2_to_mw;
    in_p->tvl_mw       = tvl_mw;
    in_p->gz_mw        = gz_mw;
    in_p->hk_tvl_sw    = hk_tvl_sw;
    in_p->fb_tvl_sw    = fb_tvl_sw;
    in_p->fb_prim_mv_y = fb_prim_mv_y;
    in_p->duschzeit    = duschzeit;
    in_p->br_bm        = br_bm;
}



