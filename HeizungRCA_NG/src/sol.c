#define _SOL_C_

#include "sol.h"
#include "param.h"

void sol_Init( sol_param_t *par_p )
{
    par_p->sp_t_max  = param_sol_sp_t_max;
    par_p->dt_ein_sw = param_sol_dt_ein_sw;
    par_p->dt_aus_sw = param_sol_dt_aus_sw;
}

/**
 * \brief Solarspeicherabsperrventil entsprechend der Temperaturdifferenzen
 * zwischen Speicher und Kollektor betätigen.
 * \param par_p[in] Parametrisierung
 * \param koll_t_mw[in] Vorlauftemperatur des speisenden Kollektors
 * \param t_sp_p[in] Pointer auf Struktur mit oberer und unterer Kollektortemperatur
 * \param sp_av_sb_p[out] Zustand des Absperrventils (offen/geschlossen)
 * \return Fehlercode z.B Speicherübertemperatur: Die Speicher können die Wärme nicht
 *         mehr aufnehmen
 */
static 
int sol_Speicherabsperrventil( const sol_param_t   *par_p, 
                               const float         koll_t_mw,
                               const sol_sp_t_mw_t *t_sp_p,  
                                     do_bitbyte_t  *sp_av_sb_p )
{
    int errorcode;

    if( t_sp_p->to_mw < par_p->sp_t_max ) {
        /* Die Kollektortemperatur liegt unter dem Maximalwert  */
        if( koll_t_mw > ( t_sp_p->tu_mw + par_p->dt_ein_sw ) ) {
            *sp_av_sb_p  = IO_AUF;
        }
        else {
            if( koll_t_mw <= ( t_sp_p->tu_mw + par_p->dt_aus_sw ) ) {
                *sp_av_sb_p  = IO_ZU;
            }
            else {
                *sp_av_sb_p  = IO_AUF;
            }
        }
        errorcode = SOL_NORMAL;
    }
    else {
        /* Die Kollektortemperatur liegt ueber dem Maximalwert  */
        *sp_av_sb_p  = IO_ZU;
        errorcode = SOL_UEBERTEMPERATUR;
    }
    return( errorcode );
}

/**
 * \brief Die Pumpe eines Kollektors einschalten, wenn mind. 1 Ventil zum Speicher offen ist.
 * \param out_p Eingangsgrößen Ventilstellung, Ausgangsgrößen Pumpe ein/aus
 */
static 
void sol_Pumpe( sol_out_t *out_p )
{
    if( ( out_p->av_sb[SP1] == IO_ZU ) &&
        ( out_p->av_sb[SP2] == IO_ZU )    ) {
        out_p->pu_sb[KO1] = IO_AUS;
    }
    else {
        out_p->pu_sb[KO1] = IO_EIN;
    }
}

/**
 * \brief eigentlicher Solarregler. Absperrventile steuern und die Pumpen entsprechend betätigen.
 * \param par_p[in]
 * \param in_p[in]
 * \param out_p[out]
 * \return Fehlercode für Sammelstörungsauswertung.
 */
s16_t sol_Run(  const sol_param_t  *par_p,
                const sol_in_t     *in_p,
                      sol_out_t    *out_p )
{
    int errorcode = 0;

    /* Absperrventil Speicher 1 */
    errorcode += sol_Speicherabsperrventil( par_p, in_p->koll_t_mw[KO1], &(in_p->t_sp[SP1]), &(out_p->av_sb[SP1]) ); 
    /* Absperrventil Speicher 2 */
    errorcode += sol_Speicherabsperrventil( par_p, in_p->koll_t_mw[KO1], &(in_p->t_sp[SP2]), &(out_p->av_sb[SP2]) );
    /* Pumpe entsprechend des Absperrventilzustands schalten */
    sol_Pumpe( out_p );
    return( errorcode );
}

/**
 * \brief Befüllen des Eingangsvektors
 * \param koll_t_mw[in] Kollektortemperatur
 * \param sp1_to_mw[in] Obere Temperatur des Speicher 1
 * \param sp1_tu_mw[in] Untere Temperatur des Speicher 1
 * \param sp2_to_mw[in] Obere Temperatur des Speicher 2
 * \param sp2_tu_mw[in] Untere Temperatur des Speicher 2
 */
void sol_WriteInp( sol_in_t    *in_p,
		           const float  koll_t_mw,
		           const float  sp1_to_mw,
		           const float  sp1_tu_mw,
		           const float  sp2_to_mw,
		           const float  sp2_tu_mw )
{
    in_p->koll_t_mw[KO1]  = koll_t_mw;
    in_p->t_sp[SP1].to_mw = sp1_to_mw;
    in_p->t_sp[SP1].tu_mw = sp1_tu_mw;
    in_p->t_sp[SP2].to_mw = sp2_to_mw;
    in_p->t_sp[SP2].tu_mw = sp2_tu_mw;
}


