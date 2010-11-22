#ifndef _ERR_H_
#define _ERR_H_

#include "gen_types.h"
#include "io_v2.h"

/* <Defines> */
#define SOL_NORMAL  0
/* <Defines/> */

/* <Typen> */
typedef struct {
    s16_t   br_TimeOut;
    float   dt;
} err_param_t;


typedef struct {
    di_bitbyte_t    koll_Uebertemperatur;
    float           kes_tvl_sw;
    float           kes_tvl_mw;
    di_bitbyte_t    br_RueckMeldung;
    di_bitbyte_t    br_StoerMeldung;
    di_bitbyte_t    stb_Fussbodenheizung;
    s16_t           sol_err;
    s16_t           fb_err;
    s16_t           hk_err;
    s16_t           ww_err;
    s16_t           kes_err;
} err_in_t;


typedef struct {
    s16_t           br_Countdown;
    do_bitbyte_t    Sammelstoermeldung;
} err_out_t;
/* <Typen/> */

/* <Prototypen> */
void err_Init( err_param_t *par_p, 
               err_in_t    *in_p, 
               err_out_t   *out_p );

void err_Run( const err_param_t *par_p,
              const err_in_t    *in_p,
                    err_out_t   *out_p );

void err_Reset_Sammelstoermeldung( err_param_t *par_p,
                                   err_out_t   *out_p );

/* <Prototypen/> */


#endif /* _ERR_H_ */

