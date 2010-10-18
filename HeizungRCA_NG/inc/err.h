#ifndef _ERR_H_
#define _ERR_H_

#include "gen_types.h"

/* <Defines> */
#define SOL_NORMAL  0
/* <Defines/> */

/* <Typen> */
typedef struct {
    // float TA;       // Abtastzeit
    u16_t           br_TimeOut;
}   err_param_t;


typedef struct {
    di_bitbyte_t    koll_Uebertemperatur;
    float           kes_tvl_sw;
    float           kes_tvl_mw;
    di_bitbyte_t    br_RueckMeldung;
    di_bitbyte_t    br_StoerMeldung;
    di_bitbyte_t    stb_Fussbodenheizung;    
} err_in_t;
/* <Typen/> */

typedef struct {
    u16_t           br_Countdown;
    do_bitbyte_t    Sammelstoermeldung;
} sol_out_t;   

/* <Prototypen> */
void err_Init( sol_param_t *par_p );
int err_Run(  const err_param_t  *par_p,
              const err_in_t     *in_p,
                    err_out_t    *out_p );
/* <Prototypen/> */


#endif /* _ERR_H_ */

