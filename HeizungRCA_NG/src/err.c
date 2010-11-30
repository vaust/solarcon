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
    
    in_p->sol_errcnt      = 0;  /* Zaehler auf 0 -> kein Fehler               */
    in_p->ao_errcnt       = 0;  /* Jedes Fehlerereignis zählt Fehler herunter */
    in_p->tempsens_errcnt = 0;

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

    if( (0          == out_p->br_Countdown       ) ||
        (SET        == in_p->br_StoerMeldung     ) ||
        (SET        == in_p->stb_Fussbodenheizung) ||
        (ERR_MAXCNT >  in_p->sol_errcnt          ) ||
        (ERR_MAXCNT >  in_p->tempsens_errcnt     ) ||
        (ERR_MAXCNT >  in_p->ao_errcnt           )    ) {

        out_p->Sammelstoermeldung = SET;
    }
    else {
        out_p->Sammelstoermeldung = RESET;
    }
}

/**
 * \brief Sammelstoermeldung zurücksetzen.
 * Dies Funktion soll vom Benutzerinterface aufgerufen werden.
 * \param par_p[in] enthält timeout für Anforderungscountdown
 * \param out_p[out] Störmeldung zurücksetzen.
 */
void err_Reset_Sammelstoermeldung( err_param_t *par_p,
                                   err_in_t    *in_p,
                                   err_out_t   *out_p )
{
    out_p->br_Countdown = par_p->br_TimeOut;
    out_p->Sammelstoermeldung = RESET;
    in_p->sol_errcnt          = 0;
    in_p->tempsens_errcnt     = 0;
    in_p->ao_errcnt           = 0;
}

/*
void err_WriteInp( err_in_t *in_p, float        kes_tvl_sw,
                                   float        kes_tvl_mw,
                                   di_bitbyte_t br_RueckMeldung,
                                   di_bitbyte_t br_StoerMeldung,
                                   di_bitbyte_t stb_Fussbodenheizung,
                                   s16_t        tempsens_errcnt,
                                   s16_t        ao_errcnt,
                                   s16_t        sol_errcnt          )
{
    in_p->kes_tvl_sw           = kes_tvl_sw;
    in_p->kes_tvl_mw           = kes_tvl_mw;
    in_p->br_RueckMeldung      = br_RueckMeldung;
    in_p->br_StoerMeldung      = br_StoerMeldung;
    in_p->stb_Fussbodenheizung = stb_Fussbodenheizung;
    in_p->tempsens_errcnt      = tempsens_errcnt;
    in_p->ao_errcnt            = ao_errcnt;
    in_p->sol_errcnt           = sol_errcnt;
}
*/

