#ifndef _FB_H_
#define _FB_H_

#include "gen_types.h"
#include "sup.h"

/* <Typen> */
typedef struct fb_param_s {
    float reg_kp;
    float reg_ap;
    float reg_ki;
    float TA;
    float tvl_absenk;
    float tvl_steigung;
    float tvl_niveau;
    float tvl_min;
    float tvl_max;
    float at_start;
    float frostschutz;
    float tr_sw;
} fb_param_t;

typedef struct fb_in_s {
    float       tau_mw;
    float       tau_avg;
    float       sek_tvl_mw;
    abgesenkt_t zustand;
    u8_t        partytime_flg;
} fb_in_t;

typedef struct fb_out_s {
    float            tvl_sw;
    sup_digreg_out_t prim_mv_y;
    do_bitbyte_t     prim_pu_sb;
    do_bitbyte_t     sek_pu_sb;
} fb_out_t;
/* <Typen/> */

/* <Prototypen> */
void fb_Init( fb_param_t *par_p, sup_digreg_coeff_t *q_p, fb_out_t *out_p );
void fb_Run( const fb_param_t *par_p, const sup_digreg_coeff_t *q_p, const fb_in_t *in_p, fb_out_t *out_p );
void fb_WriteInp(       fb_in_t     *in_p,
                  const float        tau_mw,
                  const float        tau_avg,
                  const float        sek_tvl_mw,
                  const abgesenkt_t  zustand,
                  const u8_t         partytime_flg );
/* <Prototypen/> */

#endif /* _FB_H_ */

