#ifndef _HK_H_
#define _HK_H_

#include "sup.h"

/* <Typen> */
typedef struct {
    float reg_kp;
    float reg_tn;
    float TA;
    float tvl_absenk;
    float tvl_steigung;
    float tvl_niveau;
    float tvl_min;
    float tvl_max;
    float at_start;
    float frostschutz;
} hk_param_t;

typedef struct {
    float        tau_mw;
    float        tau_avg;
    float        tr_sw;
    float        tvl_mw;
    abgesenkt_t  zustand;
    char         partytime_flg;
} hk_in_t;

typedef struct {
    float        tvl_sw;
    float        mv_y;
    do_bitbyte_t pu_sb;
} hk_out_t;
/* <Typen/> */

/* <Prototypen> */
void hk_Init( hk_param_t *par_p, sup_digreg_coeff_t *q_p, hk_out_t *out_p );
void hk_Run( const hk_param_t         *par_p, 
             const sup_digreg_coeff_t *q_p, 
             const hk_in_t            *in_p, 
                   hk_out_t           *out_p );

/* <Prototypen/> */

#endif /* _HK_H_ */

