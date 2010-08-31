#ifndef _KES_H_
#define _KES_H_

#include "gen_types.h"

/* <Typen> */
typedef struct {
    float TA;
    float tvl_absenk;
    float tvl_steigung;
    float tvl_niveau;
    float tvl_min;
    float tvl_max;
    float at_start;
    float frostschutz;
    float sp_dt_sw;  /* Globaler Wert div 2 !! */
    float ww_tww_sw;
} kes_param_t;

typedef struct {
    float       sp1_to_mw;
    float       sp1_tu_mw;
    float       sp2_to_mw;
    float       sp2_tu_mw;
    float       tvl_mw;
    float       hk_tvl_sw;
    float       fb_tvl_sw;
    float       ww_tww_sw;
    nutzzeit_t  duschzeit;
    char        partytime_flg;
    char        br_bm;
} kes_in_t;

typedef struct {
    float sp1_to_sw;
    float sp2_to_sw;
    float tvl_sw_sp1;
    float tvl_sw_sp2;
    float tvl_sw;
    unsigned char pu_sp1_sb;
    unsigned char pu_sp2_sb;
} kes_out_t;
/* <Typen/> */

/* <Prototypen> */
void kes_Init( void );
void kes_Run( const kes_param_t *par_p, 
              const kes_in_t    *in_p,
                    kes_out_t   *out_p );
/* <Prototypen/> */

#endif /* _KES_H_ */

