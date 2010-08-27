#ifndef _FB_H_
#define _FB_H_

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
} fb_param_t;

typedef struct {
    float  tau_mw;
    float  tau_avg;
    float  tr_sw;
    float  sek_tvl_mw;
    char   zustand;
    char   partytime_flg;
} fb_in_t;

typedef struct {
    float tvl_sw;
    float prim_mv_y;
    unsigned char prim_pu_sb;
    unsigned char sek_pu_sb;
} fb_out_t;
/* <Typen/> */

/* <Prototypen> */
void fb_Init( fb_param_t *par_p, digreg_coeff_t *q, fb_out_t *out_p );
void fb_Run( const fb_param_t *par_p, const sup_digreg_coeff_t *q_p, const fb_in_t *in_p, fb_out_t *out_p );
/* <Prototypen/> */

#endif /* _FB_H_ */