/** \file Sammelstörmeldung bedienen
 * \author Volker Stegmann
 */

#define _ERR_C_

#include "gen_types.h"
#include "param.h"
#include "err.h"

/*
SAMMELSTOERMELDUNG =
        Kollektoruebertemperatur
  oder  Brennermeldung kommt nicht nach max 1 min nach Anforderung
  oder  Kesselstoermeldung ist gesetzt
  oder  STB der Fussbodenheizung hat ausgeloest
  oder  ...
*/

void err_Init( err_param_t *par_p, err_in_t *in_p, err_out_t *out_p )
{
    par_p->br_TimeOut   = 240;                       /* 240 entspr. bei 1sec Zyklus 4 min        */
    par_p->dt           = param_kes_sp_dt_sw / 2.0;  /* Tvl_MW muss um diesen Betrag hoeher sein */

    out_p->br_Countdown = par_p->br_TimeOut;
    
    in_p->sol_err      = 0;    
    in_p->tempsens_err = 0;
}

/** 
  * \brief Betriebszustaende lesen und auf Plausibiliteat pruefen.
  * Falls nicht plausibel: Sammelstoermeldung setzen
  */
void err_Run( const err_param_t *par_p,
              const err_in_t    *in_p,
                    err_out_t   *out_p )
{
    if( in_p->kes_tvl_sw > (in_p->kes_tvl_mw + par_p->dt) ) {
        if( in_p->br_RueckMeldung == RESET ) {
            if( out_p->br_Countdown > 0 ) out_p->br_Countdown --;
        }
        else {
            out_p->br_Countdown = par_p->br_TimeOut;
        }
    }
    else {
        out_p->br_Countdown = par_p->br_TimeOut;
    }

    if( (0    == out_p->br_Countdown       ) ||
        (SET  == in_p->br_StoerMeldung     ) ||
        (SET  == in_p->stb_Fussbodenheizung) ||
        (0    != in_p->sol_err             ) ||
        (0    != in_p->tempsens_err        )   ) {

        out_p->Sammelstoermeldung = SET;
    }
    else {
        out_p->Sammelstoermeldung = RESET;
    }
}

/**
 * \brief Sammelstörmeldung zurücksetzen.
 * Dies Funktion soll vom Benutzerinterface aufgerufen werden.
 * \param par_p[in] enthält timeout für Anforderungscountdown
 * \param out_p[out] Störmeldung zurücksetzen.
 */
void err_Reset_Sammelstoermeldung( err_param_t *par_p, err_out_t *out_p )
{
    out_p->br_Countdown = par_p->br_TimeOut;
    out_p->Sammelstoermeldung = RESET;
}
