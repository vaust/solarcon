#define _ERR_C_

#include "gen_types.h"
#include "err.h"

/*
SAMMELSTOERMELDUNG =
    Kollektorübertemperatur ||
    Brennermeldung kommt nicht nach max 1 min nach Anforderung ||
    Kesselstörmeldung ist gesetzt ||
    STB Fussbodenheizung hat ausgelöst ||

    ...


*/

void err_Init( err_param_t *par_p, err_out_t *out_p )
{
    par_p->br_TimeOut   = 240;      /* 240 entspr. 4 min */
    par_p->dt           =   5.0;    /* Tvl_MW muss um diesen Betrag hoeher sein */
    out_p->br_Countdown = par_p->br_TimeOut;
}

/** err_Run(): Betriebszustaende lesen und auf Plausibiliteat prufen.
    Falls nicht plausibel: Sammelstoermeldung blinken lassen
  */
void err_Run( const err_param_t *par_p,
              const err_in_t    *in_p,
                    err_out_t   *out_p )
{
    if( (in_p->kes_tvl_sw) > in_p->kes_tvl_mw + par_p->dt ) {
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
        (0    != in_p->sol_err             )    ) {

        out_p->Sammelstoermeldung = SET;
    }
}



