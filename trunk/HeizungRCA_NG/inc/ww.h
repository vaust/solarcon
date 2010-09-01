#ifndef _WW_H_
#define _WW_H_

#include "sup.h"
#include "gen_types.h"

/* <Defines> */
#define WW_VV_SP1       0x00
#define WW_VV_SP2       0x01
/* <Defines> */

/* <Typen> */
typedef struct {
    float pu_reg_kp;
    float pu_reg_tn;
    float mv_reg_kp;
    float mv_reg_tn;   
    float TA;
    float kes_sp_dt_sw;
    float frostschutz;
    float at_start;
    float mv_korr;
    float hzg_pu_y_min;
    u16_t schwachlastzeit_max;
    float hk_tvl_sw;
} ww_param_t;

typedef struct {
    float tww_mw;
    float tww_sw;
    float tau_mw;
    float tau_36h_mittel;
    u32_t wz_mw;
    float hzg_trl_mw;
    float sol_sp1_to_mw;
    float sol_sp2_tu_mw;
    abgesenkt_t zirkzustand;
} ww_in_t;

typedef struct {
    float           hzg_tvl_sw;
    float           hzg_mv_y;
    float           hzg_pu_y;
    do_bitbyte_t    zirk_pu_sb;  
    do_bitbyte_t    hzg_pu_sb;
    do_bitbyte_t    hzg_vv_sb;    
} ww_out_t;

/* <Typen/> */

/* <Prototypen> */
static void ww_MV_Steuerung( const ww_param_t *par_p, 
                             const ww_in_t    *in_p, 
                                   ww_out_t   *out_p );
                            
static void ww_VV_Steuerung( const ww_param_t *par_p, 
                             const ww_in_t    *in_p, 
                                   ww_out_t   *out_p );
              
static void ww_Schwachlast_Steuerung( const ww_param_t *par_p, 
                                            ww_out_t   *out_p );
              
void ww_Init( ww_param_t         *par_p, 
              sup_digreg_coeff_t *q_hzg_pu_p, 
              ww_out_t           *out_p );
                    
void ww_Run( const ww_param_t         *par_p, 
             const sup_digreg_coeff_t *q_hzg_pu_p, 
             const ww_in_t            *in_p, 
                   ww_out_t           *out_p );
/* <Prototypen/> */

#endif /* _WW_H_ */

