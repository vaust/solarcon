#define _ERR_C_

#include "err.h"

/* 
SAMMELSTOERMELDUNG =
    Kollektorübertemperatur ||
    Brennermeldung kommt nicht nach max 1 min nach Anforderung ||
    Kesselstörmeldung ist gesetzt ||
    STB Fussbodenheizung hat ausgelöst ||
    
    ...


*/

void err_Init( err_param_t *par_p )
{
    par_p->br_TimeOut = 240;    /* 4 min */
}

/** err_Run(): Betriebszustaende lesen und auf Plausibiliteat prufen.
    Falls nicht plausibel: Sammelstoermeldung blinken lassen
  */
void err_Run( const err_param_t *par_p,
              const err_in_t    *in_p,
                    err_out_t   *out_p )
{
    if( (in_p->kes_tvl_sw    >  in_p->kes_tvl_mw ) && 
        (out_p->br_Countdown >= par_p->br_TimeOut)    ) {
        if( in_p->br_RueckMeldung == RESET ) 
            if( br_Countdown > 0 ) br_Countdown --;
        else 
            br_Countdown = par_p->br_TimeOut;
    }
    else {
        out_p->br_Countdown = par_p->br_TimeOut; 
    }
    
    if( (0    == br_Countdown              ) ||
        (SET  == in_p->br_StoerMeldung     ) ||
        (SET  == in_p->stb_Fussbodenheizung)    ) {
     
        out_p->Sammelstoermeldung = SET;
    }
}
        
    
         
