#ifndef _WW_H_
#define _WW_H_

#include "sup.h"
#include "gen_tpyes.h"

/* <Typen> */
typedef struct {
    float pu_reg_kp;
    float pu_reg_tn;
    float mv_reg_kp;
    float mv_reg_tn;   
    float TA;
    float kes_sp_dt_sw;
    float mv_korr;
} ww_param_t;

typedef struct {
    float tww_mw;
    float tww_sw;
    u32_t wz_mw;
    float hzg_trl_mw;
    float sol_sp1_to_mw;
    
} ww_in_t;

typedef struct {
    float           hzg_tvl_sw;
    float           hzg_mv_y;
    float           hzg_pu_y;
    do_bitbyte_t    zirk_pu_sb;  
    do_bitbyte_t    hzg_pu_sb;
} ww_out_t;

/* <Typen/> */

/* <Prototypen> */
void ww_Init( ww_param_t *par_p, sup_digreg_coeff_t *q_hzg_pu_p, ww_out_t *out_p );
void ww_Run( const ww_param_t         *par_p, 
             const sup_digreg_coeff_t *q_p, 
             const ww_in_t            *in_p, 
                   ww_out_t           *out_p );
/* <Prototypen/> */

#endif /* _WW_H_ */

