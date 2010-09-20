#ifndef _SOL_H_
#define _SOL_H_

#include "gen_types.h"

/* <Defines> */
#define SOL_NORMAL           0
#define SOL_UEBERTEMPERATUR -1

#define SOL_N_SP    2
#define SOL_N_KOLL  1
/* <Defines/> */

/* <Typen> */
typedef struct {
    float sp_t_max;
    float dt_ein_sw;
    float dt_aus_sw;
}   sol_param_t;

typedef struct {
    float to_mw;
    float tu_mw;
} sol_sp_t_mw_t;

typedef struct {
    float           koll_t_mw[SOL_N_KOLL];
    sol_sp_t_mw_t   t_sp[SOL_N_SP];
} sol_in_t;
/* <Typen/> */

typedef struct {
    do_bitbyte_t    sp_av_sb[SOL_N_SP];
    do_bitbyte_t    sol_pu_sb[SOL_N_KOLL];
} sol_out_t;   

/* <Prototypen> */
void sol_Init( sol_param_t *par_p );
int sol_Run(  const sol_param_t  *par_p,
              const sol_in_t     *in_p,
                    sol_out_t    *out_p );
/* <Prototypen/> */


#endif /* _SOL_H_ */

